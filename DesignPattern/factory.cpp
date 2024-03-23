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

class ShapeFactory {
public:
    // virtual Shape* produce() = 0;
    virtual shared_ptr<Shape> produce() = 0;
};


// template <typename Shp>
// class TShapeFactory {
// public:
//     std::shared_ptr<Shape> produce() {
//         return std::make_shared<Shp>();
//     }
// };


class CircleFactory: public ShapeFactory {
public:
    // Shape* produce() {
    //     return new Circle();
    // }
    shared_ptr<Shape> produce() {
        return std::make_shared<Circle>();
    }
};

class SquareFactory: public ShapeFactory {
public:
    // Shape* produce() {
    //     return new Square();
    // }
    shared_ptr<Shape> produce() {
        return std::make_shared<Square>();
    }
};

// unordered_map<string, function<ShapeFactory*()>> m {
//     {"Circle", []() { return new CircleFactory(); }},
//     {"Square", []() { return new SquareFactory(); }}
// };

unordered_map<string, function<shared_ptr<ShapeFactory>()>> m2 {
    {"Circle", []() { return std::make_shared<CircleFactory>(); }},
    {"Square", []() { return std::make_shared<SquareFactory>(); }}
};


class Factory{
public:
    vector<shared_ptr<Shape>> shapes;
    
    void create_shape(const string& type, int cnt) {
        auto sf = m2[type]();
        // shapes.push_back(s);
        for (int i = 0; i < cnt; i++) {
            shapes.push_back(std::move(sf->produce()));
        }
    }

    void show() {
        for (auto s : shapes) {
            s->show();
        }
    }
};


int main() {
    int n;
    cin >> n;

    string type;
    int cnt;
    Factory* factory = new Factory();
    
    for (int i = 0; i < n; i++) {
        cin >> type >> cnt;
        factory->create_shape(type, cnt);
    }

    factory->show();

    delete factory;

    return 0;
}