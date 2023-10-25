/*************************************************************************
    > File Name: useproxy.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include<iostream>
#include"proxy.h"

void func(CC var) {
    //var.func();
    std::cout << "by value" << std::endl;
}

int main(int argc, char *argv[]) {

    CC cc;

    // 错误示范
    // func(cc);
    
    cc.func();

    return 0;
}
