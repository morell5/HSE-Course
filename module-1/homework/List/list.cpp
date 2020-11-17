#include "list.h"

task::list::list() {

}
int& task::list::front() {
	int a = 0;
	if (!num) a;
	return be.p->value;
}
const int& task::list::front() const {
	int a = 0;
	if (!num) a;
	return be.p->value;
}
int& task::list::back() {
	int a = 0;
	if (!num) a;
	return be.n->value;
}
const int& task::list::back() const {
	int a = 0;
	if (!num) a;
	return be.n->value;
}

bool task::list::empty() const {
	return (num == 0) ? true : false;
}

size_t task::list::size() const {
	return num;	
}

void task::list::clear() {
  while (!task::list::empty()) task::list::pop_back();
}

void task::list::push_back(const int& value) {
	if (num == 0) {
		element* pb = new element{ value, pb, pb };
		be.n = pb;
		be.p = pb;
	}
	else{
		element* pb = new element{ value, be.n, be.p };
		be.n = pb;
		be.n->p->n = be.n;
	}
	num++;
}

void task::list::pop_back() {
	if (num == 1){
		delete be.n;
		num=0;
	}
	if (num > 1){
		element* a = be.n->p;
		delete be.n;
		be.n = a;
		be.p->p = a;
		num--;
	}
}

void task::list::push_front(const int& value) {
	if (num==0){
		element* pb = new element{ value, pb, pb };
		be.p = pb;
		be.n = pb;
	}
	else {
		element* pb = new element{ value, be.n, be.p };
		be.p = pb;
		be.p->n->p = be.p;
	}
	num++;
}

void task::list::pop_front() {
	if (num == 1){
		delete be.n;
		num=0;
	}
	else if (num > 0){
		element* a = be.p->n;
		delete be.p;
		be.p = a;
		be.n->n = a;
		num--;
	}
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
	bool nul = false;
  if (task::list::empty()){
	   this->push_back(0);
	   nul = true;
	}
  list x;
  x = other;
  other = *this;
  *this = x;
  if (nul) other.pop_back();
}

task::list::~list() {
	task::list::clear();
}

 task::list& task::list::operator=(const list& other) {
	task::list::clear();
	element * c = other.be.p;
	for(int i = 0; i < other.num; i++) {
		this->push_back(c->value);
		c=c->n;
	} 
	return *this;
}

void task::list::remove(const int& value) {
	int k;
	int mvalue = value;
	k = this->size();
	for(int i = 0; i < k; i++){
		const int g = this->front();
		if (g == mvalue){
			this->pop_front();
		}
		else{
			this->push_back(g);
			this->pop_front();
		}
	}
}

void task::list::unique() {
	if (this->empty()) return;
	task::list x;
	x.push_front(this->front());
	this->pop_front();
	while (!task::list::empty()){
		if (this->front() == x.back()){
			this->pop_front();
		}
		else{
			x.push_back(this->front());
			this->pop_front();
		}
	}
	x.push_back(2);
	x.push_back(2);
	this->push_back(1);
	*this = x;
	this->pop_back();
	this->pop_back();
}

void task::list::sort() {
	bool don = true;
	while (don){
		don = false;
		element* s = be.p;
		while (s != be.n){
			if (s->n->value<s->value){
				int g = s->value;
				s->value = s->n->value;
				s->n->value = g;
				don = true;
			}
			s=s->n;
		}
	}
}

task::list::list(size_t count, const int& value) {
	while (num < (int)count) {
		push_back(value);
	}
}

task::list::list(const list& other) : list() {
	*this = other;
}
