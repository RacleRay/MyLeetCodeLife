// 命名空间可以用来避免命名冲突

// 创建
//	可嵌套
//  默认整体的命名空间没有名字，::表示
namespace MJ {
	namespace SS {
		int g_no;
		class Person {

		};

		void test() {

		}
	}

	void test() {

	}
}


void test() {

}

// 使用
void test3() {
	test();
	// 默认的命名空间，没有名字
	::test();

	::MJ::SS::g_no = 30;

	MJ::SS::g_no = 20;

	using namespace MJ;
	SS::g_no = 30;

	using namespace MJ::SS;
	g_no = 10;
}

// using namespace std，就是iostream中定义的std命名空间

// Java中通过包文件夹形式区分命名空间
//  package com.mj.ss;  指定
//  或者
//  com.mj.ss.Class_name object_name;   创建相应空间中的类