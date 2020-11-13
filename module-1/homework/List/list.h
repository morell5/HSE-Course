#pragma once
#include <cstddef>
#include <utility>
#include <iostream>

namespace task {

struct Node {
  Node* next = nullptr;
  Node* prev = nullptr;
  int elem;
  Node() {
    this->elem = 0;
    this->next = nullptr;
    this->prev = nullptr;
  }
  explicit Node(const int& x) {
    this->elem = x;
    this->next = nullptr;
    this->prev = nullptr;
  }
};

class list {

 public:

  list();
  list(const list& other);
  explicit list(size_t count, const int& value = int());

  list& operator=(const list& other);

  ~list();

  int& front();
  [[nodiscard]] const int& front() const;

  int& back();
  [[nodiscard]] const int& back() const;


  [[nodiscard]] bool empty() const;
  [[nodiscard]] size_t size() const;
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

  void print();


 private:
  size_t length = 0;
  Node* head = nullptr;
  Node* tail = nullptr;

  static std::pair<Node*, Node*> qsort(std::pair<Node*, Node*> info);

};

}
