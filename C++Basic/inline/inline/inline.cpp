#include <iostream>
using namespace std;

//使用inline修饰函数的声明或者实现，可以使其变成内联函数 
//	建议声明和实现都增加inline修饰，可以只在一处修饰

//特点 
//	编译器会将函数调用直接展开为函数体代码：相当于在函数处，换成对应代码 
//	可以减少函数调用的开销：函数的每次调用都会，开辟栈空间和释放栈空间 
//	会增大代码体积

//注意 
//	尽量不要内联超过10行代码的函数 
//	有些函数即使声明为inline，也不一定会被编译器内联，比如递归函数

//inline相当于建议编译方法，实际可能不是inline处理方式

inline int sum(int a, int b);

int main(){
	sum(10, 20);

	getchar();
	return 0;
}

inline int sum(int a, int b) {
	return a + b;
}

//宏替换
//inline和宏定义，有着相似的功能
//	对比宏，内联函数多了语法检测和函数特性

#define add(a, b) ((a) + (b))
