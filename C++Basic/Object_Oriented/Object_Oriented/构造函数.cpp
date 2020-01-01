//构造函数（也叫构造器Constructor）
//	在对象创建的时候自动调用，一般用于完成对象的初始化工作

//特点 
//	函数名与类同名，无返回值（void都不能写），可以有参数，可以重载，可以有多个构造函数 
//	一旦自定义了构造函数，必须用其中一个自定义的构造函数来初始化对象

//注意 
//	通过malloc分配的对象不会调用构造函数


#include <iostream>
using namespace std;

struct Person {
	int m_age;

	// 无参数
	Person() {
		cout << "Person()" << endl;
		// this->m_age = 0;
		memset(this, 0, sizeof(Person));
	}

	// 有参数重载
	Person(int age) {
		cout << "Person(int age)" << endl;
		this->m_age = age;
	}
};

// 全局区
Person g_person1; // Person()
Person g_person2(); // 这是一个函数声明，函数名叫g_person2，无参，返回值类型是Person
Person g_person3(10); // Person(int age)

int main() {
	// 栈空间
	Person person1; // Person()
	Person person2(); // 这是一个函数声明，函数名叫person2，无参，返回值类型是Person
	Person person3(20);  // Person(int age) 

	// 堆空间
	Person* p1 = new Person; // Person()
	Person* p2 = new Person(); // Person()
	Person* p3 = new Person(30);  // Person(int age)

	delete p1;
	delete p2;
	delete p3;

	// 通过malloc分配的对象不会调用构造函数。new会调用构造函数
	Person* p = (Person*)malloc(sizeof(Person));  
	p->m_age = 10;

	// 在某些特定的情况下，编译器才会为类生成空的无参的构造函数。见虚函数部分

	getchar();
	return 0;
}