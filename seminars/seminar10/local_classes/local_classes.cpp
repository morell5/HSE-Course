#include <iostream>
#include <string>

class InterfaceB {
public:
    virtual void MethodB(std::string s) { std::cout << "Hello world!" << std::endl;  };
};

class InterfaceA {
public:
    virtual void MethodA() { std::cout << "Hello world!" << std::endl; }
};

void LegacyFunction(InterfaceA* obj) {
    obj->MethodA();
}

template<typename ObjType, typename ArgType>
InterfaceA* Adapter(const ObjType& obj, const ArgType& arg) {
    class LocalClass : public InterfaceA {
        public:
            LocalClass(const ObjType& obj, const ArgType& arg) : 
                obj_(obj),
                arg_(arg) 
            {}

            void MethodA() override {
                obj_.MethodB(arg_); 
            }

        private:
            ArgType arg_;
            ObjType obj_;
    };

    return new LocalClass(obj, arg);
}

int main() {
    InterfaceB* b = new InterfaceB;
    InterfaceA* a = Adapter(*b, std::string("aaa"));
    LegacyFunction(a);
    return 0;
}