#include <iostream>
using namespace std;


// 继承，可以让子类拥有父类的所有成员（变量\函数）

struct Person {
	int m_age;
	void run() {
		cout << "run()" << endl;
	}
};

struct Student : Person {
	int m_score;
	void study() {
		cout << "study()" << endl;
	}
};

struct Worker : Person {
	int m_salary;
	void work() {
		cout << "work()" << endl;
	}
};

// Java：所有的Java对象最终都继承自java.lang.Object这个类
// OC：所有的OC对象最终都继承自NSObject这个类

void test() {
	/*Student student;
	student.m_age = 18;
	student.m_score = 100;
	student.run();
	student.study();*/
}

struct Person {
	int m_age;
};

struct Student : Person {
	int m_no;
};

struct GoodStudent : Student {
	int m_money;
};

int main() {
	// 12
	GoodStudent gs;
	// 其储存变量的地址，父类的排在低地址，子类的排在高地址（大）
	gs.m_age = 20;
	gs.m_no = 1;
	gs.m_money = 2000;

	cout << &gs << endl;
	cout << &gs.m_age << endl;
	cout << &gs.m_no << endl;
	cout << &gs.m_money << endl;

	// 4
	Person person;

	// 8
	Student stu;

	cout << sizeof(Person) << endl;
	cout << sizeof(Student) << endl;
	cout << sizeof(GoodStudent) << endl;

	getchar();
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// 成员访问权限：
// 成员访问权限、继承方式有3种 
//	public：公共的，任何地方都可以访问（struct定义类时默认） 
//	protected：子类内部、当前类内部可以访问 
//	prvate：私有的，只有当前类内部可以访问（class定义类时默认）

// 访问权限：
//	在定义类时，声明

// 继承方式：
//	在继承时声明
//  class Student: private Person{};
//  class Student: public Person{};

// 子类内部访问父类成员的权限，是以下2项中权限最小的那个 
//	1. 成员本身的访问权限 
//	2. 上一级父类的继承方式

// 开发中用的最多的继承方式是public，这样能保留父类原来的成员访问权限

// 访问权限不影响对象的内存布局

// 
#include <iostream>
using namespace std;

class Person {
private:
	string m_name;

public:
	int m_age;
	void run() {

	}

	// 子类可以通过public方法进行修改
	void setName() {
		m_name = "reseted";
	}
};

class Student : public Person {
	int m_no;
	void study() {
		m_age = 10;
	}
};

class GoodStudent : public Student {
	int m_money;
	void work() {
		m_age = 10;
	}
};