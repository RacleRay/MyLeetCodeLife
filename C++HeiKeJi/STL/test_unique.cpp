#include <cstdio>
#include <vector>
#include <iostream>
#include "unique_ptr.hpp"

struct MyClass {
    int a, b, c;
};

struct Animal {
    virtual void speak() = 0;
    virtual ~Animal() = default;
};

struct Dog : Animal {
    int age;

    // 值
    Dog(int age_) : age(age_) {
    }

    virtual void speak() {
        printf("Dog age is %d\n", age);
    }
};

struct Cat : Animal {
    int &age;

    // 引用
    Cat(int &age_) : age(age_) {
    }

    virtual void speak() {
        printf("Cat age is %d\n", age);
    }
};

int main() {
    std::vector<UniquePtr<Animal>> zoo;

    int age = 3;
    zoo.push_back(makeUnique<Cat>(age));
    zoo.push_back(makeUnique<Dog>(age));

    for (auto const &a: zoo) {
        a->speak();
    }

    age++;
    for (auto const &a: zoo) {
        a->speak();
    }
    return 0;
}