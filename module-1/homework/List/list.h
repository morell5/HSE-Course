#pragma once
#include <cstddef>
#include <iostream>

namespace task {

class list {
 public:
  list();
  list(size_t count, const int& value = int());
  list(std::initializer_list<int>);
  list(const list& other);

  ~list();
  list& operator=(const list& other);

  int& front();
  const int& front() const;

  int& back();
  const int& back() const;

  bool empty() const;
  size_t size() const;
  void clear();

  void push_back(const int& value);
  void pop_back();
  void push_front(const int& value);
  void pop_front();
  void resize(size_t count);
  void swap(list& other);

  void remove(const int& value);
  void unique();
  void sort();

  friend std::ostream& operator<<(std::ostream& o, task::list& l) {
    auto current = l.head;
    o << "list{size=" << l.m_size << ",nodes={";
    while (current != nullptr) {
      o << " {" << (current == l.head ? "$ " : "") << current->data
        << (current == l.tail || (current->next == nullptr && l.tail == nullptr)
                ? " #} "
                : "");

      if (current->next != nullptr)
        o << "} <->";
      current = current->next;
    }
    o << "}}";

    return o;
  }

 private:
  struct Node {
    Node(int data) : data(data), next(nullptr), prev(nullptr) {}
    Node(const Node& o) : data(o.data), next(o.next), prev(o.prev) {}
    ~Node() = default;

    Node& operator=(const Node& other) {
      data = other.data;
      next = other.next;
      prev = other.prev;

      return *this;
    }

    int data;
    Node* next;
    Node* prev;
  } * head, *tail;

  size_t m_size;

  // Remove node. Mess with links and free memory
  void _remove_node(Node*& node);
};

}  // namespace task
