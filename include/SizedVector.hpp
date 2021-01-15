#pragma once

#include <Common.hpp>
#include <vector>
#include <cassert>
#include <cinttypes>
#include <stdexcept>
#include <ostream>

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
    fpt old_m = 0;
    fpt new_m = 0;
    fpt old_s = 0;
    fpt new_s = 0;
public:
    explicit SizedVector(uint32_t size) : cap(size) {}

    inline void push_back(const T &t) {
        if(t > 50) {
            if (this->mem.size() >= cap) {
                this->mem.erase(mem.begin());
            }
            this->mem.push_back(t);

            if (this->mem.size() == 1) {
                old_m = new_m = t;
                old_s = 0;
            } else {
                new_m = old_m + (t - old_m) / this->mem.size();
                new_s = old_s + (t - old_m) * (t - new_m);

                old_m = new_m;
                old_s = new_s;
            }
        }
    }

    inline void push_back(const std::vector<T> &data) {
        if (data.size() < cap) {
            uint32_t newSize = data.size() + mem.size();
            if (newSize >= cap) {
                uint32_t toRemove = newSize - cap;
                mem.erase(mem.begin(), mem.begin() + toRemove);
            }

            assert(mem.size() + data.size() <= cap);

            for(int32_t i = 0; i < data.size(); i++) {
                this->push_back(data[i]);
            }

        } else if (data.size() == cap) {
            this->mem = std::vector<T>();
            old_m = 0;
            new_m = 0;
            old_s = 0;
            new_s = 0;
            for(int32_t i = 0; i < data.size(); i++) {
                this->push_back(data[i]);
            }
        } else {
            throw std::runtime_error("Can not handle data this big.");
        }
    }

    inline size_t size() {
        return this->mem.size();
    }

    inline fpt mean() {
        if(this->mem.empty()) {
            return 0.0;
        }
        return new_m;
    }

    inline fpt std() {
        if(this->mem.size() > 1) {
            return new_s / (mem.size() - 1);
        }else {
            return 0.0;
        }
    }

    inline void reset() {
        this->mem = std::vector<fpt>();
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