// C++中存在隐式构造的现象：某些情况下，会隐式调用单参数的构造函数

// 可以通过关键字explicit禁止掉隐式构造


#include <iostream>;
using namespace std;

class Person {
	int m_age;
public:
	Person() {
		cout << "Person() - " << this << endl;
	}
	// 因此，要限制隐式构造的现象时，使用explicit
	/*explicit Person(int age) :m_age(age) {
		cout << "Person(int) - " << this << endl;
	}*/

	Person(int age) :m_age(age) {
		cout << "Person(int) - " << this << endl;
	}
	Person(const Person& person) {
		cout << "Person(const Person &person) - " << this << endl;
	}
	~Person() {
		cout << "~Person() - " << this << endl;
	}
	void display() {
		cout << "display() - age is " << this->m_age << endl;
	}
};

void test1(Person person) {

}

// 调用了单参数的构造函数
Person test2() {
	return 30;
}

int main() {

	// 调用了单参数的构造函数
	test1(40);

	// Person person = test2();
	// Person person(10);
	// person = test2();

	// 调用了单参数的构造函数
	Person person = 10;

	// Person person(10);
	person = 20;
	// person.display();

	// 因此，要限制隐式构造的现象时，使用explicit

	getchar();
	return 0;
}