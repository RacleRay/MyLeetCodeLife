//泛型，是一种将类型参数化以达到代码复用的技术，C++中使用模板来实现泛型

//模板的使用格式如下 
//	template <typename\class T> 
//	typename和class是等价的

// 模板没有被使用时，是不会被实例化出来的
// 模板的声明和实现如果分离到.h和.cpp中，会导致链接错误
//	 每个.cpp文件是单独编译的，当模板函数只在某个文件中声明，没有在该文件中调用，是不会生成实例化的代码的
//   因此在汇编代码链接时，call [函数地址] 是找不到地址的

// 一般将模板的声明和实现统一放到一个.hpp文件中

#include <iostream>
#include "Array.hpp"
using namespace std;

class Person {
	friend ostream& operator<<(ostream&, const Person&);
	int m_age;
public:
	Person(int age = 0) :m_age(age) { }
};

ostream& operator<<(ostream& cout, const Person& person) {
	return cout << "age=" << person.m_age;
}


int main() {

	Array<Person> array(3);
	array.add(Person(11));
	array.add(Person(12));
	array.add(Person(13));
	// array.display();

	cout << array << endl;

	getchar();
	return 0;
}