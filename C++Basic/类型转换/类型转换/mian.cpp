//C语言风格的类型转换符 
//	(type)expression 
//	type(expression)


//C++中有4个类型转换符 
//	static_cast 
//	dynamic_cast 
//	reinterpret_cast 
//	const_cast 

//使用格式：xx_cast<type>(expression)


#include <iostream>
using namespace std;

class Person {
public:
	int m_age;
	virtual void run() { }
};

class Student : public Person {
public:
	int m_score;
};

void test_const_cast() {
	const Person* p1 = new Person();

	//一般用于去除const属性，将const转换成非const
	Person* p2 = const_cast<Person*>(p1);
	Person* p3 = (Person*)p1;


	p2->m_age = 20;
	p3->m_age = 30;

	cout << p1->m_age << endl;
}

class Car {

};

void test_dynamic_cast() {
	Person* p1 = new Person();
	Person* p2 = new Student();

	/*Student *stu1 = (Student *) p1;
	Student *stu2 = (Student *) p2;
	Car *car = (Car *) p2;*/

	// 一般用于多态类型（要有virtual func声明）的转换，有运行时安全检测
	// 不安全，子类指针指向了父类对象p1，编译器会直接赋值* stu1为00000000
	Student* stu1 = dynamic_cast<Student*>(p1);  // NULL
	// 安全
	Student* stu2 = dynamic_cast<Student*>(p2);
	
	// 不相关类型转换检测
	// 运行时进行安全检测，编译器会直接赋值* car为00000000
	Car* car = dynamic_cast<Car*>(p2);  // NULL

	cout << stu1 << endl;
	cout << stu2 << endl;
	cout << car << endl;
}

void test_static_cast() {
	/*对比dynamic_cast，缺乏运行时安全检测 
		◼ 不能交叉转换（不是同一继承体系的，无法转换） 
		◼ 常用于基本数据类型的转换、非const转成const 
		◼ 适用范围较广*/
	Person* p1 = new Person();
	Person* p2 = new Student();

	Student* stu1 = static_cast<Student*>(p1);
	Student* stu2 = static_cast<Student*>(p2);

	int i = 10;
	double d = i;

	cout << stu1 << endl;
	cout << stu2 << endl;
}

void test_reinterpret_cast() {
	/*属于比较底层的强制转换，没有任何类型检查和格式转换，仅仅是简单的二进制数据拷贝 
	可以交叉转换 
	可以将指针和整数互相转换*/

	// 0A 00 00 00
	int a = 10;
	// 0A 00 00 00 00 00 00 00
	// 实际上浮点数的内存储存方式是如下的方式，和整型数的储存方式不同
	// 因为浮点数存储方式是： 符号位 指数位 尾数部分
	// 00 00 00 00 00 00 24 40
	// double b = 10;

	// 直接二进制位内存数据拷贝
	// 0A 00 00 00 cc cc cc cc
	double b = reinterpret_cast<double&>(a);

	Person* p1 = new Person();
	Person* p2 = new Student();

	Student* stu1 = reinterpret_cast<Student*>(p1);
	Student* stu2 = reinterpret_cast<Student*>(p2);
	Car* car = reinterpret_cast<Car*>(p2);

	cout << p1 << endl;
	cout << p2 << endl;
	cout << p2 << endl;

	cout << stu1 << endl;
	cout << stu2 << endl;
	cout << car << endl;
}


int main() {

}