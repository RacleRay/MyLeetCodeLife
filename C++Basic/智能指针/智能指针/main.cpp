//传统指针存在的问题 
//	需要手动管理内存 
//	容易发生内存泄露（忘记释放、出现异常等） 
//	释放之后产生野指针

//内存泄露
#include <iostream>
using namespace std;

void test() {
	throw 6;
}

void test1() {
	try {
		int* p = new int();

		test();

		// 没有执行，内存泄露
		delete p;

		p = nullptr; // 防止指向释放的内存（野指针）
	}
	catch (...) {
		cout << "出现异常" << endl;
	}
}


//智能指针就是为了解决传统指针存在的问题 
//	auto_ptr：属于C++98标准，在C++11中已经不推荐使用（有缺陷，比如不能用于数组） 
//	shared_ptr：属于C++11标准 
//	unique_ptr：属于C++11标准

class Person {
public:
	Person() {
		cout << "Person()" << endl;
	}
	~Person() {
		cout << "~Person()" << endl;
	}

	void run() {
		cout << "Person::run()" << endl;
	}
};


void test_auto_ptr() {
	cout << "1" << endl;
	{
		//Person *p = new Person();  // 手动构建对象，需要手动释放

		// 支持泛型
		// 注意不要指向栈空间，可能出现double free
		auto_ptr<Person> p(new Person());
		p->run();

		// auto_ptr不能用于数组
		//auto_ptr<Person> p(new Person[3]);  // 会出现错误
	}
	cout << "2" << endl;
}


void test_shared_ptr() {
	cout << "1" << endl;
	{
		// 针对数组的用法
		shared_ptr<Person[]> p(new Person[3]);  // 正确

		// 多个shared_ptr可以指向同一个对象，当最后一个shared_ptr在作用域范围内结束时，对象才会被自动释放
		//   一个shared_ptr会对一个对象产生强引用（strong reference）
		//	 每个对象都有个与之对应的 强引用计数 ，记录着当前对象被多少个shared_ptr强引用着 
		//		可以通过shared_ptr的use_count函数获得强引用计数
		//	 当有一个新的shared_ptr指向对象时，对象的强引用计数就会 + 1
		//	 当有一个shared_ptr销毁时（比如作用域结束），对象的强引用计数就会 - 1
		//	 当一个对象的强引用计数为0时（没有任何shared_ptr指向对象时），对象就会自动销毁（析构）

		shared_ptr<Person> p1(new Person);
		shared_ptr<Person> p2 = p1;
		cout << "2" << endl;
	}
	cout << "3" << endl;

	//shared_ptr的注意点
	//	不要使用裸指针来初始化智能指针，比如以下代码: 出现两次析构
	Person* p = new Person();
	{
		shared_ptr<Person> p1(p);
	}  // ~Person()

	{
		shared_ptr<Person> p2(p);
	}  // ~Person()

	//	可以通过一个已存在的智能指针初始化一个新的智能指针
	shared_ptr<Person> p3(new Person());
	shared_ptr<Person> p4(p3);
}


// shared_ptr的循环引用
class Person {
public:
	// Car *m_car;
	shared_ptr<Car> m_car = nullptr;
	Person() {
		cout << "Person()" << endl;
	}
	~Person() {
		cout << "~Person()" << endl;
	}
	void run() {
		cout << "Person::run()" << endl;
	}
};

class Car {
public:
	// Person *m_person;
	// shared_ptr会增加 强引用计数
	// shared_ptr<Person> m_person = nullptr;
	// 弱引用不会增加强引用计数
	// 因此不存在两个存在互相指向时，析构后，强引用计数不为0的情况（内存不会回收，内存泄漏）
	weak_ptr<Person> m_person;
	Car() {
		cout << "Car()" << endl;
	}
	~Car() {
		cout << "~Car()" << endl;
	}
};

void test_circle_ref_of_shared_ptr() {
	// 传统指针不存在强引用计数引起的循环引用
	/*Person *p = new Person();
	p->m_car = new Car();
	p->m_car->m_person = p;*/

	cout << "1" << endl;

	{
		shared_ptr<Person> person(new Person());
		shared_ptr<Car> car(new Car());
		person->m_car = car;
		car->m_person = person;
	}

	cout << "2" << endl;
}



// unique_ptr
// unique_ptr也会对一个对象产生强引用，它可以确保同一时间只有1个指针指向对象（强引用）

// 当unique_ptr销毁时（作用域结束时），其指向的对象也就自动销毁了

// 可以使用std::move函数转移unique_ptr的所有权
int test_unique_ptr() {

	{
		unique_ptr<Person> p1(new Person());
		{	
			// 对象的指向权，从p1转移给p2
			unique_ptr<Person> p2 = std::move(p1);
			cout << "1" << endl;
		}
		cout << "2" << endl;
	}

	getchar();
	return 0;
}



////////////////////////////////////////////////////////////////
//智能指针的简单自实现
template <class T>
class SmartPointer {
	T* m_pointer;

public:
	SmartPointer(T* pointer) :m_pointer(pointer) { }
	~SmartPointer() {
		if (m_pointer == nullptr) return;
		// 当SmartPointer对象销毁时，自动delete pointer指向的对象
		delete m_pointer;
	}
	// 运算符重载使得SmartPointer对象可以使用指针运算符
	T* operator->() {
		return m_pointer;
	}
};


int main() {

	cout << "1" << endl;
	{
		SmartPointer<Person> p(new Person());
		p->run();
	}
	cout << "2" << endl;

	getchar();
	return 0;
}