#include "Vector.hpp"


int main() {
    Vector<int> v(10);

    for (size_t i = 0; i < v.size(); i++) {
        // v[i] = i;

    }

    // int a = 10;
    std::string a = "asdfa";
    std::cout << a << std::endl;

    // int b = std::move(a);
    std::string b = std::move(a);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
}