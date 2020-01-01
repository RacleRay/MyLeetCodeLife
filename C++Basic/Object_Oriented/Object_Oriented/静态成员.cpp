// 静态成员：被static修饰的成员变量\函数
//	可以通过对象（对象.静态成员）、对象指针（对象指针->静态成员）、类访问（类名::静态成员）

// 静态成员变量 
//	存储在数据段（全局区，类似于全局变量），整个程序运行过程中只有一份内存 
//	对比全局变量，它可以设定访问权限（public、protected、private），达到局部共享的目的 
//	必须初始化，必须在类外面初始化（可理解为类外的全局变量），初始化时不能带static，如果类的声明和实现分离（在实现.cpp中初始化）

// 静态成员函数 
//	内部不能使用this指针（this指针只能用在 非静态成员函数 内部）
//	不能是虚函数（虚函数只能是 非静态成员函数 ） 
//	静态成员函数内部不能访问非静态成员变量\函数，只能访问静态成员变量\函数 
//	非静态成员函数内部可以访问静态成员变量\函数 
//	构造函数、析构函数不能是静态 
//	当声明和实现分离时，实现部分不能带static

#include <iostream>
using namespace std;


class Car {
public:
	static int m_price;
	void run() {
		cout << "run()" << endl;

	}
};

// 初始化静态成员变量
int Car::m_price = 0;
// 和普通全局变量的区别在于，静态成员变量可以设置访问权限

int main() {
	Car car;
	car.m_price = 10;

	Car car2;
	car2.m_price = 20;

	Car::m_price = 30;

	Car *p = new Car();
	p->m_price = 40;
	delete p;
	// 独立于对象空间的内存区域，仍存在
	cout << Car::m_price << endl;


	Car car3;
	cout << car3.m_price << endl;


	getchar();
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
class CarCount {
private:
	static int m_count;
public:
	// 可能出现线程安全问题，不同线程同时创建删除不同对象，需要根据系统api进行优化
	CarCount() {
		m_count++;
	}
	~CarCount() {
		m_count--;
	}
	static int getCount() {
		return m_count;
	}
};

int CarCount::m_count = 0;

//int main() {
//	Car car1;
//	Car car2;
//	Car *p = new Car();
//	delete p;
//
//	cout << car1.getCount() << endl;
//
//	cout << Car::getCount() << endl;
//
//	/*Car car1;
//	car1.m_count = 10;
//	car1.getCount();
//
//	p->m_count = 10;
//	p->getCount();
//
//	Car::m_count = 20;
//	Car::getCount();*/
//
//	getchar();
//	return 0;
//}