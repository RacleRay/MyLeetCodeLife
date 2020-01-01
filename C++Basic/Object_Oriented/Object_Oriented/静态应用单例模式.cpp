#include <iostream>
using namespace std;

/*
单例模式：
在程序运行过程中，可能会希望某些类的实例对象永远只有一个

	1.把构造函数，析构函数私有化
	2.定义一个私有的静态成员变量指针，用于指向单例对象
	3.提供一个公共的返回单例对象的静态成员函数
*/


class Rocket {
public:
	static Rocket* sharedRoc(){
		if (ms_rocket == NULL) {
			ms_rocket = new Rocket();
		}
		return ms_rocket;
	}

	static void deleteRocket() {
		if (ms_rocket == NULL) return;

		delete ms_rocket;  // 回收堆空间
		ms_rocket = NULL;  // 清零地址空间，（清理遗留痕迹）
	}

private:
	Rocket() {
	}
	~Rocket() {
	}
	static Rocket* ms_rocket;
};

int main() {
	Rocket* p1 = Rocket::sharedRoc();
	Rocket::deleteRocket();

	Rocket* p2 = Rocket::sharedRoc();
	Rocket::deleteRocket();

	/*Rocket *p1 = Rocket::sharedRoc();
	Rocket *p2 = Rocket::sharedRoc();
	Rocket *p3 = Rocket::sharedRoc();
	Rocket *p4 = p3->sharedRoc();

	cout << p1 << endl;
	cout << p2 << endl;
	cout << p3 << endl;
	cout << p4 << endl;*/

	getchar();
	return 0;
}
