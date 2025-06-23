#pragma once
//я не уверен что этот инклуд нужен, но иначе вылазит ошибка
#include <cstddef>
#include "./CustomIterator.hpp"

template<typename T, typename IteratorType = CustomIterator<T>>
class CustomContainer {
  public:
    virtual ~CustomContainer() = default;
    // struct Iterator {
    //     virtual ~Iterator() = default;
    //     virtual T& operator*() = 0;
    //     virtual Iterator& operator++() = 0;
    // };
    virtual void push_back(T val) = 0;
    virtual void insert(T val, size_t index) = 0;
    virtual void erase(size_t index) = 0;
    virtual IteratorType begin() = 0;
    virtual IteratorType end() = 0;
    virtual T operator[](size_t index) = 0;
    virtual size_t size() const = 0;
    virtual void clear() = 0;
};
