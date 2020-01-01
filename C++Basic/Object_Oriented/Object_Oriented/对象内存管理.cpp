#include <iostream>
using namespace std;

struct Car {
	int m_price;
	Car() {
		cout << "Car()" << endl;
	}

	~Car() {
		cout << "~Car()" << endl;
	}
};

// 对象内部申请的堆空间，由对象内部回收

struct Person {
	int m_age; // 4
	Car* m_car; // 4。栈空间的指针

	// 初始化工作
	Person() {
		cout << "Person()" << endl;

		this->m_car = new Car();  // 指向堆空间的对象

		/*Car car;
		this->m_car = &car;*/
	}

	// 内存回收、清理工作(回收Person对象内部申请的堆空间)
	//	如果没有析构函数，那么函数调用过程的栈空间回收不了内部申请的堆空间。
	~Person() {
		cout << "~Person()" << endl;

		delete this->m_car;
	}
};

void test() {
	Person* p = new Person();

	delete p;
}

int main() {
	test();

	getchar();
	return 0;
}