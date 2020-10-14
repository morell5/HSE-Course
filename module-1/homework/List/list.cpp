#include "list.h"

namespace task {

	list::Node::Node() {
		this->value = 0;
		this->next_node = nullptr;
		this->prev_node = nullptr;
		return;
	}

	list::Node::Node(const int& value, Node* next, Node* prev) {
		this->value = value;
		this->next_node = next;
		this->prev_node = prev;
		return;
	}

	list::Node::Node(const Node& node) = default;

	list::Node::~Node() = default;

	list::list() {
		this->sz = 0;
		this->head = new Node;
		this->tail = this->head;
	}

	list::list(const list& other) {
		int n = static_cast<int>(other.size());
		this->sz = n;
		Node* curr = other.head;
		this->head = new Node;
		this->tail = this->head;
		for (int i = 0; i < n; i++) {
			if (this->empty()) {
				Node* new_node = new Node(curr->value);
				new_node->next_node = this->tail;
				new_node->prev_node = nullptr;
				this->tail->prev_node = new_node;
				this->head = new_node;
				curr = curr->next_node;
				continue;
			}
			Node* new_node = new Node(curr->value);
			new_node->next_node = this->tail;
			new_node->prev_node = this->tail->prev_node;
			this->tail->prev_node->next_node = new_node;
			this->tail->prev_node = new_node;
			curr = curr->next_node;
		}
	}

	list::list(size_t count, const int& value) {
		this->sz = count;
		this->head = new Node;
		this->tail = this->head;
		for (int i = 0; i < static_cast<int>(count); i++) {
			if (this->empty()) {
				Node* node_to_add = new Node(value);
				node_to_add->next_node = this->tail;
				node_to_add->prev_node = nullptr;
				this->tail->prev_node = node_to_add;
				this->head = node_to_add;
				continue;
			}
			Node* node_to_add = new Node(value);
			node_to_add->next_node = this->tail;
			node_to_add->prev_node = this->tail->prev_node;
			this->tail->prev_node->next_node = node_to_add;
			this->tail->prev_node = node_to_add;
		}
	}

	list::~list() {
		Node* node_to_delete = this->head;
		for (Node* sn = this->head; sn != this->tail; ) {
			sn = sn->next_node;
			delete node_to_delete;
			node_to_delete = sn;
		}
		delete node_to_delete;
	}

	list& list::operator = (const list& other) {
		this->clear();
		int n = static_cast<int>(other.size());
		if (n == 0) {
			return *this;
		}
		Node* curr_node = other.head;
		this->sz = n;
		for (int i = 0; i < n; i++) {
			Node* node_to_add = new Node(curr_node->value);
			curr_node = curr_node->next_node;
			if (this->empty()) {
				node_to_add->next_node = this->head;
				node_to_add->prev_node = nullptr;
				this->head->prev_node = node_to_add;
				this->head = node_to_add;
				continue;
			}
			node_to_add->next_node = this->tail;
			node_to_add->prev_node = this->tail->prev_node;
			this->tail->prev_node->next_node = node_to_add;
			this->tail->prev_node = node_to_add;
		}
		return (*this);
	}

	int& list::front() {
		return this->head->value;
	}

	const int& list::front() const {
		return this->head->value;
	}

	int& list::back() {
		return this->tail->prev_node->value;
	}

	const int& list::back() const {
		return this->tail->prev_node->value;
	}

	bool list::empty() const {
		return this->tail == this->head;
	}

	size_t list::size() const {
		return this->sz;
	}

	void list::clear() {
		this->sz = 0;
		Node* node_to_delete = this->head;
		for (Node* sn = this->head; sn != this->tail; ) {
			sn = sn->next_node;
			delete node_to_delete;
			node_to_delete = sn;
		}
		delete node_to_delete;
		node_to_delete = nullptr;
		this->head = new Node;
		this->tail = this->head;
	}

	void list::push_back(const int& value) {
		this->sz += 1;
		if (this->head == this->tail) {
			Node* node_to_add = new Node(value);
			node_to_add->next_node = this->head;
			this->head->prev_node = node_to_add;
			this->head = node_to_add;
		}
		else {
			Node* node_to_add = new Node(value);
			node_to_add->next_node = this->tail;
			node_to_add->prev_node = this->tail->prev_node;
			this->tail->prev_node->next_node = node_to_add;
			this->tail->prev_node = node_to_add;
		}
		return;
	}

	void list::pop_back() {
		if (this->empty()) {
			return;
		}
		this->sz--;
		if (this->size() == 0) {
			this->clear();
			return;
		}
		Node* node_to_delete = this->tail->prev_node;
		this->tail->prev_node = node_to_delete->prev_node;
		node_to_delete->prev_node->next_node = this->tail;
		node_to_delete->next_node = nullptr;
		node_to_delete->prev_node = nullptr;
		delete node_to_delete;
	}

	void list::push_front(const int& value) {
		if (this->head == this->tail) {
			this->push_back(value);
			return;
		}
		this->sz += 1;
		Node* node_to_add = new Node(value);
		node_to_add->next_node = this->head;
		this->head->prev_node = node_to_add;
		this->head = node_to_add;
	}

	void list::pop_front() {
		if (this->empty()) {
			return;
		}
		this->sz--;
		if (this->sz == 0) {
			this->clear();
			return;
		}
		Node* node_to_delete = this->head;
		this->head = this->head->next_node;
		this->head->prev_node = nullptr;
		node_to_delete->next_node = nullptr;
		delete node_to_delete;
	}

	void list::resize(size_t count) {
		if (this->size() <= count) {
			int n = static_cast<int>(count - this->size());
			for (int i = 0; i < n; i++) {
				this->push_back(0);
			}
			return;
		}
		else {
			int n = static_cast<int>(this->size() - count);
			for (int i = 0; i < n; i++) {
				this->pop_back();
			}
			return;
		}
	}

	int list::count(const int& value) const {
		if (this->empty()) {
			return 0;
		}
		int res = 0;
		int n = static_cast<int>(this->size());
		Node* curr = this->head;
		for (int i = 0; i < n; i++) {
			if (curr->value == value) {
				res++;
			}
			curr = curr->next_node;
		}
		return res;
	}

	void list::swap(list& other) {
		Node* node_left_head = this->head;
		Node* node_left_tail = this->tail;
		Node* node_right_head = other.head;
		Node* node_right_tail = other.tail;

		int dust_sz = this->sz;
		this->sz = other.sz;
		other.sz = dust_sz;

		this->head = node_right_head;
		this->tail = node_right_tail;
		other.head = node_left_head;
		other.tail = node_left_tail;

	}

	void list::remove(const int& value) {
		int tmp = value;
		if (!this->count(value)) {
			return;
		}
		int n = static_cast<int>(this->size());
		Node* curr_node = this->head;
		for (int i = 0; i < n; i++) {
			if (curr_node->value != tmp) {
				curr_node = curr_node->next_node;
				continue;
			}
			if (curr_node == this->head) {
				curr_node = curr_node->next_node;
				this->pop_front();
				continue;
			}
			this->sz--;
			Node* node_to_delete = curr_node;
			curr_node = curr_node->next_node;
			node_to_delete->prev_node->next_node = curr_node;
			curr_node->prev_node = node_to_delete->prev_node;
			node_to_delete->next_node = nullptr;
			node_to_delete->prev_node = nullptr;
			delete node_to_delete;
		}
	}

	void list::unique() {
		if (this->empty()) {
			return;
		}
		int n = static_cast<int>(this->size());
		Node* curr_node = this->head;
		Node* curr_node_next = curr_node->next_node;
		while (curr_node_next != this->tail) {
			if (curr_node->value != curr_node_next->value) {
				curr_node = curr_node_next;
				curr_node_next = curr_node_next->next_node;
				continue;
			}
			this->sz--;
			Node* node_to_delete = curr_node_next;
			curr_node->next_node = curr_node_next->next_node;
			curr_node_next->next_node->prev_node = curr_node;
			curr_node_next = curr_node_next->next_node;
			node_to_delete->next_node = nullptr;
			node_to_delete->prev_node = nullptr;
			delete node_to_delete;

		}
	}

	void list::sort() {
		if (this->empty() || this->size() == 1) {
			return;
		}
		int n = static_cast<int>(this->size());
		for (int i = 0; i < n; i++) {
			Node* curr_node = this->head;
			Node* curr_next_node = this->head->next_node;
			while (curr_next_node != this->tail) {
				if (curr_node->value > curr_next_node->value) {
					int val = curr_next_node->value;
					curr_next_node->value = curr_node->value;
					curr_node->value = val;
				}
				curr_node = curr_next_node;
				curr_next_node = curr_next_node->next_node;
			}
		}
	}
}