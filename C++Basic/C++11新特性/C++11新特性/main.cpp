#include <iostream>
using namespace std;


class Person {
public:
	int m_age;
};

void test_Auto() {
	//auto 
	//	可以从初始化表达式中推断出变量的类型，大大简化编程工作 
	//	属于编译器特性，不影响最终的机器码质量，不影响运行效率

	auto i = 10;
	auto name = "jack";
	auto d = 9.6;
	auto p = new Person();
	p->m_age = 10;

	//decltype 
	//	可以获取变量的类型
	decltype(d) c = 9.9;
}


void func(int p) {
	cout << "func(int) - " << p << endl;
}

void func(int* p) {
	cout << "func(int *) - " << p << endl;
}

void test_nullptr() {
	int i = 0;
	int *p = nullptr;

	/*nullptr 
		可以解决NULL的二义性问题*/
	// NULL: 实际上就是定义的一个宏，其值为0
	// 因此C语言中调用func(int p)与func(int* p）都是传入int p。
	// 使用nullptr可以防止NULL的二义性
	func(0);
	func(NULL);
	func(nullptr);

	// nullptr只能赋值给指针
	// delete p;
	// p = nullptr;

	cout << (nullptr == NULL) << endl;
}

int main() {
	/*int length = sizeof(array) / sizeof(int);
	for (int i = 0; i < length; i++)
	{
		cout << array[i] << endl;
	}*/

	// 快速遍历
	int array[]{ 10, 20, 30, 40 };
	for (int item : array) {
		cout << item << endl;
	}

	// 更简洁的初始化
	int array[]{ 10, 20, 30, 40 };
	// int array[] = { 10, 20, 30, 40 };
}

