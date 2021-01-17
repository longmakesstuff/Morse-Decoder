#pragma once

#include <Common.hpp>
#include <vector>
#include <cassert>
#include <cinttypes>
#include <stdexcept>
#include <ostream>
#include <set>

/**
 * A ring buffer style for saving incoming data
 * Also implemented running statistics
 * @tparam T flexible template type
 */
template<class T>
class SizedVector {
private:
    uint32_t cap;
    std::vector<T> mem;
    std::set<T> set;
    fpt old_m = 0;
    fpt new_m = 0;
    fpt old_s = 0;
    fpt new_s = 0;
public:
    explicit SizedVector(uint32_t size) : cap(size) {}

    /**
     * Push a new element to the sized vector
     * @param t new variable
     * Also calculate the running mean
     */
    inline void push_back(const T &t) {
        // Delete first element
        if (this->mem.size() >= cap) {
            if(this->set.find(mem.front()) != this->set.end()) {
                this->set.erase(this->set.find(mem.front()));
            }
            this->mem.erase(mem.begin());
        }
        // Push new element
        this->mem.push_back(t);
        this->set.insert(t);

        if constexpr (std::is_same_v<T, fpt> || std::is_same_v<T, int> || std::is_same_v<T, long>) {
            // Start running statistics
            if (this->mem.size() == 1) {
                old_m = new_m = t;
            } else {
                new_m = old_m + (t - old_m) / this->mem.size();
                new_s = old_s + (t - old_m) * (t - new_m);

                old_m = new_m;
                old_s = new_s;
            }
        }

        assert(mem.size() <= cap);
    }

    /**
     * Bulk push new data to vector
     * @param data  bulk data
     */
    inline void push_back(const std::vector<T> &data) {
        // There is free space
        if (data.size() < cap) {

            for (size_t i = 0; i < data.size(); i++) {
                this->push_back(data[i]);
            }

            // New data bulk's size is the same as the capacity
        } else if (data.size() == cap) {
            this->reset();
            for (size_t i = 0; i < data.size(); i++) {
                this->push_back(data[i]);
            }
        } else {
            throw std::runtime_error("Can not handle data this big.");
        }

        assert(mem.size() <= cap);
    }

    inline size_t size() {
        return this->mem.size();
    }

    inline fpt mean() {
        if (this->mem.empty()) {
            return 0.0;
        }
        return new_m;
    }

    inline fpt entropy() {
        return std::log2(this->set.size());
    }

    inline fpt std() {
        if (this->mem.size() > 1) {
            return new_s / (mem.size() - 1);
        } else {
            return 0.0;
        }
    }

    [[nodiscard]] inline uint32_t getCap() const {
        return cap;
    }

    inline void reset() {
        this->mem = std::vector<T>();
        this->set = std::set<T>();
        old_m = 0;
        new_m = 0;
        old_s = 0;
        new_s = 0;
    }

    inline std::vector<T> &data() {
        return mem;
    }

    inline T &operator[](uint32_t index) {
        return mem[index];
    }

    inline void operator<<(T t) {
        this->push_back(t);
    }

    friend std::ostream &operator<<(std::ostream &os, const SizedVector &vector) {
        os << "Sized Vector<" << vector.cap << "> [";
        for (const auto &i : vector.mem) {
            os << i << ", ";
        }
        os << "]";
        os << std::endl;
        return os;
    }
};