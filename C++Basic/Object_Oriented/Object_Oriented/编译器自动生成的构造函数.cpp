//C++的编译器在某些特定的情况下，会给类自动生成无参的构造函数，比如 
//	1. 成员变量在声明的同时进行了初始化 
//	2. 有定义虚函数 
//	3. 虚继承了其他类 
//	4. 包含了对象类型的成员，且这个成员有构造函数（编译器生成或自定义） 
//	5. 父类有构造函数（编译器生成或自定义）



#include <iostream>
using namespace std;

/*
错误的说法：“编译器会为每个类生成一个默认的无参的构造函数”
*/

// 对象创建后，需要做一些额外操作时（比如内存操作、函数调用），
// 编译器一般都会为其自动生成无参的构造函数

class Person {
public:
	int m_age = 0;
};

class Student : public Person {

};

int main() {
	Student student;

	getchar();
	return 0;
}