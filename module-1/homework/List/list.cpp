#include "list.h"
using namespace task;


element::element(const int& value) {
	previous = nullptr;
	next = nullptr;
	this->value = value;
}
element::~element() {
	previous = nullptr;
	next = nullptr;
	//deleted element
}

list::list() {
	length = 0;
	beg = end = nullptr;
}
list::list(size_t count, const int& value) {
	length = 0;
	beg = end = nullptr;
	for (size_t i = 0; i < count; ++i) {
		push_back(value);
	}
}
list::list(const list& other) {
	beg = end = nullptr;
	length = 0;
	size_t cnt = 0;
	for (element* it = other.beg; cnt < other.size(); cnt++) {
		push_back(it->value);
		it = it->next;
	}
}

list::~list() {
	clear();
	delete beg;
	delete end;
	//destroyed list
}
list& list::operator=(const list& other) {
	clear();
	size_t cnt = 0;
	for (element* it = other.beg; cnt < other.size(); cnt++) {
		push_back(it->value);
		it = it->next;
	}
	length = other.size();
	return *this;
}


int& list::front() {
	return beg->value;
}
const int& list::front() const {
	return beg->value;
}

int& list::back() {
	return end->value;
}
const int& list::back() const {
	return end->value;
}

bool list::empty() const {
	return (int)this->size() == 0;
}
size_t list::size() const {
	return this->length;
}
void list::clear() {
	size_t cnt = 0;
	for (element* it = beg; cnt < length; cnt++) {
		element* cur = it;
		it = it->next;
		list::delete_element(cur);
	}

	length = 0;
	beg = end = nullptr;
}

void list::push_back(const int& value) {
	length++;
	element* cur = new element(value);
	if (end == nullptr) {
		end = cur;
		if (end->previous != nullptr) end->previous->next = end;
		if (beg == nullptr) beg = end;
	}
	else {
		if (beg == end) {
			end = cur;
			beg->next = end;
			end->previous = beg;
		}
		else {
			end->next = cur;
			cur->previous = end;
			end = cur;
		}
	}
}
void list::pop_back() {
	//assert !empty();
	if (end == nullptr) return;//out of range
	length--;
	if (end != beg) {
		element* prev = end->previous;
		list::delete_element(end);
		end = prev;
	}
	else {
		delete end;
		beg = end = nullptr;
	}
}
void list::push_front(const int& value) {
	length++;
	element* cur = new element(value);
	if (beg == nullptr) {
		beg = cur;
		if (beg->next != nullptr) beg->next->previous = beg;
		if (end == nullptr) end = beg;
	}
	else {
		if (beg == end) {
			beg = cur;
			beg->next = end;
			end->previous = beg;
		}
		else {
			beg->previous = cur;
			cur->next = beg;
			beg = cur;
		}
	}
}
void list::pop_front() {
	//assert !empty();
	if (beg == nullptr) return;//out of range
	length--;
	if (end != beg) {
		element* nx = beg->next;
		list::delete_element(beg);
		beg = nx;
	}
	else {
		delete beg;
		beg = end = nullptr;
	}
}
void list::resize(size_t count) {
	while (length < count) {
		push_back(0);
	} 
	while (length > count) {
		pop_back();
	}
}
void list::swap(list& other) {
	std::swap(this->beg, other.beg);
	std::swap(this->end, other.end);
	std::swap(this->length, other.length);
}
void list::delete_element(element* a) {
	if (a == nullptr) return;
	if (a->previous != nullptr) {
		if (a->next != nullptr) {
			a->previous->next = a->next;
			a->next->previous = a->previous;
		}
		else {
			a->previous->next = nullptr;
		}
	}
	else {
		if (a->next != nullptr) {
			a->next->previous = nullptr;
		}
		else {

		}
	}
	if (a == beg && a == end) {
		beg = end = nullptr;
	}
	else if (a == beg) {
		if (a->next != nullptr) beg = a->next;
		else beg = nullptr;
	}
	else if (a == end) {
		if (a->previous != nullptr) end = a->previous;
		else end = nullptr;
	}
	delete a;
}

void list::remove(const int& value) {
	size_t cnt = 0;
	int cnt_deleted = 0;
	int val = value;
	for (element* it = beg; cnt < length; cnt++) {
		element* cur = it;
		it = it->next;
		if (cur->value == val) {
			list::delete_element(cur);
			cnt_deleted++;
		}
	}
	length -= cnt_deleted;
}
void list::unique() {
	if (length == 0) return;
	size_t cnt = 1;
	int cnt_deleted = 0;
	int last = beg->value;
	for (element* it = beg->next; cnt < length; cnt++) {
		element* cur = it;
		it = it->next;
		if (cur->value == last) {
			list::delete_element(cur);
			cnt_deleted++;
		}
		else {
			last = cur->value;
		}
	}
	length -= cnt_deleted;
}
void list::sort() {
	if (empty() || length == 1) return;
	bool ok = true;
	element* l = nullptr, * r = nullptr;
	while (ok) {
		ok = false;
		l = beg;
		while (l->next != r) {
			if (l->value > l->next->value) {
				std::swap(l->value, l->next->value);
				ok = true;
			}
			l = l->next;
		}
		r = l;
	}
}
void list::print() {
	size_t cnt = 0;
	for (element* it = beg; cnt < length; cnt++) {
		std::cout << it->value << ' ';
		it = it->next;
	}
	std::cout << std::endl;
}