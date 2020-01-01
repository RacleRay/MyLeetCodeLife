//Lambda表达式 
//有点类似于JavaScript中的闭包、iOS中的Block，本质就是函数 
//
//完整结构：[capture list](params list) mutable exception-> return type{ function body } 
//	✓capture list：捕获外部变量列表 
//	✓params list：形参列表，不能使用默认参数，不能省略参数名 
//	✓mutable：用来说用是否可以修改捕获的变量 
//	✓exception：异常设定 
//	✓return type：返回值类型 
//	✓function body：函数体 
//
//有时可以省略部分结构 
//	✓[capture list](params list) -> return type{ function body } 
//	✓[capture list](params list) { function body } 
//	✓[capture list]{ function body }


#include <iostream>
using namespace std;

int exec(int a, int b, int (*func)(int, int)) {
	return func(a, b);
}


// [capture list]：外部变量捕获
// 默认都是直接捕获变量的当前值
// 因此，要得到随时更新的变量值，就捕获变量的地址
void test_capture() {
	int a = 10;
	int b = 20;
	auto func = [a] {
		cout << a << endl;
	};

	// 地址捕获
	auto func = [&a] {
		cout << a << endl;
	};

	// 隐式捕获：根据函数体内变量名，捕获
	auto func = [=] {
		cout << a << endl;
	};

	// 隐式地址捕获：根据函数体内变量名，捕获地址
	auto func = [&] {
		cout << a << endl;
	};

	auto func_2 = [=, &a] {
		cout << a << endl;
		cout << b << endl;

	};

	auto func_2 = [&, a] {
		cout << a << endl;
		cout << b << endl;
	};

	// mutable：在值捕获条件下，修改函数内部的外部变量值，但外部变量不变
	// 注意()
	auto func = [a]() mutable {
		cout << ++a << endl;
	};
	func();
	cout << a << endl;
}


int main() {
	// [](int a, int b) -> int {return a + b;} 相当于一个函数
	// 定义函数指针指向该函数
	int (*p1)(int, int) = [](int a, int b) -> int {return a + b;};

	auto p1 = [](int a, int b) -> int {return a + b; };

	int res;
	// 传入lambda
	res = exec(1, 2, [](int a, int b) {return a + b; });
}