# SharedPointer

## Задание

Реализовать control_block в `control.h`
* без аллокатора
* счетчик ссылок
    
    ```c++
    std::atomic<std::size_t>
    ```

Написать класс [shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr)

Реализовать:
* **Special member functions**

    ```c++
    constexpr shared_ptr() noexcept = default;

    template<typename Y>
    shared_ptr(Y* p);

    template<typename Y, typename Deleter>
    shared_ptr(Y* p, Deleter deleter) noexcept;

    shared_ptr(const shared_ptr& other) noexcept;

    shared_ptr(shared_ptr&& other) noexcept;

    shared_ptr& operator=( const shared_ptr& r ) noexcept;

    template<typename Y>
    shared_ptr& operator=( const shared_ptr<Y>& r ) noexcept;

    shared_ptr& operator=( shared_ptr&& r ) noexcept;

    template<typename Y>
    shared_ptr& operator=( shared_ptr<Y>&& r ) noexcept;

    ~shared_ptr();
    ```

* **Modifiers**

    ```c++
    void reset() noexcept;

    template<typename Y>
    void reset(Y* p) noexcept;

    template<typename Y, typename Deleter>
    void reset(Y*p, Deleter deleter) noexcept;

    void swap(shared_ptr& other) noexcept;
    ```

* **Observers**

    ```c++
    T* get() const noexcept;

    long use_count() const noexcept;

    T& operator*() const noexcept;

    T* operator->() const noexcept;

    element_type& operator[](std::ptrdiff_t idx) const;

    explicit operator bool() const noexcept;
    ```


Написать класс [weak_ptr](https://en.cppreference.com/w/cpp/memory/weak_ptr)

Реализовать:
* **Special member functions**

    ```c++
    constexpr weak_ptr() noexcept = default;
    
    template<typename Y>
    weak_ptr(const shared_ptr<Y>& other);
    
    weak_ptr(const weak_ptr& other) noexcept;
    
    weak_ptr(weak_ptr&& other) noexcept;
    
    template<typename Y>
    weak_ptr& operator=(const shared_ptr<Y>& other);
    
    weak_ptr& operator=(const weak_ptr& other) noexcept;
    
    weak_ptr& operator=(weak_ptr&& other) noexcept;

    ~weak_ptr();
    ```

* **Modifiers**

    ```c++
    void reset() noexcept;
    void swap(weak_ptr<T>& other) noexcept;
    ```

* **Observers**

    ```c++
    bool expired() noexcept;
    shared_ptr<T> lock() const noexcept;
    ```