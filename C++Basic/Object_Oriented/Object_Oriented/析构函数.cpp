#include <iostream>
using namespace std;

// 构造函数、析构函数要声明为public，才能被外界正常使用

//特点 
//	函数名以~开头，
//	与类同名，
//	无返回值（void都不能写），
//	无参，
//	不可以重载，
//	有且只有一个析构函数


class Person {
	int m_age;
public:
	// 对象创建完毕的时候调用
	Person() {
		cout << "Person()" << endl;
		this->m_age = 0;
	}

	Person(int age) {
		cout << "Person(int age)" << endl;
		this->m_age = age;
	}

	// 对象销毁(内存被回收)的时候调用
	~Person() {
		cout << "~Person()" << endl;
	}
};

//void test() {
//	Person person;
//}

int main() {
	Person person;

	// 栈空间：{}作用域内创建，出作用域时释放
	/*{
		Person person;
	}*/

	// 堆空间：手动释放
	Person *p = new Person();
	delete p;

	// 通过malloc分配的对象free的时候不会调用构造函数
	/*Person *p = (Person *) malloc(sizeof(Person));
	free(p);*/

	getchar();
	return 0;
}