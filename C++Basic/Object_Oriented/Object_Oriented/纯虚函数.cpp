// 纯虚函数：没有函数体且初始化为0的虚函数，用来定义接口规范

// 抽象类（Abstract Class） 
//	含有纯虚函数的类，不可以实例化（不可以创建对象） 
//	抽象类也可以包含非纯虚函数，成员变量（只要有一个纯虚函数） 
//	如果父类是抽象类，子类没有完全实现纯虚函数，那么这个子类依然是抽象类


#include <iostream>
using namespace std;

// 类似于Java中接口、抽象类
// 类似于OC中的协议protocol

// Animal是个抽象类
class Animal {
public:
	virtual void speak() = 0;
	virtual void run() = 0;
};

class Cat : public Animal {
public:
	void run() {

	}
};

class WhiteCat : public Cat {
public:
	void speak() {

	}
	void run() {

	}
};

int main() {
	Cat* cat = new WhiteCat();

	getchar();
	return 0;
}