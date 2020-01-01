#include <iostream>
using namespace std;

class Animal {
public:
	int m_age;
	virtual void speak() {
		cout << "Animal::speak()" << endl;
	}
	virtual void run() {
		cout << "Animal::run()" << endl;
	}
	virtual ~Animal() {
		cout << "~Animal()" << endl;
	}
};

class Cat : public Animal {
public:
	int m_life;
	Cat() :m_life(0) {}
	void speak() {
		cout << "Cat::speak()" << endl;
	}
	void run() {
		cout << "Cat::run()" << endl;
	}
	~Cat() {
		cout << "~Cat()" << endl;
	}
};


// 当存在父类指针指向子类对象的情况下，应该将析构函数声明为虚函数
//	因为new的是Cat对象，而非虚函数会直接根据Animal* 类型处理析构函数
//	声明为虚函数，才能调用Cat对象对应的析构函数

// 子类的析构函数也自然为虚函数
int main() {
	Animal* cat1 = new Cat();
	cat1->speak();
	cat1->run();

	delete cat1;

	getchar();
	return 0;
}