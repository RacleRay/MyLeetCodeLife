#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

using namespace std;


class Bike {
private:
    string type{};

public:
    void set_type(const string& type) {
        this->type = type;
    }

    string get_info() {
        return type;
    }
};


class Builder {
public:
    virtual void build_type() = 0;
    virtual Bike get_bike() = 0;
    virtual ~Builder() = default;
};


class RoadBikeBuilder : public Builder {
private:
    Bike bike{};

public:
    void build_type() override {
        bike.set_type("Road");
    }

    Bike get_bike() override {
        return bike;
    }
};


class MountainBikeBuilder : public Builder {
private:
    Bike bike{};

public:
    void build_type() override {
        bike.set_type("Mountain");
    }

    Bike get_bike() override {
        return bike;
    }
};


class Director {
private:
    Builder* builder{nullptr};

public:
    Director(Builder* builder) {
        this->builder = builder;
    }

    // normal build process with virtual functions
    void construct() {
        builder->build_type();
    }
    // after the build process, get the result
};


int main() {
    int n;
    cin >> n;
    string type;

    unordered_map<string, function<shared_ptr<Builder>()>> m = {
        {"road", []() { return make_shared<RoadBikeBuilder>(); }},
        {"mountain", []() { return make_shared<MountainBikeBuilder>(); }}
    };

    while (n--) {
        cin >> type;

        auto builder = m[type]();

        Director director(builder.get());

        director.construct();

        auto bike = builder->get_bike();
        cout << bike.get_info() << endl;
    }

    return 0;
}