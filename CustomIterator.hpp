#pragma once

template<typename T>
class CustomIterator {
  public:
    virtual ~CustomIterator() = default;
    virtual T& operator*() = 0;
    virtual CustomIterator& operator++() = 0;
    virtual bool operator!=(const CustomIterator<T>& other) = 0;
    // virtual CustomIterator& operator--() = 0;
};