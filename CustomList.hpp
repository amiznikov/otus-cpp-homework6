#pragma once
#include "./CustomIterator.hpp"
#include "./CustomContainer.hpp"
namespace list {
  template<typename T>
  struct Node {
    Node* next;
    Node* prev;
    T data;
  };

  template<typename T>
  class Iterator: public CustomIterator<T> {
  public:
    Iterator(Node<T>* node) : node_(node) {};
    T& operator*() override {
      return node_->data;
    }
    Iterator& operator++() override {
      node_ = node_->next;
      return *this;
    }
    bool operator!=(const CustomIterator<T>& other) override {
      const Iterator<T>* otherIterator = dynamic_cast<const Iterator<T>*>(&other);
      if (otherIterator) {
        return node_ != otherIterator->node_;
      }
      return true;
    }
  private:
    Node<T>* node_;
  };
}


template<typename T>
class CustomList: public CustomContainer<T, list::Iterator<T>> {
public:
  CustomList() = default;
  CustomList(const CustomList& list) {
    copy_from_other(list);
  }
  CustomList(CustomList&& list) {
    this->m_head = list.m_head;
    this->m_last = list.m_last;
    this->size_ = list.size_;
    list.m_head = nullptr;
    list.m_last = nullptr;
    list.size_ = 0;
  }
  CustomList& operator=(CustomList&& rhs) {
    CustomList tmp{std::move(rhs)};
    return *this = tmp;
  }
  CustomList& operator=(const CustomList& list) {
    copy_from_other(list);
    return *this;
  }
  ~CustomList() override {
    clear();
  }
  void clear() override {
    while (m_last != nullptr) {
      list::Node<T>* temp = m_last;
      m_last = m_last->prev;
      delete temp;
    }
    size_ = 0;
    m_head = nullptr;
    m_last = nullptr;
  }
  void push_back(T value) override {
    list::Node<T>* new_node = new list::Node<T>{};
    if (size_ > 0) {
      m_last->next = new_node;
      new_node->prev = m_last;
    } else {
      m_head = new_node;
      new_node->prev = nullptr;
    }
    new_node->next = nullptr;
    new_node->data = value; // сохраняем пользовательские данные
    m_last = new_node; // обновляем указатель на последний
    size_ += 1; // обновляем размер
  }
  void insert(T val, size_t index) override {
    if (index > size_) {
      return;
    }
    list::Node<T>* new_node = new list::Node<T>{};
    list::Node<T>* current = find_element(index);
    new_node->data = val;
    if (index == size_) {
      new_node->next = nullptr;
      new_node->prev = m_last;
      m_last->next = new_node;
      m_last = new_node;
    } else {
      new_node->next = current;
      if (current->prev) {
        new_node->prev = current->prev;
        current->prev->next = new_node;
        current->prev = new_node;
      }
      if (index == 0) {
        m_head = new_node;
      }
    }
    size_ += 1;
  }
  void erase(size_t index) override {
    if (index >= size_) {
      return;
    }
    list::Node<T>* current = find_element(index);
    if (index == 0) {
      current->next->prev = nullptr;
      m_head = current->next;
    } else {
      if (index == size_ - 1) {
        current->prev->next = nullptr;
        m_last = current->prev;
      } else {
        if (current->prev) {
          current->prev->next = current->next;
        }
        if (current->next) {
          current->next->prev = current->prev;
        }
      }
    }
    delete current;
    size_ -= 1;
  }
  list::Iterator<T> begin() override {
    return list::Iterator<T>{m_head};
  }
  list::Iterator<T> end() override {
    return list::Iterator<T>{nullptr};
  }
  T operator[](size_t index) override {
    const list::Node<T>* current = find_element(index);
    return current->data;
  }
  size_t size() const override {
    return size_;
  }
private:
  size_t size_ = 0;
  list::Node<T>* m_head = nullptr;
  list::Node<T>* m_last = nullptr;
  list::Node<T>* find_element(size_t index) {
    list::Node<T>* current = m_head;
    if (index == size_) {
      return nullptr;
    }
    for (size_t i = 0; i < index; i++) {
      if (current->next) {
        current = current->next;
      }
    }
    return current;
  }
  void copy_from_other(const CustomList& other) {
    list::Node<T>* current = other.m_head;
    while (current != nullptr) {
      push_back(current->data);
      current = current->next;
    }
  }
};
