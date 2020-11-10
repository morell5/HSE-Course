#include "List.h"


task::list::list() {

}

int& task::list::front() {
	
	if (!num) be.value;
	return be.p->value;
}

int& task::list::back() {
	if (!num) be.value;
	return be.n->value;
}

bool task::list::empty() const {
	return (num == 0) ? true : false;
}

size_t task::list::size() const {
	return num;	
}

void task::list::clear() {
	if (!num) return;
	element* a;
	a = be.p->n;
	while (!empty() && be.n != be.p) {
		a = be.p->n;
		delete be.p;
		be.p = a;
	}
	if (be.n == be.p) {
		delete be.n;
	}
	num = 0;
}

void task::list::push_back(const int& value) {
	if (num == 0) {
		element* pb = new element{ value, pb, pb };
		be.n = pb;
		be.p = pb;
		num++;
	}
	else{
		element* pb = new element{ value, be.n, be.p };
		be.n = pb;
		be.n->p->n = be.n;
		num++;
	}
}

void task::list::pop_back() {
	if (num > 0){
		element* a = be.n->p;
		delete be.n;
		*be.n = *a;
		delete a;
		num--;
	}
}

void task::list::push_front(const int& value) {
	if (num==0){
		element* pb = new element{ value, pb, pb };
		be.p = pb;
		be.n = pb;
		num++;
	}
	else {
		element* pb = new element{ value, be.n, be.p };
		be.n = pb;
		be.p->n->p = be.p;
		num++;
	}
}

void task::list::pop_front() {
	element* a = be.p->n;
	delete be.p;
	*be.p = *a;
	delete a;
	num--;
}

void task::list::resize(size_t count) {
	if (num < (int)count) {
		while (num != count) {
			task::list::push_back(0);
		}
	}
	else {
		while (num != count) {
			task::list::pop_back();
		}
	}
}

void task::list::swap(list& other) {
	list b = other;
	other.be = this->be;
	this->be = b.be;
}

task::list::~list() {
	task::list::clear();
}

 task::list& task::list::operator=(const list& other) {
	clear();
	element * b = other.be.n;
	element * c = other.be.p;
	do {
		this->push_back(c->value);
		c=c->n;
	} while (b != c);
	delete c,b;
	return *this;
}

void task::list::remove(const int& value) {
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

void task::list::unique() {
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

void task::list::sort() {
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

task::list::list(size_t count, const int& value) {
	while (num < (int)count) {
		push_back(value);
	}
}
