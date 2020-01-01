//在一个函数内部定义的类，称为局部类

//局部类的特点 
//	1. 作用域仅限于所在的函数内部 
//	2. 其所有的成员必须定义在类内部，不允许定义static成员变量 
//	3. 成员函数不能直接访问函数的局部变量（static变量除外）


#include <iostream>
using namespace std;

int g_age = 20;

void test() {
	int age = 10;
	static int s_age = 30;

	// 局部类
	class Person {
	public:
		static void run() {
			g_age = 30;
			s_age = 40;

			cout << "run()" << endl;
		}
	};

	Person person;
	Person::run();
}

int main() {
	test();

	getchar();
	return 0;
}