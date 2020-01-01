#include <iostream>
using namespace std;


// 父类指针可以指向子类对象，是安全的，开发中经常用到（继承方式必须是public）
// 子类指针指向父类对象是不安全的


class Person {
public:
	int m_age;
};

// Student是一个Person
class Student : public Person {
public:
	int m_score;
};

int main() {
	// 学生是一个人
	// 父类指针的访问范围不会超过子类的大小
	//Person *stu = new Student();
	//stu->m_age = 10;

	// 将指向父类的子类指针强制转化为子类指针类型，欺骗编译器
	// 那么子类指针的访问范围可能超过父类对象大小的范围
	/*Student *p = (Student *) new Person();
	p->m_age = 10;
	p->m_score = 20;*/

	getchar();
	return 0;
}


///////////////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

	/*
	面向对象的3大特性：
	封装
	继承
	多态

	重写（override）：子类重写（覆盖）父类的方法
	重载（overload）
	*/

// 多态是面向对象非常重要的一个特性 
//	同一操作作用于不同的对象，可以有不同的解释，产生不同的执行结果 
//	在运行时，可以识别出真正的对象类型，调用对应子类中的函数


// 下面没有virtual时是有问题的实现

// 多态的要素 
//	1. 子类重写父类的成员函数（override） 
//	2. 父类指针指向子类对象 
//	3. 利用父类指针调用重写的成员函数
// C++中的多态还要通过虚函数（virtual function）来实现
class Animal {
public:
	virtual void run() {
		cout << "Animal::run()" << endl;
	}
};

class Cat : public Animal {
public:
	void run() {
		cout << "Cat::run()" << endl;
	}
};

class Dog : public Animal {
public:
	void run() {
		cout << "Dog::run()" << endl;
	}
};

class Pig : public Animal {
public:
	void run() {
		cout << "Pig::run()" << endl;
	}
};

// 默认情况下，编译器只会根据指针类型调用对应的函数，不存在多态
// 输入不同对象都会调用Animal::run()
// 但是virtual可以优化这一问题。
void liu(Animal *animal) {
	animal->run();
}

//多态的要素 
//	1. 子类重写父类的成员函数（override） 
//	2. 父类指针指向子类对象 
//	3. 利用父类指针调用重写的成员函数

// C++中的多态还要通过虚函数（virtual function）来实现
//	virtual function实现时，call的不是Animal::run()，而是eax寄存器中的地址对应的函数
//	virtual function实现时，对象会创建一段内存地址（最前面的4字节），对应一个新创建的虚表，虚表空间储存着virtual function对应的地址
//	调用时，eax寄存器调用虚表中的地址对应的函数
//	子类重写时，虚表中的函数变为重写函数的地址
//  每一类对象都有一张共有的虚表，因为对应相同的方法函数代码

// 相当于virtual function函数地址动态绑定到对象
// 若子类中virtual function没有重写，那么编译时，保持父类的虚表中的函数地址

// 虚函数：被virtual修饰的成员函数
// 只要在父类中声明为虚函数，子类中重写的函数也自动变成虚函数（也就是说子类中可以省略virtual关键字）

int main() {
	liu(new Dog());
	liu(new Cat());
	liu(new Pig());

	getchar();
	return 0;
}


//int main(){
//	Animal *animal = new Pig();
//	animal->run();
//
//	getchar();
//	return 0;
//}


// 调用父类成员函数：
//	直接 Animal::run()