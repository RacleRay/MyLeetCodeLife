#include <iostream>
#include <cassert>
#include "Any.hpp"

int main() {
    google::InitGoogleLogging("test_Any");

    // Test empty MyAny
    MyAny empty;
    assert(empty.empty());

    // Test MyAny with int
    MyAny a = 10;
    assert(!a.empty());
    assert(a.getType() == typeid(int));
    assert(any_cast<int>(a) == 10);

    // Test MyAny with string
    std::string str = "Hello";
    a = str;
    assert(!a.empty());
    assert(a.getType() == typeid(std::string));
    assert(any_cast<std::string>(a) == "Hello");

    // Test MyAny with custom class
    class MyClass {
    public:
        int value;
        MyClass(int val) : value(val) {}
    };

    MyClass obj(42);
    a = obj;
    assert(!a.empty());
    assert(a.getType() == typeid(MyClass));
    assert(any_cast<MyClass>(a).value == 42);

    // Test assignment operator
    MyAny b = 20;
    a = b;
    assert(!a.empty());
    assert(a.getType() == typeid(int));
    assert(any_cast<int>(a) == 20);

    // Test move assignment operator
    MyAny c = std::move(a);
    assert(a.empty());
    assert(!c.empty());
    assert(c.getType() == typeid(int));
    assert(any_cast<int>(c) == 20);

    std::cout << "All tests passed!" << std::endl;

    return 0;
}