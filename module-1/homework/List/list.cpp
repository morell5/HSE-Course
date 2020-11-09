#include "list.h"

// Constructors
task::list::list() : head(nullptr), tail(nullptr), m_size{0} {}
task::list::list(std::initializer_list<int> lst) : task::list() {
  for (const auto& element : lst) {
    push_back(element);
  }
}
task::list::list(size_t count, const int& value) : task::list() {
  // Just push values into list.
  for (size_t i = 0; i < count; i++) {
    push_back(value);
  }
}
task::list::list(const task::list& o) : task::list() {
  auto copy_pointer = o.head;
  while (copy_pointer != nullptr) {
    push_back(copy_pointer->data);
    copy_pointer = copy_pointer->next;
  }
}

// Destructor
task::list::~list() {
  clear();
  if (head != nullptr)
    delete head;
  if (tail != nullptr)
    delete tail;
}

task::list& task::list::operator=(const list& other) {
  clear();
  auto copy_pointer = other.head;
  while (copy_pointer != nullptr) {
    push_back(copy_pointer->data);
    copy_pointer = copy_pointer->next;
  }

  return *this;
}

// Properties
size_t task::list::size() const {
  return m_size;
}

bool task::list::empty() const {
  return m_size == 0;
}

void task::list::clear() {
  auto current = tail;
  while (current != nullptr) {
    auto subject = current;
    current = current->prev;

    if (subject->next != nullptr)
      delete subject->next;
  }

  delete head;
  head = nullptr;
  tail = nullptr;
  m_size = 0;
}

// Operations
void task::list::push_back(const int& value) {
  m_size++;

  // If there's no head, simply just create one.
  if (head == nullptr) {
    head = new Node(value);
    return;
  }

  // If there's no tail, create one and it's links to head and head to it.
  if (tail == nullptr) {
    tail = new Node(value);
    tail->prev = head;
    head->next = tail;
    return;
  }

  // Creating our new node.
  auto newbie = new Node(value);

  // Set a link from previous tail's next to our newbie.
  tail->next = newbie;
  // Counterwise.
  newbie->prev = tail;
  // Update the tail.
  tail = newbie;
}

void task::list::pop_back() {
  // To prevent segfault
  if (head == nullptr)
    return;

  // Decreasing size of the list
  m_size--;

  // If there is no tail, we'll just delete the head. (decapitate our list)
  if (tail == nullptr) {
    delete head;
    head = nullptr;
    return;
  }

  // Check the situation () <-> (). If we prefer using the code below, then
  // we'll get our head duplicated.
  if (tail->prev == head) {
    head->next = nullptr;
    delete tail;
    tail = nullptr;
    return;
  }

  // (1) <-> (2-newTail) <-> (3-last)
  // We delcare the tail of out list the node (2)
  // Remove link to (3) and then delete (3)
  // (1) <-> (2-newTail)
  auto prevous_tail = tail;
  tail = tail->prev;

  if (tail != nullptr)
    tail->next = nullptr;

  delete prevous_tail;
}

void task::list::push_front(const int& value) {
  // Increasing size of the list.
  m_size++;

  // Creating a head if it does not exist.
  if (head == nullptr) {
    head = new Node(value);
    return;
  }

  // If we have tail empty then we'll just swap head and tail so that former
  // head now is the tail and then just initialize current head.
  if (tail == nullptr) {
    std::swap(head, tail);
    head = new Node(value);

    tail->next = nullptr;
    tail->prev = head;
    head->next = tail;
    return;
  }

  // Just normally create node and mess with links
  auto newbie = new Node(value);
  newbie->next = head;
  head->prev = newbie;
  head = newbie;
}

void task::list::pop_front() {
  if (head == nullptr)
    return;

  m_size--;

  // If it's last node to remove
  if (tail == nullptr) {
    delete head;
    head = nullptr;
    return;
  }

  auto former_head = head;
  if (former_head->next == tail) {
    delete head;
    head = nullptr;

    std::swap(head, tail);
    head->prev = nullptr;
    head->next = nullptr;

    return;
  }

  head = former_head->next;
  if (head != nullptr)
    head->prev = nullptr;

  delete former_head;
}

// Remove one node. WE REQURE parameter's node to be part of our list as we are
// messing around our head and tail.
void task::list::_remove_node(task::list::Node*& node) {
  if (node == nullptr)
    return;

  m_size--;

  // Propagate links
  if (node->prev != nullptr)
    node->prev->next = node->next;
  if (node->next != nullptr)
    node->next->prev = node->prev;

  // Handling head
  if (node == head) {
    auto previous_head = head;
    if (head->next == tail) {
      delete head;
      head = nullptr;
      std::swap(head, tail);
      if (head != nullptr)
        head->prev = nullptr;
      return;
    }

    head = previous_head->next;

    if (head != nullptr)
      head->prev = nullptr;

    delete previous_head;
  } else if (node == tail) {
    auto previous_tail = tail;
    if (tail->prev == head) {
      delete tail;
      tail = nullptr;
      head->next = nullptr;
      return;
    }

    tail = previous_tail->prev;

    if (tail != nullptr)
      tail->next = nullptr;

    delete previous_tail;
  } else {
    delete node;
  }
}

// Just iterating thourgh and removing every
void task::list::remove(const int& value) {
  auto current = head;
  int val = value;
  while (current != nullptr) {
    auto check = current;
    current = current->next;
    if (check->data == val) {
      task::list::_remove_node(check);
    }
  }
}

// Just pushing back to fit > m_size to count
void task::list::resize(size_t count) {
  while (m_size > count)
    pop_back();
  while (m_size < count)
    push_back(0);
}

// Just swapping head, tail and size
void task::list::swap(list& o) {
  std::swap(head, o.head);
  std::swap(tail, o.tail);
  std::swap(m_size, o.m_size);
}

// Pretty awesome methods i hate that.
void task::list::sort() {
  if (head == nullptr || size() == 1)
    return;

  bool swapped;
  Node *lptr = nullptr, *rptr = nullptr;

  do {
    swapped = false;
    lptr = head;

    while (lptr->next != rptr) {
      if (lptr->data > lptr->next->data) {
        std::swap(lptr->data, lptr->next->data);
        swapped = true;
      }
      lptr = lptr->next;
    }
    rptr = lptr;
  } while (swapped);
}

void task::list::unique() {
  sort();
  auto current = head;

  // Simply eating cosecutive equal numbers leaving only one occurance.
  while (current != nullptr) {
    auto data = current->data;
    current = current->next;

    while (current != nullptr && current->data == data) {
      auto to_remove = current;
      current = current->next;
      _remove_node(to_remove);
    }
  }
}

/**
 * Access
 */
int& task::list::front() {
  if (head == nullptr)
    throw std::out_of_range(
        "Cannot get item from front because list is empty!");
  return head->data;
}

const int& task::list::front() const {
  if (head == nullptr)
    throw std::out_of_range(
        "Cannot get item from front because list is empty!");
  return head->data;
}

int& task::list::back() {
  if (tail == nullptr) {
    if (head != nullptr)
      return head->data;
    throw std::out_of_range("Cannot get item from back because list is empty!");
  }
  return tail->data;
}

const int& task::list::back() const {
  if (tail == nullptr) {
    if (head != nullptr)
      return head->data;
    throw std::out_of_range("Cannot get item from back because list is empty!");
  }
  return tail->data;
}