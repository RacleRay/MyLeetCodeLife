// 泛型Lambda表达式：参数列表中的 auto

#include <iostream>
using namespace std;

auto func = [](auto a, auto b) {return a + b; };


// 对捕获的变量进行初始化
int a;
auto func_2 = [a = 10](){
	cout << a << endl;
};



// C++17
int main() {
	//可以进行初始化的if、switch语句
	if (int a = 10; a > 10) {
		a = 1;
	} else if (int b = 20; a > 5 && b > 10) {
		b = 2;
		a = 2;
	}
}
