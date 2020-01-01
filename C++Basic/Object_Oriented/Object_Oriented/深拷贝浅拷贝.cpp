//编译器默认的提供的拷贝是浅拷贝（shallow copy） 
//	将一个对象中所有成员变量的值拷贝到另一个对象 
//	如果某个成员变量是个指针，只会拷贝指针中存储的地址值，并不会拷贝指针指向的内存空间 
//	可能会导致堆空间多次free的问题

//如果需要实现深拷贝（deep copy），就需要自定义拷贝构造函数(拷贝构造函数) 
//	将指针类型的成员变量所指向的内存空间，拷贝到新的内存空间


#include <iostream>
using namespace std;

// 浅拷贝（shallow copy）：指针类型仅仅是拷贝地址值
// 深拷贝（deep copy）：拷贝内容到新申请的内存空间

class Car {
	int m_price;
	char* m_name;
	void copy(const char* name = NULL) {
		if (name == NULL) return;

		// 在堆空间申请空间，将堆空间的内容复制到堆空间，解决堆空间指向栈空间的问题
		// 申请堆空间存储字符串内容。  +1为'\0'。  ｛｝表示初始化为全0
		this->m_name = new char[strlen(name) + 1]{};
		// 拷贝字符串内容到堆空间(string copy)
		strcpy(this->m_name, name);
	}
public:
	Car(int price = 0, const char* name = NULL) :m_price(price) {
		copy(name);
		cout << "Car(int, const char *)" << endl;
	}

	// 拷贝构造函数实现深拷贝，m_price拷贝，new一段内存空间
	Car(const Car& car) :m_price(car.m_price) {
		copy(car.m_name);
		cout << "Car(const Car &car)" << endl;
	}

	~Car() {
		if (this->m_name == NULL) return;

		delete[] this->m_name;
		this->m_name = NULL;

		cout << "~Car()" << endl;
	}

	void display() {
		cout << "price is " << this->m_price << ", name is " << this->m_name << endl;
	}
};


int main() {
	//C语言中的字符串，因为'\0'表示结尾的原因，占用的字节数比strlen大1
	//const char* name = "bmw";
	//char name[] = { 'b', 'm', 'w', '\0' };  // 字符数组形式

	char name[] = { 'b', 'm', 'w', '\0' };  // 栈空间
	
	// *car在栈空间，new在堆空间。同时对象的name指针指向了栈空间内的一段内存
	// 堆空间指向栈空间（系统控制释放）是危险的。name指针可能指向了被回收的内存
	Car *car = new Car(100, name); 
	car->display();
	delete car;

	//====================================================================
	// 拷贝问题分析部分
	Car car1(100, "bmw");

	// 将car1的内存空间（8个字节）覆盖car2的内存空间（8个字节）
	// 那么，name指针指向的内存地址，也会指向和Car1的中name指向的内存
	// 同时，car2与car1会反复析构回收同一片内存，这是很危险的
	Car car2 = car1;

	// 因此此条件下，需要深拷贝拷贝构造函数实现深拷贝
	
	Car car3(car1);  // 
	getchar();
	return 0;
}