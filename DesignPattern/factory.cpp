#include <iostream>
#include <bits/stdc++.h>


using namespace std;


class Shape {
public:
    virtual void show() = 0;
};

class Circle : public Shape {
public:
    void show() {
        cout << "circle" << endl;
    }
};

class Square : public Shape {
public:
    void show() {
        cout << "square" << endl;
    }
};

template <typename T>
class ShapeFactory {
public:
    // virtual shared_ptr<T> produce() = 0;
    shared_ptr<T> produce() {
        return make_shared<T>();
    }
};


// unordered_map<string, function<ShapeFactory<Shape>()>> m {
//     "Circle", []() { return ShapeFactory<Circle>(); }
// };


class Factory{
public:
    vector<Shape*> shapes;
    
    void create_shape(const string& type, int cnt) {
        Shape* s = 
    }
};