#include <iostream>
#include <map>
#include <unordered_map>
#include <string>

struct Person {
    std::string name;

    Person(std::string& name_) : name(std::move(name_)) {}
};

struct Order {
    std::string name;

    Order(std::string& name_) : name(std::move(name_)) {}
};

struct KFCOrder : public Order {};

struct McDonaldsOrder : public Order {};

class Restourant {
    public:
        Restourant() = delete;

    private:
        std::unordered_map<Person*, Order*> orders;
};

class KFC : public Restourant {

};

class McDonalds : public Restourant {

};


int  main() {  
    return 0;
}