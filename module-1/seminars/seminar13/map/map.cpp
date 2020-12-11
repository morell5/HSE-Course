#include <cassert>
#include <iostream>
#include <string>

namespace my_std {

    template<typename Key, typename T>
    class map {
    public:

        enum Color {
            BLACK,
            RED
        };
        
        typedef Key key_type;
        typedef T mapped_type;
        typedef std::pair<key_type, mapped_type> value_type;

    public:

        map() { __init__(); }

        map(std::initializer_list<value_type> init) {
            __init__();
        }

        struct Node {
            value_type val;
            Node* left = nullptr;
            Node* right = nullptr;
            Node* parent = nullptr;
            Node* next = nullptr;
            Node* prev = nullptr;
            std::string name = "Node";

            Color color = BLACK;
            
            Node() = default;

            Node(value_type _val) :
                val(_val),
                left(nullptr),
                right(nullptr),
                parent(nullptr),
                next(nullptr),
                prev(nullptr),
                color(BLACK)
            {}

            virtual bool isLeaf() { return false; }
        };

        struct LeafNode: Node {
            LeafNode() : Node() {}

            bool isLeaf() override { return true; }
        };

        class iterator {
            public:

                iterator() = delete;
                iterator(Node* _ptr) : ptr(_ptr) {}
                
                iterator(const iterator& it) :
                    ptr(new Node(*(it.ptr))) 
                {   
                    std::cout << "iterator: copy" << std::endl;
                }

                iterator& operator++() {
                    ptr = ptr->next;
                    return *this;
                }

                iterator& operator--() {
                    ptr = ptr->prev;
                    return *this;
                }
                
                iterator operator++(int) {
                    iterator it(*this);
                    operator++();
                    return it;
                }

                iterator operator--(int) {
                    iterator it(*this);
                    operator--();
                    return it;
                }

                Node* operator->() const {
                    return ptr;
                }

                std::pair<Key, T>& operator*() const {
                    return ptr->val;
                }

                bool operator==(const iterator& rhs) const {
                    return rhs.ptr == ptr;
                }
                
                bool operator!=(const iterator& rhs) const {
                    return !(*this == rhs);
                }

            private:
                Node* ptr;
        };

        iterator find(const Key& key) {
            return __find__(root, key);
        }

        T& operator[](const Key& key) {
            std::pair<iterator, bool> p = insert(std::make_pair(key, T()));
            return p.first->val.second;
        }

       std::pair<iterator, bool> insert(const value_type& val) {
            Node* node = new Node(val);
            std::pair<iterator, bool> p = __recursive__insert__(root, node);
            if (p.second) { 
                __insert_repair__tree__(node);
                root = node;
                while (get_parent(root)) {
                    root = get_parent(root);
                }    
            } else {
                delete node;
            }
            return p;
        }
        
        iterator begin() { return iterator(head->next); }
        iterator end() { return iterator(tail); }

        std::size_t erase(const Key& key) {
            iterator it = find(key);
            if ( it == end() ) { return 0; }

            Node* substituted = max(it->left);
            it->val = substituted->val;

            __remove__one__child__node__(substituted);
            return 1;
        }

    private:
        Node* root;
        Node* head;
        Node* tail;
        Node* next;
        Node* prev;

    private:
        
        void __init__() {
            root = nullptr;
            head = new Node();
            head->name = "HEAD";
            tail = new Node(); 
            tail->name = "TAIL";

            head->next = tail;
            head->prev = tail;

            tail->next = head;
            tail->prev = head;
        }

        iterator __find__(Node* cur, const Key& key) {
            if (cur == nullptr) {
                return end();
            }
            
            if (cur->val.first == key) {
                return iterator(cur);
            } else if (key < cur->val.first) {
                return __find__(cur->left, key);
            } else {
                return __find__(cur->right, key);
            }
        }
    
        Node* get_parent(Node* node) {
            return  !node ? nullptr : node->parent;
        }

        Node* get_grandparent(Node* node) {
            return get_parent(get_parent(node));
        }

        Node* get_sibling(Node* node) {
            Node* parent = get_parent(node);
            if (!parent) {  return nullptr; }
            return  (parent->left == node) ? parent->right : parent->left;
        }

        Node* get_uncle(Node* node) {
            return get_sibling(get_parent(node));
        }

        void rotate_left(Node* node) {
            Node* new_node = node->right;
            Node* parent = get_parent(node);

            node->right = new_node->left;
            new_node->left = node;
            node->parent = new_node;

            if (node->right) {
                node->right->parent = node;
            }

            if (parent) {
                if (node == parent->left) {
                    parent->left = new_node;
                } else if (node == parent->right) {
                    parent->right = new_node;
                }
            }
            new_node->parent = parent;
        }

        void rotate_right(Node* node) {
            Node* new_node = node->left;
            Node* parent = get_parent(node);

            node->left = new_node->right;
            new_node->right = node;
            node->parent = new_node;

            if (node->left) {
                node->left->parent = node;
            }

            if (parent) {
                if (node == parent->left) {
                    parent->left = new_node;
                } else if (node == parent->right) {
                    parent->right = new_node;
                }
            }
            new_node->parent = parent;
        }
    
        std::pair<iterator, bool> __recursive__insert__(Node* cur, Node* node) {
            if (cur) {
                if (node->val.first < cur->val.first) {
                    if (cur->left->isLeaf()) {
                        cur->left = node;
                    } else {
                        return __recursive__insert__(cur->left, node);
                    }
                } else if (node->val.first > cur->val.first) {
                    if (cur->right->isLeaf()) {
                        cur->right = node;
                    } else {
                        return __recursive__insert__(cur->right, node);
                    }
                } else {
                    return std::make_pair(iterator(cur), false);
                }
            }

            node->parent = cur;
            node->left = new LeafNode();
            node->left->parent = node;
            node->right = new LeafNode();
            node->right->parent = node;
            node->color = RED;
            if (!node->parent) {
                tail->prev = node;
                head->next = node;
                node->next = tail;
                node->prev = head;
            } else {
                
                if (node->parent->val.first < node->val.first) {
                    Node* successor = node->parent;
                    while (successor != tail && successor->val.first < node->val.first) {
                        successor = successor->next;
                    }                
                    node->next = successor;
                    node->prev = successor->prev;
                    successor->prev = node;
                    node->prev->next = node;
                } 
                
                else {
                    Node* predecessor = node->parent;
                    while (predecessor != head && predecessor->val.first > node->val.first) {
                        predecessor = predecessor->prev;
                    }
                    node->next = predecessor->next;
                    node->prev = predecessor;
                    predecessor->next = node;
                    node->next->prev = node;
                }
            }
            return std::make_pair(iterator(node), true);
        }

        void __insert_repair__tree__(Node* node) {
            Node* parent = get_parent(node);
            Node* uncle = get_uncle(node);
            Node* grandparent = get_grandparent(node);

            if (!get_parent(node)) {
                node->color = BLACK;
            } else if (parent->color == BLACK) {

            } else if (uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                __insert_repair__tree__(grandparent);
            } else {
                
                
                node = __inside__node__(node);
                
                __outside__node__(node);
            }
        }

        Node* __inside__node__(Node* node) {
            Node* grandparent = get_grandparent(node);
            Node* parent = get_grandparent(node);
            if (grandparent->left == parent && parent->right == node) {
                rotate_left(parent);
                
                node = node->left;
            } else if (grandparent->right == parent && parent->left == node) {
                rotate_right(parent);
                
                node = node->right;
            }
            return node;
        }

        void __outside__node__(Node* node) {
            Node* grandparent = get_grandparent(node);
            Node* parent = get_parent(node);
            if (node == parent->left) {
                rotate_right(grandparent);
            } else {
                rotate_left(grandparent);
            }
            parent->color = BLACK;
            grandparent->color = RED;
        }

        Node* min(Node* node) {
            return (node->left->isLeaf()) ? node : min(node->left);
        }

        Node* max(Node* node) {
            return (node->right->isLeaf()) ? node : max(node->right);
        }
        
        void __replace__node__(Node* node, Node* child) {
            child->parent = node->parent;
            
            if (node->parent->left == node) {
                node->parent->left = child;
            } else {
                node->parent->right = child;
            }
        }

        void __remove__one__child__node__(Node* node) {
            assert(node->left->isLeaf() || node->right->isLeaf());
            Node* child = (node->left->isLeaf()) ? node->right : node->left;
            __replace__node__(node, child);
            if (node->color == BLACK) {
                if (child->color == RED) {
                    child->color = BLACK;
                } else {
                    __remove__repair__tree__(child);
                }
            }
            node->next->prev = node->prev;
            node->prev->next = node->next;

            delete node;
        }
            
        void __remove__repair__tree__(Node* node) {
            if (node->parent) {
                __remove__case2__(node);
            }
        }
        
        void __remove__case2__(Node* node) {
            Node* sibling = get_sibling(node);
            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                if (node == node->parent->left) {
                    rotate_left(node->parent);
                } else {
                    rotate_right(node->parent);
                }
            }
            __remove__case3__(node);
        }

        void __remove__case3__(Node* node) {
            Node* sibling = get_sibling(node);
            if (node->parent->color == BLACK && sibling->color == BLACK && sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                __remove__repair__tree__(node->parent);
            } else {
                __remove__case4__(node->parent);
            }
        }
        
        void __remove__case4__(Node* node) {
            Node* sibling = get_sibling(node);
            if (node->parent->color == RED && sibling->color == RED && sibling->left->color == BLACK && sibling->right->color == BLACK) {
                std::swap(node->parent->color, sibling->color);
            } else {
                __remove__case5__(node);
            }
        }

        void __remove__case5__(Node* node) {
            Node* sibling = get_sibling(node);
            if (sibling->color == BLACK) {
                sibling->color = RED;
                if (node == node->parent->left && sibling->right->color == BLACK && sibling->left->color == RED) {
                    sibling->color = RED;
                    sibling->left->color = BLACK;
                    rotate_right(sibling);
                } else if (node == node->parent->right && sibling->left->color == BLACK && sibling->right->color == RED) {
                    sibling->color = RED;
                    sibling->right->color = BLACK;
                    rotate_left(sibling);
                }
            }
            __remove__case6__(sibling);
        }

        void __remove__case6__(Node* node) {
            Node* sibling = get_sibling(node);

            sibling->color = node->parent->color;
            node->parent->color = BLACK;
            if (node->parent->left == node) {
                sibling->right->color == BLACK;
                rotate_left(node->parent);
            } else {
                sibling->left->color = BLACK;
                rotate_right(node->parent);
            }
        }
};
}

class IntWrapper {
public:
    IntWrapper() = default;
    IntWrapper(int _x) : x(_x) {}
    
    
    int get_int() const {  return x;  }
    
    friend bool operator<(const IntWrapper& lhs, const IntWrapper& rhs);

private:
    int x = -1;
};

bool operator<(const IntWrapper& lhs, const IntWrapper& rhs) {
    return lhs.x < rhs.x;
}

int main() {
    IntWrapper sample1(1);
    IntWrapper sample2(1);
    
    my_std::map<int, IntWrapper> a = {
        {0, sample1},
        {1, sample2}
    };
    
    a.insert(std::make_pair(0, 0));
    a.insert(std::make_pair(1, 1));
    a.insert(std::make_pair(2, 2));
    a.insert(std::make_pair(3, 3));
    a.insert(std::make_pair(4, 4));
    a.insert(std::make_pair(5, 5));
    a.insert(std::make_pair(6, 6));
    a.insert(std::make_pair(7, 7));
    
    for (auto it = a.begin(); it != a.end(); ++it) {
        std::cout << "val:" << it->val.first << std::endl;
    }

    std::cout << "num_erased:" << a.erase(3) << std::endl;

    for (auto it = a.begin(); it != a.end(); ++it) {
        std::cout << "val:" << it->val.first << std::endl;
    }
    return 0;
}