#pragma once

class shared_count {
    protected:
        // Your code goes here...

    public:
        // Your code goes here...
};

class shared_weak_count : public shared_count {
    private:
        // Your code goes here...
    
    public:
        // Your code goes here...
};

template<typename T, typename Deleter>
class control_block : public shared_weak_count {
    public:
        // Your code goes here...

    private:
        // Your code goes here...
};
