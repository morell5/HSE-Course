# SharedPointer

## Task

Implement `ControlBlock` in the `control.h`
* with reference counting
* without allocator
    
    ```c++
    std::atomic<std::size_t>
    ```

For the class [SharedPtr](https://en.cppreference.com/w/cpp/memory/shared_ptr)

You should implement the following operations:
* **Special member functions**

    ```c++
    constexpr SharedPtr() noexcept = default;

    template<typename Y>
    SharedPtr(Y* p);

    template<typename Y, typename Deleter>
    SharedPtr(Y* p, Deleter deleter) noexcept;

    SharedPtr(const SharedPtr& other) noexcept;

    SharedPtr(SharedPtr&& other) noexcept;

    SharedPtr& operator=( const SharedPtr& r ) noexcept;

    template<typename Y>
    SharedPtr& operator=( const SharedPtr<Y>& r ) noexcept;

    SharedPtr& operator=( SharedPtr&& r ) noexcept;

    template<typename Y>
    SharedPtr& operator=( SharedPtr<Y>&& r ) noexcept;

    ~SharedPtr();
    ```

* **Modifiers**

    ```c++
    void Reset() noexcept;

    template<typename Y>
    void Reset(Y* p) noexcept;

    template<typename Y, typename Deleter>
    void Reset(Y*p, Deleter deleter) noexcept;

    void Swap(SharedPtr& other) noexcept;
    ```

* **Observers**

    ```c++
    T* Get() const noexcept;

    long UseCount() const noexcept;

    T& operator*() const noexcept;

    T* operator->() const noexcept;

    element_type& operator[](std::ptrdiff_t idx) const;

    explicit operator bool() const noexcept;
    ```


For the class [WeakPtr](https://en.cppreference.com/w/cpp/memory/weak_ptr)

You should implement:
* **Special member functions**

    ```c++
    constexpr WeakPtr() noexcept = default;
    
    template<typename Y>
    WeakPtr(const SharedPtr<Y>& other);
    
    WeakPtr(const WeakPtr& other) noexcept;
    
    WeakPtr(WeakPtr&& other) noexcept;
    
    template<typename Y>
    WeakPtr& operator=(const SharedPtr<Y>& other);
    
    WeakPtr& operator=(const WeakPtr& other) noexcept;
    
    WeakPtr& operator=(WeakPtr&& other) noexcept;

    ~WeakPtr();
    ```

* **Modifiers**

    ```c++
    void Reset() noexcept;
    void Swap(WeakPtr<T>& other) noexcept;
    ```

* **Observers**

    ```c++
    bool Expired() noexcept;
    SharedPtr<T> Lock() const noexcept;
    ```