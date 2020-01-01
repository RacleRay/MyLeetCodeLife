//编程过程中的常见错误类型 
//	语法错误 
//	逻辑错误 
//	异常

// 异常是一种在程序运行过程中的发生的不好预测的错误（比如内存不够） 
// 异常没有被处理，会导致程序终止


#include <iostream>
using namespace std;

void test() {
	cout << "1" << endl;

	// 如果内存不够，就会抛出异常(运行过程中抛出一个错误)
	try {
		for (int i = 0; i < 9999999; i++) {
			int* p = new int[9999999];
		}

		cout << "2" << endl;
	}
	catch (...) {
		cout << "发生了异常" << endl;
	}
	// catch(异常类型 [变量名]){}

	cout << "3" << endl;

	// delete[] p;
}

// 定义在try中的a / 0，程序可能闪退，catch部分并没有执行
// 因此此时需要手动抛出异常
//	  异常会在整个运行过程中检测对应的catch。
//	  找不到就 终止当前函数代码，去上一层函数中查找。
//    如果最终都找不 到匹配的catch，整个程序就会终止。
int divide(int a, int b) {
	if (b == 0) throw "不能除以0";
	return a / b;
}


// 异常的抛出声明
//	为了增强可读性和方便团队协作，
//	如果函数内部可能会抛出异常，建议函数声明一下异常类型

// 抛出任何可能的异常
void func1() {

}

// 不抛出任何异常
void func2() throw() {

}

// 只抛出int、double类型异常
void func3() throw(int, double) {

}



// 自定义异常类型

class Exception {
public:
	virtual const char* what() const = 0;
};

class DivideException : public Exception {
public:
	const char* what() const {
		return "不能除以0";
	}
};

class AddException : public Exception {
public:
	const char* what() const {
		return "加法有问题";
	}
};

int divide(int a, int b) throw(Exception){
	if (b == 0) throw DivideException();
	return a / b;
}

int main() {
	try {
		int a = 10;
		int b = 0;
		int c = divide(a, b);
	}
	catch (const Exception & exception) {
		cout << exception.what() << endl;
	}
}