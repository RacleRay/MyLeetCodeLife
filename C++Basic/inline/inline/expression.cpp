//在C++中，(a+b) 括号表达式是可以赋值的

//const是常量的意思，被其修饰的变量不可修改 
//	如果修饰的是类、结构体（的指针），其成员也不可以更改

//const修饰的是其右边的内容

#include <iostream>
using namespace std;


struct Student {
	int age;
};

int main() {
	const Student d = { 18 };
	Student d2 = { 17 };

	//d = d2; 不可行

	const Student* p = &d2;
	//p->age = 19;  不可通过指针修改
	//(*p).age = 19;

	d2.age = 19; // 可行


	int var1 = 10, var2 = 20;

	// * p1不可修改，p1可
	// int与const位置可以交换
	const int* p1 = &var1;
	// p1不可修改，*p1可
	int* const p1 = &var1;

	// 都不可修改
	const int* const p2 = &var2;

}
