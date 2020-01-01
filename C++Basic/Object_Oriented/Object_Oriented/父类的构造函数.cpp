#include <iostream>
using namespace std;


// 子类的构造函数默认会调用父类的无参构造函数 (先调用)
// 如果子类的构造函数显式地调用了父类的有参构造函数，就不会再去默认调用父类的无参构造函数
// 如果父类缺少无参构造函数，子类的构造函数必须显式调用父类的有参构造函数

class Person {
	int m_age;
public:
	Person(int age = 90) :m_age(age) {
		cout << "Person(int age)" << endl;
	}

	~Person() {
		cout << "~Person" << endl;
	}
};

class Student : public Person {
	int m_score;
public:
	// 如果父类缺少无参构造函数，子类的构造函数必须显式调用父类的有参构造函数
	Student(int age = 18, int score = 80) :m_score(score), Person(age) {

	}

	// 构造和析构顺序相反：先子类，再父类
	~Student() {
		cout << "~Student" << endl;
	}
};

int main() {
	Student student;

	getchar();
	return 0;
}