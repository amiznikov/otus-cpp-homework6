#pragma once

#include <cmath>
#include "./CustomContainer.hpp"

namespace vector {
    template<typename T>
    class Iterator: public CustomIterator<T> {
        public:
            Iterator(T* region, size_t size) : region_(region), size_(size) {};
            T& operator*() override {
                return region_[index_];
            }
            Iterator& operator++() override {
                index_ += 1;
                return *this;
            }
            bool operator!=(const CustomIterator<T>& other) override {
                //FIXME скорее всего этот код просто для того чтобы использовавть other
                //и можно просто описать index < size_ но для общего замысловатого вида пущай будет так
                const Iterator<T>* otherIterator = dynamic_cast<const Iterator<T>*>(&other);
                if (otherIterator) {
                    return index_ < otherIterator->size_;
                }
                return true;
            }
        private:
            T* region_;
            size_t size_;
            size_t index_ = 0;
        };
}

template<typename T>
class CustomVector: public CustomContainer<T, vector::Iterator<T>> {
public:
    CustomVector() = default;
    CustomVector(const double& reserved_index) : reserved_index_(reserved_index) {
        region_ = new T[1];
        capacity_ = 1;
    };
    CustomVector(const CustomVector& other) {
        if (this != &other) {
            copy_from_other(other);
        }
    }
    CustomVector& operator=(const CustomVector& other) {
        if (this != other) {
            copy_from_other(other);
        }
        return *this;
    }
    CustomVector(CustomVector&& other) {
        region_ = other.region_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        reserved_index_ = other.reserved_index_;
        other.region_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.reserved_index_ = 0.0;
    }
    CustomVector& operator=(CustomVector&& other) {
        CustomVector tmp{std::move(other)};
        return *this = tmp;
    }
    ~CustomVector() override {
        clear();
    }
    void clear() override {
        delete [] region_;
        size_ = 0;
    }
    void push_back(T value) override {
            T* new_region = get_region(1);
            new_region[size_] = value;
            size_ += 1;

    }
    void insert(T val, size_t index) override {
        if (index > size_) {
            return;
        }
        T* new_region = get_region(1);
        for(int i = size_; i > index; i--) {
            new_region[i] = new_region[i - 1];
        }
        new_region[index] = val;
        size_ += 1;
    }
    void erase(size_t index) override {
        if (index >= size_) {
            return;
        }

        for (size_t i = 0; i < size_; ++i) {
            if (i > index) {
                region_[i - 1] = region_[i];
            }
        }
        T* new_region = get_region(-1);
        size_ -= 1;
    }
    vector::Iterator<T> begin() override {
        return vector::Iterator<T>{region_, size_};
    }
    vector::Iterator<T> end() override {
        return vector::Iterator<T>{region_, size_};
    }
    T operator[](size_t index) override {
        return region_[index];
    }
    size_t size() const override {
        return size_;
    }
private:
    size_t size_ = 0;
    double reserved_index_ = 0.0;
    size_t capacity_ = 0;
    T* region_ = nullptr;
    //вообще не уверен что я правильно поступаю, но что-то типо std::move для динамических массивов я не нашел( может плохо искал
    void update_region(T*& new_region) {
        delete [] region_;
        region_ = std::move(new_region);
    }
    T*& get_region(const int updated_count = 0) {
        if (reserved_index_ > 0.0) {
            if (size_ >= capacity_) {
                capacity_ = ceil(size_ * reserved_index_);
                resize_region(capacity_);
            }
        } else {
            size_t new_size = size_ + updated_count;
            resize_region(new_size);
        }
        return region_;
    }
    void resize_region(size_t& new_size) {
        T* new_region = new T[new_size];
        for (size_t i = 0; i < size_; ++i) {
            new_region[i] = region_[i]; // копирование элементов
        }
        update_region(new_region);
    }
    size_t real_capacity() const {
        return capacity_ > 0 ? capacity_ : size_;
    }
    void copy_from_other(const CustomVector& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        reserved_index_ = other.reserved_index_;
        region_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            region_[i] = other.region_[i];
        }
    }
};