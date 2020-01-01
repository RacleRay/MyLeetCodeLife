//特点 
//	一种便捷的初始化成员变量的方式 
//	只能用在构造函数中 
//	初始化顺序只跟成员变量的声明顺序有关

#include <iostream>
using namespace std;


int myAge() {
	cout << "myAge()" << endl;
	return 30;
}

int myHeight() {
	cout << "myHeight()" << endl;
	return 180;
}

struct Person {
	//	构造函数的初始化顺序只跟成员变量的声明顺序有关
	int m_age;
	int m_height;

	Person() {
		this->m_age = 0;
		this->m_height = 0;
	}

	// 初始化列表 :m_age(age), m_height(height)，和上面的代码等价
	/*Person(int age, int height) :m_height(height), m_age(m_height)   {

	}*/

	// 那么可以传入有返回值的函数
	//	构造函数的初始化顺序只跟成员变量的声明顺序有关
	Person(int age, int height) :m_height(myHeight()), m_age(myAge()) {

	}

	void display() {
		cout << "m_age is " << this->m_age << endl;
		cout << "m_height is " << this->m_height << endl;
	}
};


//如果函数声明和实现是分离的 
//	初始化列表只能写在函数的实现中: 因为其本质就是和函数实现中的代码 
//	默认参数只能写在函数的声明中


// 构造函数的相互调用必须使用初始化列表
struct Person {
	int m_age;
	int m_height;

	// 初始化列表将对象的地址传给了构造函数Person(0, 0)，而没有创建一个临时对象
	Person() :Person(0, 0) {
		cout << "Person() " << this << endl;
	}

	// 直接调用构造函数，会创建一个临时对象，传入一个临时的地址值给this指针
	// Person(){
	//	 Person(0, 0);
	// }
};