#include "list.h"


task::list::list() {

}

task::list::list(size_t count, const int& value) {
	for (size_t i = 0; i < count; i++) {
		push_back(value);
	}
}

task::list::list(const task::list& other) {
	for (Node* cur = other.head; cur != nullptr; cur = cur->next) {
		push_back(cur->num);
	}
}

task::list::~list() {
	clear();
}

task::list& task::list::operator=(const task::list& other) {
	clear();
	for (Node* cur = other.head; cur != nullptr; cur = cur->next) {
		push_back(cur->num);
	}
	return *this;
}

int& task::list::front() {
	return head->num;
}

const int& task::list::front() const {
	return head->num;
}

int& task::list::back() {
	return tail->num;
}

const int& task::list::back() const {
	return tail->num;
}

bool task::list::empty() const {
	return len == 0;
}

size_t task::list::size() const {
	return len;
}

void task::list::clear() {
	while (!empty()) {
		pop_back();
	}
}

void task::list::push_back(const int& value) {
	if (tail) {
		tail->next = new Node{ value, tail, nullptr };
		tail = tail->next;
	}
	else {
		tail = head = new Node{ value, nullptr, nullptr };
	}
	len++;
}

void task::list::pop_back() {
	if (len > 1) {
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
	}
	else {
		delete head;
		tail = head = nullptr;
	}
	len--;
}

void task::list::push_front(const int& value) {
	if (head) {
		head->prev = new Node{ value, nullptr, head };
		head = head->prev;
	}
	else {
		head = tail = new Node{ value, nullptr, nullptr };
	}
	len++;
}

void task::list::pop_front() {
	if (len > 1) {
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
	}
	else {
		delete head;
		head = tail = nullptr;
	}
	len--;
}

void task::list::resize(size_t count) {
	while (len < count) {
		push_back(int());
	}
	while (len > count) {
		pop_back();
	}
}

void task::list::swap(task::list& other) {
	std::swap(len, other.len);
	std::swap(head, other.head);
	std::swap(tail, other.tail);
}

void task::list::remove(const int& value) {
	for (Node* cur = head; cur != nullptr; cur = cur->next) {
		if (cur->num == value) {
			if (cur->prev) {
				cur->prev->next = cur->next;
			}
			if (cur->next) {
				cur->next->prev = cur->prev;
			}
			if (cur == head) {
				head = cur->next;
			}
			if (cur == tail) {
				tail = cur->prev;
			}
			len--;
		}
	}
}

void task::list::unique() {
	for (Node* cur = head; cur != nullptr; cur = cur->next) {
		while (cur->next && cur->next->num == cur->num) {
			Node* del = cur->next;
			cur->next = del->next;
			delete del;
			len--;
		}
		if (cur->next) {
			cur->next->prev = cur;
		}
		else {
			tail = cur;
		}
	}
}

void task::list::sort() {
	for (size_t i = 0; i < len - 1; i++) {
		for (Node* cur = head; cur != tail; cur = cur->next) {
			if (cur->num > cur->next->num) {
				std::swap(cur->num, cur->next->num);
			}
		}
	}
}