#include "list.h"
#include <set>

using namespace task;

void list::out() {
	node* element = this->first_element;
	for (element; element != nullptr; element = element->next_element) {
		std::cout << element->value << ' ';
	}
	std::cout << std::endl;
}

node::node() {
	this->back_element = nullptr;
	this->next_element = nullptr;
	this->value = 0;
}

list::list() {
	this->size_list = 0;
	this->first_element = nullptr;
	this->last_element = &this->main_element;
}

list::list(int value) {
	this->size_list = 1;
	this->first_element = nullptr;
	this->last_element = &this->main_element;
	push_back(value);
}

list::list(size_t count, const int& value) {
	this->size_list = 0;
	this->first_element = nullptr;
	this->last_element = &this->main_element;
	node* element = &this->main_element;
	while (this->size_list != count) {
		this->push_back(value);
	}
}

list::~list() {
	this->clear();
	this->first_element = nullptr;
	this->last_element = nullptr;
	this->size_list = 0;

}

list::list(const list& other) {
	*this = other;
}

list& list::operator=(const list& other) {
	this->clear();
	node* element = other.first_element;
	for (element; element != nullptr; element = element->next_element) {
		this->push_back(element->value);
	}
	return *this;
}

int& list::front() {
	return this->first_element->value;
}

const int& list::front() const {
	return this->first_element->value;
}

int& list::back() {
	return this->last_element->value;
}

const int& list::back() const {
	return this->last_element->value;
}

bool list::empty() {
	return !bool(this->size_list);
}

size_t list::size() {
	return this->size_list;
}

void list::clear() {
	while (this->main_element.next_element != nullptr) {
		this->pop_back();
	}
	this->first_element = nullptr;
	this->last_element = &this->main_element;
}

void list::push_back(const int& value) {
	this->last_element->next_element = new node;
	this->last_element->next_element->back_element = this->last_element;
	this->last_element->next_element->value = value;
	this->size_list++;
	if (this->size_list == 1) {
		this->first_element = this->last_element->next_element;
	}
	this->last_element = this->last_element->next_element;
	
}

void list::pop_back() {
	this->size_list--;
	this->last_element = this->last_element->back_element;
	delete this->last_element->next_element;
	this->last_element->next_element = nullptr;
	this->first_element = this->main_element.next_element;
}

void list::push_front(const int& value) {
	this->size_list++;
	this->main_element.next_element = new node;
	this->main_element.next_element->back_element = &this->main_element;
	this->main_element.next_element->value = value;
	if (this->first_element != nullptr) {
		this->main_element.next_element->next_element = this->first_element;
		this->first_element->back_element = this->main_element.next_element;
	}
	else {
		this->last_element = this->main_element.next_element;
	}
	this->first_element = this->main_element.next_element;
}

void list::pop_front() {
	this->size_list--;
	if (this->size_list == 0) {
		this->last_element = &this->main_element;
	}
	this->main_element.next_element = this->first_element->next_element;
	delete this->first_element;
	this->first_element = this->main_element.next_element;
	if (this->first_element != nullptr) {
		this->first_element->back_element = &this->main_element;
	}

}

void list::resize(size_t count) {
	clear();
	const int value = 0;
	node* element = &this->main_element;
	while (this->size_list != count) {
		this->push_back(value);
	}
}

void list::swap(list& other) {
	int* arr_this = new int[this->size_list + 100];
	int* arr_other = new int[other.size_list + 100];
	int n_this = this->size_list;
	int n_other = other.size_list;
	node* element = this->main_element.next_element;
	int i;
	for (i = 0, element; element != nullptr; element = element->next_element, i++) {
		arr_this[i] = element->value;
	}
	element = other.main_element.next_element;
	for (i = 0, element; element != nullptr; element = element->next_element, i++) {
		arr_other[i] = element->value;
	}
	this->clear();
	other.clear();
	for (i = 0; i < n_this; i++) {
		other.push_back(arr_this[i]);
	}
	for (i = 0; i < n_other; i++) {
		this->push_back(arr_other[i]);
	}
	delete[] arr_this;
	delete[] arr_other;

}

void list::remove(const int& value) {
	int value_1 = value;
	node* element = this->first_element;
	this->last_element = &this->main_element;
	node* for_del;
	while (element != nullptr) {
		if (element->value == value_1) {
			this->size_list--;
			this->last_element = element->back_element;
			element->back_element->next_element = element->next_element;
			if (element->next_element != nullptr) {
				element->next_element->back_element = element->back_element;
			}
			for_del = element;
			element = element->next_element;
			delete for_del;
		}
		else {
			this->last_element = element;
			element = element->next_element;
		}
	}
	this->first_element = this->main_element.next_element;
}

void list::unique() {
	int* arr = new int[this->size_list + 1];
	node* element = this->first_element;
	int i;
	for (i = 0, element; element != nullptr; element = element->next_element, i++) {
		arr[i] = element->value;
	}
	int n = this->size_list;
	this->clear();
	for (i = 0; i < n; i++) {
		if (i == 0 || arr[i] != arr[i - 1]) {
			push_back(arr[i]);
		}
	}
	delete[] arr;
}

void list::sort() {
	int* arr = new int[this->size_list + 1];
	node* element = this->first_element;
	int i, j, n = this->size_list;
	for (i = 0, element; element != nullptr; element = element->next_element, i++) {
		arr[i] = element->value;
	}
	for (i = 0; i < n; i++) {
		for (j = n - 1; j > i; j--) {
			if (arr[j - 1] > arr[j]) {
				std::swap(arr[j - 1], arr[j]);
			}
		}
	}
	clear();
	for (i = 0; i < n; i++) {
		this->push_back(arr[i]);
	}
	delete[] arr;
}




