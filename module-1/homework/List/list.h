#pragma once
#include <cstddef>


namespace task {

    class list {
    private:

        class Node {
        public:

            Node* next_node;
            Node* prev_node;

            int value;

        public:

            Node();
            Node(const int& value, Node* next = nullptr, Node* prev = nullptr);

            Node(const Node& node);

            ~Node();

        };

    public:

        list();
        list(size_t count, const int& value = int());
        list(const list& other);

        ~list();
        list& operator=(const list& other);


        int& front();
        const int& front() const;

        int& back();
        const int& back() const;


        bool empty() const;
        size_t size() const;
        void clear();


        void push_back(const int& value);
        void pop_back();
        void push_front(const int& value);
        void pop_front();
        void resize(size_t count);
        void swap(list& other);


        void remove(const int& value);
        void unique();
        void sort();

    private:

        Node* head;
        Node* tail;

        size_t sz;
        
        int count(const int& value) const;
    };

}  // namespace task