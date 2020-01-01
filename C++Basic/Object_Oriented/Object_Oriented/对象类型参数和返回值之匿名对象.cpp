//匿名对象（临时对象）

//匿名对象：没有变量名、没有被指针指向的对象，用完后马上调用析构


#include <iostream>
using namespace std;

class Car {
	int m_price;
public:
	Car() {
		cout << "Car(int) - " << this << " - " << this->m_price << endl;
	}

	Car(const Car& car) {
		cout << "Car(const Car &) - " << this << " - " << this->m_price << endl;
	}

	~Car() {

	}
};


void test1(Car car) {

}

Car test2() {
	Car car;
	return car;
}

int main() {
	Car(); // 匿名对象,编译器优化，不会调用拷贝构造，本来就用完后马上调用析构嘛
}


