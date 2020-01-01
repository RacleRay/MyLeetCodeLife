#include <iostream>
using namespace std;


// 如果自定义了构造函数，
// 除了全局区，其他内存空间的成员变量默认都不会被初始化，需要开发人员手动初始化

struct Person {
	int m_age;

	/*Person() {
		cout << "Person()" << endl;
		this->m_age = 0;
	}*/

	// 全部成员变量初始化为0简便方式
	/*Person() {
		memset(this, 0, sizeof(Person));
	}*/
};

// 没有构造函数，默认条件下：全局区（成员变量初始化为0）
// 有构造函数: 全局区（成员变量初始化为0）
Person g_person;

int main() {
	// 没有构造函数，默认条件下：栈空间（成员变量没有初始化）
	Person person;

	// 堆空间
	Person* p1 = new Person; // 没有构造函数，默认条件下：成员变量没有初始化
	Person* p2 = new Person(); // 没有构造函数，默认条件下：成员变量有初始化0

	cout << "g_person " << g_person.m_age << endl;
	cout << "p1 " << p1->m_age << endl;
	cout << "p2 " << p2->m_age << endl;

	getchar();
	return 0;
}