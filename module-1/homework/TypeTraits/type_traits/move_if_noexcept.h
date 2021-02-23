# pragma once

#include <type_traits>
#include <utility>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

// conditional
template<bool condition, typename T, typename F>
struct conditional {
    ...
};

// conditional - partial specialization
...

template<bool condition, typename T, typename F>
using conditional_v = ...

// move_if_noexcept