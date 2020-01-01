//运算符重载注意点

//有些运算符不可以被重载，比如 
//	对象成员访问运算符：.
//	域运算符：::
//	三目运算符： ? : 
//	sizeof

//有些运算符只能重载为成员函数，比如 
//	赋值运算符： = 
//	下标运算符：[] 
//	函数运算符：() 
//	指针访问成员：->

#include <iostream>
#include "Point.h"
using namespace std;

int main() {
	Point p0(5, 10);
	Point p1(30, 70);
	Point p2(10, 40);
	Point p3 = p1++ - p2;

	// 运算符重载：最好保留运算符以前的语义
	// Java.toString   OC.description
	cout << p0 << p1 << p2 << p3 << endl;

	getchar();
	getchar();
	return 0;
}


//////////////////////////////////////////////////////////////////
//#include <iostream>
//#include "String.h"
//using namespace std;
//
//int main() {
//
//	{
//		String str1 = "1111";
//		String str2 = "2222";
//
//		// ASCIIֵ
//		// strcmp
//
//		/*if (str2 > str1) {
//
//		}
//		if (str2 == str1) {
//
//		}
//		strcat
//		String str3 = str1 + str2;
//		str1 += str2;*/
//
//		/*String str2 = "2222";
//
//		str1 = "324234";
//		cout << str1 << endl;
//
//		str1 = str1;
//		cout << str1 << endl;
//
//		str1 = str2;
//		cout << str1 << endl; */
//	}
//

//	{
//		String str1 = "abc";
//		cout << (str1 > "aac") << endl;
//	}
//
//	// str1 = 12234
//
//	getchar();
//	return 0;
//}