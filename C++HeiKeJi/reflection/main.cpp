/*************************************************************************
    > File Name: main.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include<iostream>
#include"scienum.h"

enum Color {
    RED = 1, GREEN = 2, BLUE = 3, YELLOW = 4
};

int main(int argc, char *argv[]) {
    std::cout << scienum::get_enum_name(RED) << std::endl;
    std::cout << scienum::get_enum_name(2) << std::endl;
    std::cout << scienum::enum_from_name<Color>("BLUE") << std::endl;
    return 0;
}
