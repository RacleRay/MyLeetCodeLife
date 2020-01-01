//代码段（代码区） 
//	✓用于存放代码，只读
//数据段（全局区） 
//	✓用于存放全局变量等，整个程序过程都存在
//栈空间 
//	✓每调用一个函数就会给它分配一段连续的栈空间，等函数调用完毕后会自动回收这段栈空间 
//	✓自动分配和回收
//堆空间 
//	✓需要主动去申请和释放

// 在程序运行过程，为了能够自由控制内存的生命周期、大小，会经常使用堆空间的内存

#include <iostream>
using namespace std;


void test(){
	// 申请4个字节的连续空间，因为存的是int，所以4个字节。
	int* p = (int*)malloc(4);
	*p = 10;  // 取int大小的空间存10
	free(p);

	// 申请4个字节的连续空间，但是存的是char类型，返回的首字节地址，只能改char大小到的空间
	char* p = (char*)malloc(4);
	// 相当于4个字节大小的字符数组
	*p = 10;
	*(p + 1) = 20;
	*(p + 2) = 30;
	*(p + 3) = 40;
	/*p[0] = 10;
	p[1] = 20;*/
	free(p);  // 释放了申请的4个字节的连续空间
}

// 第二种方式
void test2() {
	int* p = new int;
	int* p2 = new int;

	delete p;
	delete p2;
}

// 第三种方式
void test3() {
	/*int *p = (int *)malloc(sizeof(int) * 10);
	p[0] = 10;
	p[1] = 10;
	p[2] = 10;
	p[3] = 10;

	free(p);*/

	int* p = new int[10];

	delete[] p;
}

//注意 
//	申请堆空间成功后，会返回那一段内存空间的地址 
//	申请和释放必须是1对1的关系，不然可能会存在内存泄露

// 现在的很多高级编程语言不需要开发人员去管理内存（比如Java），屏蔽了很多内存细节，利弊同时存在 
//	利：提高开发效率，避免内存使用不当或泄露 
//	弊：不利于开发人员了解本质，永远停留在API调用和表层语法糖，对性能优化无从下手


//堆空间的初始化
void test4() {
	int* p = (int*)malloc(sizeof(int));
	*p = 0; // 初始化为0，但是当0覆盖不了int大小的空间呢？

	int size = sizeof(int) * 10;
	int* p = (int*)malloc(size);
	// 从p开始的size大小的每一个字节都设置为0。不是将整体10个字节设置为0的意思
	memset(p, 0, size);
}

// C++中new更常用
void test5() {
	int* p0 = new int;  // 没有初始化
	int* p1 = new int();  // 汇编中显示，调用了memset初始化为0
	int* p0 = new int(5);  // 初始化为5
	int* p0 = new int[3];  // 数组元素未被初始化
	int* p0 = new int[3]();  // 初始化为0
	int* p0 = new int[3]{};  // 初始化为0
	int* p0 = new int[3]{ 5 };  // 首元素初始化为5，后面为0
}


//memset
//memset函数是将较大的数据结构（比如对象、数组等）内存清零的比较快的方法
// memset(&对象,0, sizeof(对象))；
// memset(数组,0, sizeof(数组))；


// 对象的内存
//	对象的内存可以存在于3种地方 
//	全局区（数据段）：全局变量 
//	栈空间：函数里面的局部变量 
//	堆空间：动态申请内存（malloc、new等）
struct Person {
	int age;
};

// 全局区
Person g_person;

int test6(){
	// 栈空间
	Person person;

	// 堆空间
	Person* p = new Person;

	return 0;
}