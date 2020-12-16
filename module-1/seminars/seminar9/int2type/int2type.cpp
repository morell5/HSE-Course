
template<int v>
struct Int2Type {
    enum { value = v };
};

struct Base {
    Base() : x(10) { }
    Base(int _x) : x(_x) {}
    Base(const Base& obj) : x(obj.x) {}
    
    virtual Base* Clone() { return new Base(x); };
    
    void Foo() {};
    
    private:
    int x;
};

struct Derived : Base {
    Derived() : Base(), y(20) { }
    Derived(int _y) : Base(_y), y(_y) {}
    Derived(const Derived& obj) : Base(obj), y(obj.y) {}

    virtual void Foo() {};
    virtual Base* Clone() { return new Base(y); };
    
    private:
    int y;
};

// T - polymorphic type
// T - non - polymorphic type
template<typename T, bool isPolymorphic>
class Container {
private:
    void DoSomething(T* fst, Int2Type<true>) {
        T* scd = fst->Clone();
    }
    
    void DoSomething(T* fst, Int2Type<false>) {
        T* scd = new T(*fst);
    }
    
public:
    void DoSomething(T* fst) {
        DoSomething(fst, Int2Type<isPolymorphic>());
    }
};

int main() {
    Base* b = new Derived(1);
    Base* d = b->Clone();
    Container<int, false> non_poly_morphic;
    int* y = new int(1);
    non_poly_morphic.DoSomething(y);
    
    Container<Base, true> poly_morphic;
    poly_morphic.DoSomething(b);
 
    return 0;
}