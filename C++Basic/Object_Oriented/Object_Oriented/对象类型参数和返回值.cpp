// 使用对象类型作为函数的参数或者返回值，可能会产生一些不必要的中间对象


#include <iostream>
using namespace std;

class Car {
	int m_price;
public:
	Car(int price = 0) :m_price(price) {
		cout << "Car(int) - " << this << " - " << this->m_price << endl;
	}

	Car(const Car& car) :m_price(car.m_price) {
		cout << "Car(const Car &) - " << this << " - " << this->m_price << endl;
	}
};


void test1(Car car) {

}

void test1_ref(Car& car) {

}

Car test2() {
	Car car(10);
	return car;
}

int main() {
	// 构造car1对象
	Car car1(10);
	// 在传参过程中，test1(Car car = car1),"Car car = car1"再次调用拷贝构造函数（没有该函数，也会拷贝）
	// 产生中间对象
	test1(car1);

	test1_ref(car1);  // 使用引用
	
	///////////////////////////////////////////////////////////////////////
	
	// test2返回的car对象地址存在于栈空间，而test2调用完成之后，被回收
	// 所以，编译器会调用Car的拷贝构造函数，在main函数空间拷贝一份car对象
	// 所以，以下代码调用了三次构造函数
	Car car3;
	car3 = test2();

	// 以下代码编译器将两次重复的拷贝构造函数，合并为一次拷贝构造函数
	Car car2 = test2();

	// 因此，不推荐返回对象类型

	getchar();
	return 0;
}