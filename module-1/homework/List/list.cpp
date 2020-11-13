#include "list.h"

task::list::list() {
  this->length = 0;
  this->head = this->tail = nullptr;
}

const int &task::list::front() const {
  return this->head->elem;
}
const int &task::list::back() const {
  return this->tail->elem;
}

int &task::list::front() {
  return this->head->elem;
}

int &task::list::back() {
  return this->tail->elem;
}

bool task::list::empty() const {
  return this->length == 0;
}

size_t task::list::size() const {
  return this->length;
}

void task::list::push_back(const int &value) {
  Node* q = new Node(value);
  ++this->length;
  if (this->tail) {
    this->tail->next = q;
    q->prev = this->tail;
    this->tail = q;
  } else {
    this->head = this->tail = q;
  }
}

void task::list::pop_back() {
  Node* q = this->tail;
  this->tail = this->tail->prev;
  --this->length;
  if (this->tail) {
    this->tail->next = nullptr;
  }
  if (this->length == 0) {
    this->head = this->tail = nullptr;
  }
  delete q;
}

void task::list::push_front(const int &value) {
  Node* q = new Node(value);
  ++this->length;
  if (this->head) {
    q->next = this->head;
    this->head->prev = q;
    this->head = q;
  } else {
    this->head = this->tail = q;
  }
}

void task::list::pop_front() {
  Node* q = this->head;
  this->head = this->head->next;
  if (this->head) {
    this->head->prev = nullptr;
  }
  delete q;
  --this->length;
  if (this->length == 0) {
    this->head = this->tail = nullptr;
  }
}

void task::list::resize(size_t count) {
  if (count == this->length) {
    return;
  } else if (count > this->length) {
    size_t to = count - this->length;
    for (size_t i = 0; i < to; ++i) {
      this->push_back(0);
    }
  } else {
    size_t to = this->length - count;
    for (size_t i = 0; i < to; ++i) {
      this->pop_back();
    }
  }
}

void task::list::swap(task::list &other) {
  std::swap(this->head, other.head);
  std::swap(this->tail, other.tail);
  std::swap(this->length, other.length);
}

void task::list::clear() {
  while (!this->empty()) {
    this->pop_back();
  }
}

void task::list::remove(const int &value) {
  int remove_value = value;
  for (Node* q = this->head; q != nullptr; ) {
    if (q->elem == remove_value) {
      Node* tmp = q;
      if (q->prev) {
        q->prev->next = q->next;
      }
      if (q->next) {
        q->next->prev = q->prev;
      }
      q = q->next;
      if (tmp == this->head) {
        this->head = q;
      } else if (tmp == this->tail) {
        this->tail = this->tail->prev;
      }
      --this->length;
      if (this->length == 0) {
        this->tail = nullptr;
      }
      delete tmp;
    } else {
      q = q->next;
    }
  }
}

void task::list::unique() {
  if (this->length <= 1) {
    return;
  }
  for (Node* q = this->head->next; q != nullptr; ) {
    Node* prev = q->prev;
    if (q->elem == prev->elem) {
      Node* tmp = q;
      prev->next = q->next;
      if (q->next) {
        q->next->prev = prev;
      }
      if (q == this->tail) {
        this->tail = q->prev;
      }
      q = q->next;
      delete tmp;
      --this->length;
    } else {
      q = q->next;
    }
  }
}

std::pair<task::Node*, task::Node*> task::list::qsort(std::pair<Node*, Node*> info) {
  if (info.first == info.second) {
    return info;
  }
  Node* equal = info.first;
  Node* smaller = nullptr;
  Node* bigger = nullptr;
  int pivot = equal->elem;
  Node * last_smaller = nullptr, * last_equal = equal, * last_bigger = nullptr;
  for (Node * p = equal->next; ; p = p->next) {
    if (p->elem == pivot) {
      last_equal->next = p;
      last_equal = last_equal->next;
    } else if (p->elem < pivot) {
      if (last_smaller) {
        last_smaller->next = p;
        last_smaller = last_smaller->next;
      } else {
        smaller = last_smaller = p;
      }
    } else {
      if (last_bigger) {
        last_bigger->next = p;
        last_bigger = last_bigger->next;
      } else {
        bigger = last_bigger = p;
      }
    }
    if (p == info.second) {
      break;
    }
  }
  Node* first = equal;
  Node* last = last_equal;
  if (last_smaller) {
    std::pair<task::Node*, task::Node*> res = qsort(std::make_pair(smaller, last_smaller));
    smaller = res.first;
    last_smaller = res.second;
    last_smaller->next = equal;
    first = smaller;
  }
  if (last_bigger) {
    std::pair<task::Node*, task::Node*> res = qsort(std::make_pair(bigger, last_bigger));
    bigger = res.first;
    last_bigger = res.second;
    last = last_bigger;
  }
  last_equal->next = bigger;
  return std::make_pair(first, last);
}

void task::list::sort() {
  if (this->length == 1)
    return;
  std::pair<Node*, Node*> result = qsort(std::make_pair(this->head, this->tail));
  this->head = result.first;
  this->tail = result.second;
  Node* prev = this->head;
  this->tail->next = nullptr;
  this->head->prev = nullptr;
  for (Node* q = this->head->next; q != nullptr; q = q->next) {
    q->prev = prev;
    prev = prev->next;
  }
}

task::list::~list() {
  this->clear();
}

task::list &task::list::operator=(const task::list &other) {
  if (this == &other) {
    return *this;
  }
  this->resize(other.size());
  int ccc = 0;
  for (Node* q = this->head, * p = other.head; q != nullptr; q = q->next, p = p->next) {
    ++ccc;
    q->elem = p->elem;
  }
  return *this;
}

task::list::list(const task::list &other) {
  *this = other;
}

task::list::list(size_t count, const int &value) {
  for (size_t i = 0; i < count; ++i) {
    this->push_back(value);
  }
}

void task::list::print() {
  Node* q = this->head;
  int len = this->length;
  while (len--) {
    std::cout << q->elem << ' ';
    q = q->next;
  }
  std::cout << '\n';
}
