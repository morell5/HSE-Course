#include <cstdlib>
#include <type_traits>

#pragma once

namespace task {

struct nullopt_t {
    explicit constexpr nullopt_t(int) {}
};

constexpr nullopt_t nullopt = nullopt_t{0}; // Your code goes here;

template<class T>
struct in_place_type_t {
    explicit in_place_type_t() = default;
};

template<class T>
constexpr in_place_type_t<T> in_place_type{};

struct in_place_t {
    explicit in_place_t() = default;
};

constexpr in_place_t in_place = in_place_t{}; // Your code goes here;

template<typename T, bool>
class optional_destruct_helper {
public:
    constexpr optional_destruct_helper() : isEngaged(false) {}

    constexpr optional_destruct_helper(nullopt_t) : isEngaged(false) {}

    template<class... _Args>
    constexpr optional_destruct_helper(in_place_t, _Args&& ... __args): value(std::forward<_Args>(__args)...),
                                                                        isEngaged(true) {}

    template<class U = T>
    constexpr optional_destruct_helper(U&& value): value(std::forward<U>(value)), isEngaged(true) {}

protected:
    void _reset() {
        isEngaged = false;
    }

    template<class U = T>
    void setValue(U&& value) {
        this->value = std::forward<U>(value);
        isEngaged = true;
    }


    union {
        T value;
        char __nullValue;
    };

    bool isEngaged;
};

template<typename T>
class optional_destruct_helper<T, false> {
public:
    constexpr optional_destruct_helper() : isEngaged(false) {}

    constexpr optional_destruct_helper(nullopt_t) : isEngaged(false) {}

    template<class... _Args>
    constexpr optional_destruct_helper(in_place_t, _Args&& ... __args):
            value(std::forward<_Args>(__args)...),
            isEngaged(true) {}

    template<class U = T>
    constexpr optional_destruct_helper(U&& value):
            value(std::forward<U>(value)),
            isEngaged(true) {}


    ~optional_destruct_helper() {
        if (this->isEngaged) {
            value.~T();
        }
    }

protected:
    void _reset() {
        if (this->isEngaged) {
            value.~T();
        }
        isEngaged = false;
    }

    template<class U = T>
    void setValue(U&& value) {
        if (this->isEngaged) {
            this->value.~T();
        }
        this->value = std::forward<U>(value);
        isEngaged = true;
    }

    union {
        T value;
        char __nullValue;
    };

    bool isEngaged;
};

template<typename T>
class optional : public optional_destruct_helper<T, std::is_trivially_destructible_v<T>> {
private:
    using base = optional_destruct_helper<T, std::is_trivially_destructible<T>::value>;
public:

    using value_type = T;

    constexpr optional() noexcept;

    template<class U = value_type>
    constexpr optional(U&& value);

    constexpr optional(nullopt_t) noexcept;

    template<class... _Args>
    constexpr explicit optional(in_place_t, _Args&& ... __args);

    optional& operator=(nullopt_t) noexcept;

    template<class U = T>
    optional& operator=( U&& value );

    void reset() noexcept;

    template<typename U>
    constexpr T value_or(U&& default_value) const&;

    template<typename U>
    constexpr T value_or(U&& default_value)&&;

    constexpr bool has_value() const noexcept;

    constexpr explicit operator bool() const noexcept;

    constexpr std::add_pointer_t<const value_type> operator->() const;

    constexpr std::add_pointer_t<value_type> operator->();

    constexpr const value_type& operator*() const&;

    constexpr value_type& operator*()&;

    constexpr const value_type&& operator*() const&&;

    constexpr value_type&& operator*()&&;
};
} // task namespace

template<typename T>
constexpr task::optional<T>::optional() noexcept: base() {}

template<typename T>
template<class U>
constexpr task::optional<T>::optional(U&& value): base(std::forward<U>(value)) {}

template<typename T>
constexpr task::optional<T>::optional(nullopt_t) noexcept: base(nullopt) {}

template<typename T>
template<class... _Args>
constexpr task::optional<T>::optional(in_place_t, _Args&& ... __args): base(in_place, __args...) {}

template<typename T>
template<typename U>
constexpr T task::optional<T>::value_or(U&& default_value) const& {
    return this->has_value() ? this->value : default_value;
}

template<typename T>
template<typename U>
constexpr T task::optional<T>::value_or(U&& default_value)&& {
    return this->has_value() ? this->value : default_value;
}

template<typename T>
constexpr bool task::optional<T>::has_value() const noexcept {
    return this->isEngaged;
}

template<typename T>
constexpr task::optional<T>::operator bool() const noexcept {
    return this->has_value();
}

template<typename T>
constexpr std::add_pointer_t<const typename task::optional<T>::value_type> task::optional<T>::operator->() const {
    return &(this->value);
}

template<typename T>
constexpr std::add_pointer_t<typename task::optional<T>::value_type> task::optional<T>::operator->() {
    return &(this->value);
}

template<typename T>
constexpr const typename task::optional<T>::value_type& task::optional<T>::operator*() const& {
    return (this->value);
}

template<typename T>
constexpr typename task::optional<T>::value_type& task::optional<T>::operator*()& {
    return (this->value);
}

template<typename T>
constexpr const typename task::optional<T>::value_type&& task::optional<T>::operator*() const&& {
    return this->value;
}

template<typename T>
constexpr typename task::optional<T>::value_type&& task::optional<T>::operator*()&& {
    return this->value;
}

template<typename T>
task::optional<T>& task::optional<T>::operator=(task::nullopt_t) noexcept {
    this->reset();
    return *this;
}

template<typename T>
template<class U>
task::optional<T>& task::optional<T>::operator=(U&& value) {
    this->setValue(std::forward<U>(value));
    return *this;
}

template<typename T>
void task::optional<T>::reset() noexcept {
    this->_reset();
}
