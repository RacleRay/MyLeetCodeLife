//仿函数（函数对象）：将一个对象当作一个函数一样来使用

//对比普通函数，它作为对象可以保存状态。即可以使用成员变量


#include <iostream>
using namespace std;

class Sum {
	int var_count = 0;
public:
	int operator()(int a, int b) {
		var_count++;
		cout << var_count << endl;
		return a + b;
	}
};