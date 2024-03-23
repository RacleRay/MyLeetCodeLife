/*
    简单⼯⼚、⼯⼚⽅法、抽象⼯⼚的区别
    简单⼯⼚模式：⼀个⼯⼚⽅法创建所有具体产品
    ⼯⼚⽅法模式：⼀个⼯⼚⽅法创建⼀个具体产品
    抽象⼯⼚模式：⼀个⼯⼚⽅法可以创建⼀类具体产品
*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

//=================================================================================
// Product

// abstract product
class Product1 {
public:
    virtual void info() = 0;
};

class Product2 {
public:
    virtual void info() = 0;
};


// Concrete product
class ModernProduct1 : public Product1 {
public:
    void info() override {
        cout << "ModernProduct1" << endl;
    }
};

class ClassicProduct1 : public Product1 {
public:
    void info() override {
        cout << "ClassicProduct1" << endl;
    }
};

class ModernProduct2 : public Product2 {
public:
    void info() override {
        cout << "ModernProduct2" << endl;
    }
};


class ClassicProduct2 : public Product2 {
public:
    void info() override {
        cout << "ClassicProduct2" << endl;
    }
};


//=================================================================================
// Factory

class Factory {
public:
    virtual shared_ptr<Product1> createProduct1() = 0;
    virtual shared_ptr<Product2> createProduct2() = 0;
};


class ModernFactory : public Factory {
public:
    shared_ptr<Product1> createProduct1() override {
        return std::make_shared<ModernProduct1>();
    }

    shared_ptr<Product2> createProduct2() override {
        return std::make_shared<ModernProduct2>();
    }
};


class ClassicFactory : public Factory {
public:
    shared_ptr<Product1> createProduct1() override {
        return std::make_shared<ClassicProduct1>();
    }

    shared_ptr<Product2> createProduct2() override {
        return std::make_shared<ClassicProduct2>();
    }
};


//=================================================================================
// map for input
unordered_map<string, function<shared_ptr<Factory>()>> m = {
    {"Modern", []() { return std::make_shared<ModernFactory>(); }},
    {"Classic", []() { return std::make_shared<ClassicFactory>(); }}
};


//=================================================================================
// main
int main() {
    int n;
    cin >> n;

    string type;
    while (n--) {
        cin >> type;
        auto f = m[type]();
        auto p1 = f->createProduct1();
        auto p2 = f->createProduct2();
        p1->info();
        p2->info();
    }

    return 0;
}
