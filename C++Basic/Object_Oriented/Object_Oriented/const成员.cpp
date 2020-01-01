// const成员：被const修饰的成员变量、非静态成员函数

// const成员变量 
//	必须初始化（类内部初始化），可以在声明的时候直接初始化赋值 
//	非static的const成员变量还可以在初始化列表中初始化

// const成员函数（非静态）: 要求不能修改对象成员变量
//	const关键字写在参数列表后面，函数的声明和实现都必须带const 
//		内部不能修改非static成员变量 
//		内部只能调用const成员函数、static成员函数。非const成员函数可能修改对象成员变量
//		非const成员函数可以调用const成员函数

//  const成员函数和非const成员函数构成重载 
//		非const对象（指针）优先调用非const成员函数

//  const对象（指针）只能调用const成员函数、static成员函数

#include <iostream>
using namespace std;

class Car {
private:
	//引用类型成员变量必须初始化（不考虑static情况） 
	//	1. 在声明的时候直接初始化 
	//  2. 通过初始化列表初始化
	int size;
	int& m_size = size;
public:
	int m_price;
	// static const int msc_wheelsCount = 4;

	Car(int price, int &size) :m_price(0), m_size(size) {

	}

	static void test3() {

	}

	void test4() {
		test1();
	}

	void test2() const {
		// this->m_price = 20;
	}

	// 不能在这个函数内部修改当前对象的成员变量
	void test1() const {
		// this->m_price = 10;

		test2();
		test3();
	}

	void test() {
		cout << "test()" << endl;
	}

	void test() const {
		cout << "test() const" << endl;
	}
};

int main() {
	Car car;
	car.test();

	Car* p = new Car();
	p->test();

	const Car car2;
	car2.test();

	const Car* p2 = new Car();
	p2->test();

	/*Car car1;
	car1.m_price = 100;

	Car car2;
	car2.m_price = 500;

	cout << sizeof(Car) << endl;*/

	getchar();
	return 0;
}