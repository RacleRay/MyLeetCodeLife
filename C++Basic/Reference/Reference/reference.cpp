// 在C语言中，使用指针（Pointer）可以间接获取、修改某个变量的值 
// 在C++中，使用引用（Reference）可以起到跟指针类似的功能


// 注意点 
//	引用相当于是变量的别名（基本数据类型、枚举、结构体、类、指针、数组等，都可以有引用） 
//	对引用做计算，就是对引用所指向的变量做计算 
//	在定义的时候就必须初始化，一旦指向了某个变量，就不可以再改变，“从一而终”;而指针可以修改指向 
//	可以利用引用初始化另一个引用，相当于某个变量的多个别名 
//	不存在【引用的引用、指向引用的指针、引用数组】

// 引用需要初始化


// 引用存在的价值之一：比指针更安全、函数返回值可以被赋值。
//	因为指针可以 = 赋值为某一个地址；而引用作为变量的别名，只能指向赋值为 已知的变量


// 引用的本质就是指针，只是编译器削弱了它的功能，所以引用就是弱化了的指针
// 一个引用占用一个指针的大小


#include <iostream>
using namespace std;


struct Student {
	int age;
};


int main() {
	int age = 10;

	int* p = &age;
	*p = 30;

	/*x86:32位为4个字节
	x64:64位，8个字节*/
	cout << sizeof(p) << endl;

	// 从汇编的对比，可以发现引用和指针的机器码是相同的
	int& ref = age;
	ref = 40;


	// 内嵌汇编代码
	__asm {
		mov eax, 10
	}


	//结构体引用
	Student d = { 18 };
	Student& ref1 = d;  // ref1成为了d的别名

	// 指针的引用
	int var1 = 10;
	int* p = &var1;
	int*& ref2 = p;  // *指明为指针变量的引用
	*ref2 = 15;  // ref2为p的别名

	// 数组的引用
	int arr[] = { 1, 2, 3 };
	int(&ref)[3] = arr;
	// 数组名为数组首元素的地址指针
	int* const& ref = arr;  // 第二种方式


	// NOTE:
	int* arr2[3] = { p, p, p };  // 存放int*指针的数组
	int(*arr3)[3];  // 指向数组的指针

	// const reference
	//	引用可以被const修饰，这样就无法通过引用修改数据了，可以称为常引用
	//	const必须写在&符号的左边，才能算是常引用; 同指针的const规则
	
	// const引用的特点 
	//	可以指向临时数据（常量、表达式、函数返回值等）
	int& ref3 = 30;  // Wrong
	const int& ref4 = 30;
	//	可以指向不同类型的数据
	//	作为函数参数时（此规则也适用于const指针） 
	//		可以接受const和非const实参（非const引用，只能接受非const实参）
	// int sum{const int& a, const int& b} 可以接受const和非const实参  sum(1, 2)对
	// int sum{int& a, int& b}  非const引用，只能接受非const实参  sum(1, 2)不对
	//		可以跟非const引用构成重载

	// 当常引用指向了不同类型的数据时，会产生临时变量，即引用指向的并不是初始化时的那个变量
	int var4 = 10;
	const double& ref5 = var4;
	var4 = 15;  // 此时var4 == 15，ref5 == 10

	int var6 = 10;
	const int& ref6 = var6;
	var4 = 15;  // 此时var4 == 15，ref6 == 15

	getchar();
	return 0;
}