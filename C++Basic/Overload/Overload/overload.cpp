#include <iostream>
using namespace std;

/*
C语言不支持函数重载
*/

// C++重载规则：函数名相同 参数个数不同、参数类型不同、参数顺序不同

// 返回值类型与函数重载无关 
//   调用函数时，实参的隐式类型转换可能会产生二义性

// 本质：采用了name mangling或者叫name decoration技术 
//	✓C++编译器默认会对符号名（变量名、函数名等）进行改编、修饰，有些地方翻译为“命名倾轧” 
//	✓重载时会生成多个不同的函数名，不同编译器（MSVC、g++）有不同的生成规则 
//	✓通过IDA打开【VS_Release_禁止优化】可以看到

// Release和Debug：Release代码会在Debug基础上进行优化，精简

// g++
// msvc


// 默认参数
//	函数的默认参数值定义不会影响函数对象的重载，只是在调用时，不用赋值也可以调用函数栈
//	默认参数只能按照右到左的顺序 
//	如果函数同时有声明、实现，默认参数只能放在函数声明中(代码顶部的函数声明) 
//	默认参数的值可以是常量、全局符号（全局变量、函数名）

// 函数重载、默认参数可能会产生冲突、二义性（建议优先选择使用默认参数）


// display_v
void display() {
	cout << "display() " << endl;
}

// display_i
void display(int a) {
	cout << "display(int a) " << a << endl;
}

// display_l
void display(long a) {
	cout << "display(long a) " << a << endl;
}

// display_d
void display(double a) {
	cout << "display(double a) " << a << endl;
}

// 默认参数示例
int age = 23;

void test(int arg) {
	cout << "test" << arg << endl;
}

void display(int a, int b, int c = age, void (*func)(int) = test) {
	cout << "a is" << a << endl;
	cout << "b is" << b << endl;
	cout << "c is" << c << endl;
	test(c);
}


// 逆向工程：反汇编，在debug过程中，通过反汇编查看函数汇编代码
// 外部工具：IDA
int main() {
	display();
	display(10);
	display(10l);
	display(10.1);

	display(1, 2);

	getchar();

	return 0;
}