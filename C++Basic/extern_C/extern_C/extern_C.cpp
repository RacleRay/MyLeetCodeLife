#include <iostream>
#include "sum.h"
using namespace std;


// 被extern "C"修饰的代码会按照C语言的方式去编译
// 如果函数同时有声明和实现，要让函数声明被extern "C"修饰，函数实现可以不修饰

extern "C" void func();
extern "C" void func_2();

void func() {
	cout << "func()" << endl;
}
	
void func_2(int a) {
	cout << "func(int a) " << a << endl;
}


// 由于C、C++编译规则的不同，在C、C++混合开发时，可能会经常出现以下操作

// 第三方库可能是使用C写的
// 通过extern "C"指明，从.c文件去查找

// 这种方式可以实现，但是不够灵活简洁
//extern "C" {
//	#include "math.h"
//}

