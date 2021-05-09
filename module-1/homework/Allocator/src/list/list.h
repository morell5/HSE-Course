#pragma once

#include <list>
#include <memory>
#include <type_traits>
#include <set>

namespace task
{

template <typename T, typename Allocator = std::allocator<T>>
class List
{
private:
    struct Node;
    class Iterator;

public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using iterator = Iterator;
    using const_iterator = const Iterator;
    using reverse_iterator = std::reverse_iterator<Iterator>;
    using const_reverse_iterator = std::reverse_iterator<const Iterator>;

    // Special member functions
    List()
    {
    };

    List(const List& other)
    {
//        alloc_ = other.alloc_.select_on_container_copy_construction();
        alloc_ = other.alloc_;
        for (Node* e = other.first_; e != nullptr; e = e->next)
        {
            PushBack(e->value);
        }
    }

    List(const List& other, const Allocator& alloc);

    List(List&& other);
    List(List&& other, const Allocator& alloc);

    ~List();

    List& operator=(const List& other);

    List& operator=(List&& other) noexcept;

    // Element access
    reference Front();
    const_reference Front() const;
    reference Back();
    const_reference Back() const;

    // Iterators
    iterator Begin() noexcept;
    const_iterator Begin() const noexcept;

    iterator End() noexcept;
    const_iterator End() const noexcept;

    // Capacity
    bool Empty() const noexcept;

    size_type Size() const noexcept;
    size_type MaxSize() const noexcept;

    // Modifiers
    void Clear();
    void Swap(List& other) noexcept;

    void PushBack(const T& value);
    void PushBack(T&& value);

    template <typename... Args>
    void EmplaceBack(Args&&... args);
    void PopBack();
    void PushFront(const T& value);
    void PushFront(T&& value);
    template <typename... Args>
    void EmplaceFront(Args&&... args);
    void PopFront();

    void Resize(size_type count);

    // Operations
    void Remove(const T& value);
    void Unique();
    void Sort();

    allocator_type GetAllocator() const noexcept;

private:
    struct Node
    {
        Node* prev;
        Node* next;
        value_type value;

        Node(Node* prev, Node* next, const_reference value)
            : prev(prev), next(next), value(value)
        {
        }
    };

    typedef typename std::allocator_traits<Allocator>::template rebind_alloc<Node> node_alocator;

    node_alocator alloc_;
    Node* first_ = nullptr;
    Node* last_ = nullptr;

    class Iterator
    {
    public:
        using value_type = List::value_type;
        using pointer = List::pointer;
        using reference = List::reference;
        using difference_type = ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

        Iterator() = delete;
        explicit Iterator(Node* node, bool end = false)
            : node_(node), end_(end)
        {
        }

        Iterator& operator++()
        {
            if (node_->next == nullptr)
            {
                end_ = true;
            }
            else
            {
                node_ = node_->next;
            }
            return *this;
        }

        Iterator& operator--()
        {
            if (!end_)
            {
                node_ = node_->prev;
            }
            end_ = false;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator it(*this);
            operator++();
            return it;
        }

        Iterator operator--(int)
        {
            Iterator it(*this);
            operator--();
            return it;
        }

        pointer operator->() const
        {
            if (end_)
            {
                throw std::runtime_error("End iterator");
            }
            return &node_->value;
        }

        reference operator*() const
        {
            if (end_)
            {
                throw std::runtime_error("End iterator");
            }
            return node_->value;
        }

        bool operator==(const Iterator& other)
        {
            return node_ == other.node_ && end_ == other.end_;
        }

        bool operator!=(const Iterator& other)
        {
            return !(*this == other);
        }

    private:
        Node* node_;
        bool end_;
    };
};

template <typename T, typename Allocator>
List<T, Allocator>::List(const List& other, const Allocator& alloc)
{
    alloc_ = alloc;
    for (Node* e = other.first_; e != nullptr; e = e->next)
    {
        PushBack(e->value);
    }
}

template <typename T, typename Allocator>
List<T, Allocator>::List(List&& other)
{
    *this = std::move(other);
}

template <typename T, typename Allocator>
List<T, Allocator>::List(List&& other, const Allocator& alloc)
{
    alloc_ = alloc;
    for (Node* e = other.first_; e != nullptr; e = e->next)
    {
        PushBack(std::move(e->value));
    }
    other.Clear();
}


template <typename T, typename Allocator>
List<T, Allocator>::~List()
{
    Clear();
}

template <typename T, typename Allocator>
List<T, Allocator>& List<T, Allocator>::operator=(const List& other)
{
    if (this == &other)
    {
        return *this;
    }

    Clear();
    if (std::allocator_traits<allocator_type>::propagate_on_container_copy_assignment::value)
    {
        alloc_ = other.alloc_;
    }

    for (Node* e = other.first_; e != nullptr; e = e->next)
    {
        PushBack(e->value);
    }

    return *this;
}

template <typename T, typename Allocator>
List<T, Allocator>& List<T, Allocator>::operator=(List&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    Clear();

    if (std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value)
    {
        alloc_ = other.alloc_;

        first_ = other.first_;
        last_ = other.last_;

        other.first_ = nullptr;
        other.last_ = nullptr;
    }
    else
    {
        for (Node* e = other.first_; e != nullptr; e = e->next)
        {
            PushBack(std::move(e->value));
        }
        other.Clear();
    }

    return *this;
}

template <typename T, typename Allocator>
typename List<T, Allocator>::reference List<T, Allocator>::Front()
{
    return first_->value;
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_reference List<T, Allocator>::Front() const
{
    return first_->value;
}

template <typename T, typename Allocator>
typename List<T, Allocator>::reference List<T, Allocator>::Back()
{
    return last_->value;
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_reference List<T, Allocator>::Back() const
{
    return last_->value;
}

template <typename T, typename Allocator>
bool List<T, Allocator>::Empty() const noexcept
{
    return first_ == nullptr;
}

template <typename T, typename Allocator>
size_t List<T, Allocator>::Size() const noexcept
{
    size_t count = 0;
    Node* e = first_;
    while (e != nullptr) {
        ++count;
        e = e->next;
    }
    return count;
}

template <typename T, typename Allocator>
void List<T, Allocator>::Clear()
{
    while (!Empty())
    {
        PopBack();
    }
}

template <typename T, typename Allocator>
void List<T, Allocator>::PushBack(const_reference value)
{
    Node* e = alloc_.allocate(1);
    alloc_.construct(e, last_, nullptr, value);

    if (last_ != nullptr)
    {
        last_->next = e;
    }
    last_ = e;
    if (first_ == nullptr)
    {
        first_ = e;
    }
}

template <typename T, typename Allocator>
void List<T, Allocator>::PushBack(T&& value)
{
    Node* e = alloc_.allocate(1);
    alloc_.construct(e, last_, nullptr, std::move(value));

    if (last_ != nullptr)
    {
        last_->next = e;
    }
    last_ = e;
    if (first_ == nullptr)
    {
        first_ = e;
    }
}

template <typename T, typename Allocator>
template <typename... Args>
void List<T, Allocator>::EmplaceBack(Args&&... args)
{
     Node* e = alloc_.allocate(1);
    alloc_.construct(e, last_, nullptr, std::forward<Args>(args)...);

    if (last_ != nullptr)
    {
        last_->next = e;
    }
    last_ = e;
    if (first_ == nullptr)
    {
        first_ = e;
    }
}

template <typename T, typename Allocator>
void List<T, Allocator>::PopBack()
{
    if (last_ == nullptr)
    {
        return;
    }

    Node* e = last_;
    last_ = e->prev;
    if (last_ != nullptr)
    {
        last_->next = nullptr;
    }
    else
    {
        first_ = nullptr;
    }

    alloc_.destroy(e);
    alloc_.deallocate(e, 1);
}

template <typename T, typename Allocator>
void List<T, Allocator>::PushFront(const_reference value)
{
    Node* e = alloc_.allocate(1);
    alloc_.construct(e, nullptr, first_, value);

    if (first_ != nullptr)
    {
        first_->prev = e;
    }
    first_ = e;
    if (last_ == nullptr)
    {
        last_ = e;
    }
}

template <typename T, typename Allocator>
void List<T, Allocator>::PushFront(T&& value)
{
    Node* e = alloc_.allocate(1);
    alloc_.construct(e, nullptr, first_, std::move(value));

    if (first_ != nullptr)
    {
        first_->prev = e;
    }
    first_ = e;
    if (last_ == nullptr)
    {
        last_ = e;
    }
}

template <typename T, typename Allocator>
template <typename... Args>
void List<T, Allocator>::EmplaceFront(Args&&... args)
{
     Node* e = alloc_.allocate(1);
    alloc_.construct(e, nullptr, first_, std::forward<Args>(args)...);

    if (first_ != nullptr)
    {
        first_->prev = e;
    }
    first_ = e;
    if (last_ == nullptr)
    {
        last_ = e;
    }
}

template <typename T, typename Allocator>
void List<T, Allocator>::PopFront()
{
    if (first_ == nullptr)
    {
        return;
    }

    Node* e = first_;
    first_ = e->next;
    if (first_ != nullptr)
    {
        first_->prev = nullptr;
    }
    else
    {
        last_ = nullptr;
    }

    alloc_.destroy(e);
    alloc_.deallocate(e, 1);
}

template <typename T, typename Allocator>
void List<T, Allocator>::Resize(size_type count)
{
    size_type size = Size();
    if (size < count)
    {
        for (size_type i = 0; i < count - size; ++i)
        {
            PushBack(T());
        }
    }
    else
    {
        for (size_type i = 0; i < size - count; ++i)
        {
            PopBack();
        }
    }
}

template <typename T, typename Allocator>
void List<T, Allocator>::Swap(List& other) noexcept
{
    if (&other == this)
    {
        return;
    }

    if (std::allocator_traits<allocator_type>::propagate_on_container_swap::value)
    {
        std::swap(alloc_, other.alloc_);
        std::swap(first_, other.first_);
        std::swap(last_, other.last_);
    }
    else
    {
        List temp = std::move(other);
        other = std::move(*this);
        *this = std::move(temp);
    }
}

template <typename T, typename Allocator>
void List<T, Allocator>::Remove(const_reference value)
{
    Node* e = first_;

    while (e != nullptr)
    {
        Node* next;

        if (e->value != value)
        {
            next = e->next;
        }
        else
        {
            if (e->prev != nullptr)
            {
                e->prev->next = e->next;
            }
            if (e->next != nullptr)
            {
                e->next->prev = e->prev;
            }
            if (e == first_)
            {
                first_ = e->next;
            }
            if (e == last_)
            {
                last_ = e->prev;
            }

            next = e->next;

            alloc_.destroy(e);
            alloc_.deallocate(e, 1);
        }

        e = next;
    }
}

template <typename T, typename Allocator>
void List<T, Allocator>::Unique()
{
    Node* e = first_;
    std::set<T> els;

    while (e != nullptr)
    {
        Node* next;

        if (els.find(e->value) == els.end())
        {
            els.insert(e->value);
            next = e->next;
        }
        else
        {
            e->prev->next = e->next;
            if (e->next != nullptr)
            {
                e->next->prev = e->prev;
            }
            if (e == first_)
            {
                first_ = e->next;
            }
            if (e == last_)
            {
                last_ = e->prev;
            }

            next = e->next;

            alloc_.destroy(e);
            alloc_.deallocate(e, 1);
        }

        e = next;
    }
}

template <typename T, typename Allocator>
void List<T, Allocator>::Sort()
{
    size_type size = Size();
    for (size_type i = 0; i < size; ++i)
    {
        Node* e = first_;

        for (size_type j = 0; j < size - i - 1; ++j, e = e->next)
        {
            if (e->value > e->next->value)
            {
                std::swap(e->value, e->next->value);
            }
        }
    }
}

template <typename T, typename Allocator>
typename List<T, Allocator>::iterator List<T, Allocator>::Begin() noexcept
{
    return iterator(first_, first_ == nullptr);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_iterator List<T, Allocator>::Begin() const noexcept
{
    return const_iterator(first_, first_ == nullptr);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::iterator List<T, Allocator>::End() noexcept
{
    return iterator(last_, true);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_iterator List<T, Allocator>::End() const noexcept
{
    return const_iterator(last_, true);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::allocator_type List<T, Allocator>::GetAllocator() const noexcept
{
    return Allocator(alloc_);
}

}  // namespace task
