// 如果将类A定义在类C的内部，那么类A就是一个内部类（嵌套类）

//内部类的特点 
//	支持public、protected、private权限（控制类的可见性） 
//	成员函数可以直接访问其外部类对象的所有成员（反过来则不行） 
//	成员函数可以直接不带类名、对象名访问其外部类的static成员 
//	不会影响外部类的内存布局（只是影响内部类的访问权限） 
//	可以在外部类内部声明，在外部类外面进行定义


#include <iostream>
using namespace std;

// Person
class Person {
private:
	static int ms_legs;
	static void other() {

	}
	int m_age;
	void walk() {

	}

	// Car
	class Car {
		int m_price;
	public:
		Car() {
			cout << "Car()" << endl;
		}

		void run() {
			Person person;
			person.m_age = 10;
			person.walk();

			ms_legs = 10;
			other();
		}
	};
public:
	Person() {
		cout << "Person()" << endl;

		Car car;
	}


};


int Person::ms_legs = 2;

class Point {
	class Math {
		void test();
	};
};

void Point::Math::test() {

}

int main() {
	cout << sizeof(Person) << endl;
	Person person;

	// 不可访问
	Person::Car car;

	getchar();
	return 0;
}