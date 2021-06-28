#pragma once

#include <atomic>

class SharedCount {
public:
    // Your code goes here...

protected:
    // Your code goes here...
};

class SharedWeakCount : public SharedCount {
public:
    // Your code goes here...

protected:
    // Your code goes here...
};

template <typename T, typename Deleter>
class ControlBlock : public SharedWeakCount {
public:
    // Your code goes here...

private:
    // Your code goes here...
};