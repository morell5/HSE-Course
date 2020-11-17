#pragma once

#include <cstddef>


namespace task {
    class list {
    private:
        struct node {
            node(int value, node *p = nullptr, node *n = nullptr);

            int value;
            node *prev = nullptr;
            node *next = nullptr;
        };

        node *begin = nullptr;
        node *end = nullptr;
        size_t size_ = 0;

        static node *sort_move_node(node *from, node *dest);

        static void swap(node *&first, node *&second);

        static void merge_sort(node *&l, node *&r, size_t size);

    public:

        list() = default;

        list(list const &other);

        list(size_t count, const int &value = int());

        ~list();

        list &operator=(const list &other);

        int &front();

        const int &front() const;

        int &back();

        const int &back() const;

        bool empty() const;

        size_t size() const;

        void clear();

        void push_back(const int &value);

        void pop_back();

        void push_front(const int &value);

        void pop_front();

        void resize(size_t count);

        void swap(list &other);

        void remove(int value);

        void unique();

        void sort();
    };

}  // namespace task