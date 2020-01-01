// 拷贝构造函数（Copy Constructor）

// 拷贝构造函数是构造函数的一种

// 当利用已存在的对象创建一个新对象时（类似于拷贝），
// 就会调用新对象的拷贝构造函数进行初始化

// 拷贝构造函数的格式是固定的，接收一个const引用作为参数

#include <iostream>
using namespace std;

class Car {
	int m_price;
	int m_length;

public:
	Car(int price = 0, int length = 0) :m_price(price), m_length(length) {
		cout << "Car(int price = 0, int length = 0)" << endl;
	}

	// 拷贝构造函数（格式是固定的）
	Car(const Car& car) :m_price(car.m_price), m_length(car.m_length) {
		// 内部初始化，或者如上一行代码的列表初始化
		/*this->m_price = car.m_price;
		this->m_length = car.m_length;*/

		cout << "Car(const Car &car)" << endl;
	}

	void display() {
		cout << "price=" << this->m_price << ", length=" << this->m_length << endl;
	}
};

int main() {
	Car car1;

	Car car2(100, 5);

	// 利用car2对象创建了car3对象，会调用car3对象的拷贝构造函数进行初始化
	Car car3(car2);
	car3.display();

	cout << "&car2 = " << &car2 << endl;
	cout << "&car3 = " << &car3 << endl;

	//若没有实现拷贝构造函数Car(const Car& car) :m_price(car.m_price), m_length(car.m_length)
	//	这里是赋值操作，直接将car2的8个字节数据拷贝给car3的8个字节
	//	一般没有特殊要求，拷贝构造函数可以不用特别实现
	//Car car2(100, 5);
	//Car car3 = car2; // 等价于Car car3(car2)

	//Car car2(100, 5);
	//Car car3;
	// car3 = car2是一个赋值操作（默认是浅拷贝）
	//car3 = car2;

	//相当于：
	//car3.m_price = car2.m_price;
	//car3.m_length = car2.m_length;

	getchar();
	return 0;
}


class Person {
	int m_age;
public:
	Person(int age = 0) :m_age(age) { }
	Person(const Person& person) :m_age(person.m_age) { }
};

class Student : public Person {
	int m_score;
public:
	Student(int age = 0, int score = 0) :Person(age), m_score(score) { }
	// 子类的拷贝构造函数，需要调用父类的拷贝构造函数（如果有拷贝构造函数实现）
	Student(const Student& student) :Person(student), m_score(student.m_score) { }
};


// 不使用拷贝构造函数，默认复制所有成员变量