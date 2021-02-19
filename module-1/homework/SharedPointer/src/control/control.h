#pragma once

#include <atomic>


class shared_count {
protected:
    std::atomic<size_t> strong_count;

    virtual ~shared_count() {}
public:
    explicit shared_count(size_t count = 0) noexcept: strong_count(count) {}
    //delete copy
    shared_count(const shared_count& c) = delete;
    shared_count(shared_count&& c) = delete;

    void retain_shared() noexcept {
        strong_count.fetch_add(1);
    }

    bool release_shared() noexcept {
        if (strong_count.fetch_sub(1) == 0) {
            on_zero_shared();
            return true;
        }
        return false;
    }

    long use_count() const noexcept {
        return strong_count + 1;
    }

    virtual void on_zero_shared() noexcept = 0;
};

class shared_weak_count : public shared_count {
private:
    std::atomic<size_t> weak_count;

protected:
    virtual ~shared_weak_count() {}

public:
    //explicit shared_weak_count(size_t count = 1) noexcept: weak_count(count), shared_count(count) {}
    shared_weak_count(size_t weak = 1, size_t strong = 0) noexcept: weak_count(weak), shared_count(strong) {}

    shared_weak_count(const shared_weak_count& c) = delete;
    shared_weak_count(shared_weak_count&& c) = delete;


    void retain_weak() noexcept {
        weak_count.fetch_add(1);
    }

    void retain_shared() noexcept {
        shared_count::retain_shared();
    }

    void release_shared() noexcept {
        if (shared_count::release_shared()) {
            release_weak();
        }
    }

    void release_weak() noexcept {
        weak_count.fetch_sub(1);
    }

    long use_count() const noexcept {
        return shared_count::use_count();
    }

    virtual void on_zero_shared() noexcept = 0;

    virtual shared_weak_count* lock() = 0;
};

template<typename T>
struct __default_deleter {
    void operator()(T ptr) noexcept {
        delete ptr;
    }
};

template<typename T, typename Deleter=__default_deleter<T>>
class control_block : public shared_weak_count {
public:
    control_block(T _t): ptr(_t), deleter(__default_deleter<T>()) {}

    control_block(T _t, Deleter deleter): ptr(_t), deleter(deleter) {}

    control_block(const control_block<T, Deleter>& c) = delete;

    control_block(control_block<T, Deleter>&& c) = delete;

    void on_zero_shared() noexcept override {
        deleter(ptr);
    }

    shared_weak_count* lock() override {
        if (use_count() > 0) {
            control_block* res = new control_block(ptr, deleter);
            res->retain_shared();
            return res;
        }
        return nullptr;
    }

private:
    T ptr;
    Deleter deleter;
};
