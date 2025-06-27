#pragma once
#include "./CustomContainer.hpp"
namespace forward_list {
  template<typename T>
  struct Node {
    Node* next;
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
class CustomForwardList: public CustomContainer<T, forward_list::Iterator<T>> {
public:
  CustomForwardList() = default;
  CustomForwardList(const CustomForwardList& list) {
    if (&list != this) {
      copy_from_other(list);
    }
  }
  CustomForwardList& operator=(const CustomForwardList& list) {
    if (&list != this) {
      copy_from_other(list);
    }
    return *this;
  }
  CustomForwardList(CustomForwardList&& list) {
    this->m_head = list.m_head;
    this->m_last = list.m_last;
    this->size_ = list.size_;
    list.m_head = nullptr;
    list.m_last = nullptr;
    list.size_ = 0;
  }
  CustomForwardList& operator=(CustomForwardList&& rhs) {
    CustomForwardList tmp{std::move(rhs)};
    return *this = tmp;
  }
  ~CustomForwardList() override {
    clear();
  }
  void clear() override {
    while (m_head != nullptr) {
      forward_list::Node<T>* temp = m_head;
      m_head = m_head->next;
      delete temp;
    }
    size_ = 0;
    m_head = nullptr;
    m_last = nullptr;
  }
  void push_back(T value) override {
    forward_list::Node<T>* new_node = new forward_list::Node<T>{};
    new_node->next = nullptr;
    new_node->data = value; // сохраняем пользовательские данные
    if (size_ == 0) {
      m_head = new_node;
    } else {
      if (!m_last) {
        m_last = new_node;
        m_head->next = m_last;
      } else {
        m_last->next = new_node;
        m_last = new_node;
      }

    }
    size_ += 1; // обновляем размер
  }
  void insert(T val, size_t index) override {
    if (index > size_) {
      return;
    }
    forward_list::Node<T>* new_node = new forward_list::Node<T>{};
    forward_list::Node<T>* current = find_element(index);
    forward_list::Node<T>* previous = nullptr;
    if (index > 0) {
      previous = find_element(index - 1);
    }
    new_node->data = val;
    if (!current) {
      m_last -> next = new_node;
      m_last = new_node;
    }
    if (!previous) {
      new_node->next = m_head;
      m_head = new_node;
    }
    if (current && previous) {
      new_node->next = current;
      previous->next = new_node;
    }
    size_ += 1;
  }
  void erase(size_t index) override {
    if (index >= size_) {
      return;
    }
    forward_list::Node<T>* current = find_element(index);
    forward_list::Node<T>* previous = nullptr;
    if (index > 0) {
      previous = find_element(index - 1);
    }
    if (index == 0) {
      m_head = current->next;
    } else {
      if (previous) {
        previous->next = current->next;
      }
    }
    delete current;
    size_ -= 1;
  }
  forward_list::Iterator<T> begin() override {
    return forward_list::Iterator<T>{m_head};
  }
  forward_list::Iterator<T> end() override {
    return forward_list::Iterator<T>{nullptr};
  }
  T operator[](size_t index) override {
    const forward_list::Node<T>* current = find_element(index);
    return current->data;
  }
  size_t size() const override {
    return size_;
  }
private:
  size_t size_ = 0;
  forward_list::Node<T>* m_last = nullptr;
  forward_list::Node<T>* m_head = nullptr;
  forward_list::Node<T>* find_element(size_t index) {
    forward_list::Node<T>* current = m_head;
    if (index == size_) {
      return nullptr;
    }
    for (size_t i = 0; i < index; ++i) {
      if (current->next) {
        current = current->next;
      }
    }
    return current;
  }
  void copy_from_other(const CustomForwardList& other) {
    forward_list::Node<T>* current = other.m_head;
    while (current != nullptr) {
      push_back(current->data);
      current = current->next;
    }
  }
};

