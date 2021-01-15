#pragma once

#include <vector>
#include <cassert>
#include <cinttypes>
#include <stdexcept>
#include <ostream>

template<class T>
class SizedVector {
private:
    uint32_t size;
    std::vector<T> mem;
public:
    explicit SizedVector(uint32_t size) : size(size) {}

    inline void push_back(const T &t) {
        if (this->mem.size() >= size) {
            this->mem.erase(mem.begin());
        }
        this->mem.push_back(t);
    }

    inline void push_back(const std::vector<T> &data) {
        if (data.size() < size) {
            uint32_t newSize = data.size() + mem.size();
            if (newSize >= size) {
                uint32_t toRemove = newSize - size;
                mem.erase(mem.begin(), mem.begin() + toRemove);
            }

            assert(mem.size() + data.size() <= size);

            mem.insert(mem.end(), data.begin(), data.end());

        } else if (data.size() == size) {
            size = data.size();
            this->mem = std::vector(data.begin(), data.end());
        } else {
            throw std::runtime_error("Can not handle data this big.");
        }
    }

    inline std::vector<T> &data() {
        return mem;
    }

    inline T &front() {
        return mem.front();
    }

    inline T &back() {
        return mem.back();
    }

    inline T &operator[](uint32_t index) {
        return mem[index];
    }

    inline void operator<<(T t) {
        this->push_back(t);
    }

    friend std::ostream &operator<<(std::ostream &os, const SizedVector &vector) {
        os << "Sized Vector<" << vector.size << "> [";
        for (const auto &i : vector.mem) {
            os << i << ", ";
        }
        os << "]";
        os << std::endl;
        return os;
    }
};