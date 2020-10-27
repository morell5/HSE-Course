#include "List.h"

list::list() {
	be.n = &be;
	be.p = &be;
}

int& list::front() {
	return be.p->value;
}

int& list::back() {
	return be.n->value;
}

bool list::empty() const {
	return (num == 0) ? true : false;
}

size_t list::size() const {
	return num;	
}

void list::clear() {
	element* a = be.p->n;
	while (!empty() && be.n != be.p) {
		a = be.p->n;
		delete be.p;
		be.p = a;
	}
	if (be.n == be.p) {
		delete &be;
	}
	num = 0;
	delete a;
}

void list::push_back(const int& value) {
	element pb{ value, be.n, be.p };
	*be.n = pb;
	*be.n->p->n = *be.n;
	num++;
}

void list::pop_back() {
	element* a = be.n->p;
	delete be.n;
	*be.n = *a;
	delete a;
	num--;
}

void list::push_front(const int& value) {
	element pb{ value, be.n, be.p };
	*be.p = pb;
	*be.p->n->p = *be.p;
	num++;
}

void list::pop_front() {
	element* a = be.p->n;
	delete be.p;
	*be.p = *a;
	delete a;
	num--;
}

void list::resize(size_t count) {
	if (num < (int)count) {
		while (num != count) {
			list::push_back(0);
		}
	}
	else {
		while (num != count) {
			list::pop_back();
		}
	}
}

void list::swap(list& other) {
	list b = other;
	other.be = this->be;
	this->be = b.be;
}

list::~list() {
	list::clear();
}

list& list::operator=(list& other) {
	return other;
}

void list::remove(const int& value) {
	element* s = be.p->n;
	while (s != be.p) {
		if (s->value == value) {
			*s->p->n = *s->n;
			*s->n->p = *s->p;
		}
		element* r = s->n;
		delete s;
		s = r;
		delete r;
	}
	delete s;
}

void list::unique() {
	element* s = be.p->n;
	while (s != be.p) {
		if (s->value == s->n->value) {
			*s->p->n = *s->n;
			*s->n->p = *s->p;
		}
		element* r = s->n;
		delete s;
		s = r;
		delete r;
	}
	delete s;
}

void list::sort() {
	bool don = false;
		while (don == false) {
		don = true;
		element s1;
		element* s = &s1;
		*s = *be.p->n;
		while (s != be.p) {
			element* s1 = s->n;
			if (s->value < s->n->value) {
				*s->n = *s;
				*s = *s1;
				don = false;
			}
			delete s;
			s = s1;
			delete s1;
		}
	}
}

list::list(size_t count, const int& value) {
	while (num < (int)count) {
		push_back(value);
	}
}

int main() {
	list qwe;
	qwe.push_back(1);
	std::cout << qwe.front();
}