#include "list.h"
#include <vector>
#include <set>

namespace task{
    list& list::operator=(const task::list &other) {
        clear();
        auto tmp = other;
        while (tmp.head_ != tmp.tail_) {
            push_back(tmp.head_->val);
            tmp.head_ = tmp.head_->next;
        }
        push_back(tmp.head_->val);
        return *this;
    }

    list::list(const task::list& other) {
        size_ = 0;
        auto tmp = other.head_;
        while (tmp!= other.tail_) {
            push_back(tmp->val);
            tmp = tmp->next;
        }
        push_back(tmp->val);
    }

    list::list(task::list &&tmp) {
        size_ = tmp.size_;
        head_ = tmp.head_;
        tail_ = tmp.tail_;
        tmp.head_ = nullptr;
        tmp.tail_ = nullptr;
        tmp.size_ = 0;
    }

    list& list::operator=(task::list &&tmp) {
        clear();
        size_ = tmp.size_;
        head_ = tmp.head_;
        size_ = tmp.size_;
        tmp.head_ = nullptr;
        tmp.tail_ = nullptr;
        tmp.size_ = 0;
        return *this;
    }

    list::list() {
        size_ = 0;
        head_ = nullptr;
        tail_ = nullptr;
    }

    list::list(size_t count, const int &value) : size_(0){
        for (size_t i = 0; i < count; i++) {
            push_back(value);
        }
    }

    list::~list() {
        while (head_ != tail_) {
            ListNode* a = head_;
            head_ = head_->next;
            size_--;
            delete a;
        }
        delete head_;
    }

    const int& list::front() const {
        return head_->val;
    }

    int& list::front() {
        return head_->val;
    }

    const int& list::back() const {
        return tail_->val;
    }

    int& list::back() {
        return tail_->val;
    }

    bool list::empty() const {
        return size_ == 0;
    }

    size_t list::size() const {
        return size_;
    }


    void list::clear() {
        while (size_ != 0) {
            pop_back();
        }
    }

    void list::push_back(const int &value) {
        ListNode* a = new ListNode(value);
        a->prev = tail_;
        if (tail_ != nullptr) {
            tail_->next = a;
        }
        tail_ = a;
        if (size_ == 0) {
            head_ = a;
        }
        size_++;
    }

    void list::push_front(const int &value) {
        ListNode* a = new ListNode(0);
        a->val = value;
        a->next = head_;
        if (head_ != nullptr) {
            head_->prev = a;
        }
        head_ = a;
        if (size_ == 0) {
            tail_ = a;
        }
        size_++;
    }

    void list::pop_back() {
        ListNode* a = tail_;
        if (tail_->prev != nullptr) {
            tail_->prev->next = nullptr;
        }
        tail_ = tail_->prev;
        if (size_ == 1) {
            head_ = nullptr;
        }
        delete a;
        size_--;
    }

    void list::pop_front() {
        ListNode* a = head_;
        if (head_->next != nullptr) {
            head_->next->prev = nullptr;
        }
        head_ = head_->next;
        if (size_ == 1) {
            tail_ = nullptr;
        }
        delete a;
        size_--;
    }

    void list::resize(size_t count) {
        if (count > size_) {
            while (size_ != count) {
                push_back(0);
            }
        }
    }

    void list::sort() {
        ListNode* tmp = head_;
        std::vector<int> order;
        while (tmp != tail_) {
            order.push_back(tmp->val);
            tmp = tmp->next;
        }
        order.push_back(tail_->val);
        std::sort(order.begin(), order.end());
        size_t i = 0;
        tmp = head_;
        while (tmp != nullptr) {
            tmp->val = order[i];
            ++i;
            tmp = tmp->next;
        }
    }

    void list::remove_node_(task::ListNode *node) {
        auto tmp = head_;
        while (tmp != nullptr && tmp != node) {
            tmp = tmp->next;
        }

        if (tmp == head_ && tmp == tail_) {
            size_ = 0;
            head_ = nullptr;
            tail_ = nullptr;

            delete tmp;
            return;
        }

        if (tmp == head_) {
            auto next = head_->next;
            next->prev = nullptr;
            head_ = next;
        }  else {
            if (tmp == tail_) {
                auto prev = tail_->prev;
                prev->next = nullptr;
                tail_ = prev;
            } else {
                auto next = tmp->next;
                auto prev = tmp->prev;
                prev->next = next;
                next->prev = prev;
            }
        }

        size_--;
        delete tmp;
        return;
    }

    void list::swap(task::list &other) {
        std::swap(size_, other.size_);
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
    }


    void list::remove(const int value) {
        auto tmp = head_;
        while (tmp != nullptr) {
            if(tmp->val == value) {
                remove_node_(tmp);
                tmp = head_;
                continue;
            }
            tmp = tmp->next;
        }
    }

    void list::unique() {
        std::set<int> list_values;
        auto tmp = head_;
        while (tmp != nullptr) {
            if (list_values.find(tmp->val) != list_values.end()) {
                auto replace = tmp->prev;
                remove_node_(tmp);
                tmp = replace;
            } else {
                list_values.insert(tmp->val);
            }
            tmp = tmp->next;
        }
    }


}