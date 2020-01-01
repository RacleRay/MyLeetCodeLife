#include "Point.h"

Point::Point(int x, int y) :m_x(x), m_y(y) { }

// 运算符（操作符）重载
// 第一个const是声明返回值，第二个const是因为，当出现p1 + p2 + p3，其中p1 + p2
// 返回const对象，而const对象只能调用const成员函数（防止成员被修改，const对象嘛）
// 因此，加上第二个const
Point Point::operator+(const Point& point) const {
	return Point(this->m_x + point.m_x, this->m_y + point.m_y);
}

Point Point::operator-(const Point& point) const {
	return Point(this->m_x - point.m_x, this->m_y - point.m_y);
}

// 负数定义
const Point Point::operator-() const {
	return Point(-this->m_x, -this->m_y);
}

// 返回对象引用，防止中间对象产生
// 若返回具体的对象Point（1， 2），就需要指明const
Point& Point::operator+=(const Point& point) {
	this->m_x += point.m_x;
	this->m_y += point.m_y;
	return *this;
}

Point& Point::operator-=(const Point& point) {
	this->m_x -= point.m_x;
	this->m_y -= point.m_y;
	return *this;
}

bool Point::operator==(const Point& point) {
	// 1 YES true
	// 0 NO false
	/*if (this->m_x == point.m_x && this->m_y == point.m_y) {
		return 1;
	}
	else {
		return 0;
	}*/
	return (this->m_x == point.m_x) && (this->m_y == point.m_y);
}

bool Point::operator!=(const Point& point) {
	return (this->m_x != point.m_x) || (this->m_y != point.m_y);
}

// 前++
Point& Point::operator++() {
	this->m_x++;
	this->m_y++;
	return *this;
}

// 后++
// 使用临时point，返回
// cout对象本身是不能使用=赋值运算的，因为=的重载函数写在private中
const Point Point::operator++(int) {
	Point point(this->m_x, this->m_y);
	this->m_x++;
	this->m_y++;
	return point;
}

// 注意是否声明在成员函数中
// 注意ostream的cout对象不能声明为const
// 注意要返回cout对象，才能再次进行 << 运算
// 相当于*this.operator<<(cout, point)函数调用
ostream& operator<<(ostream& cout, const Point& point) {
	return cout << "(" << point.m_x << ", " << point.m_y << ")";
}

// cin输入，修改point，所以point不能为const
istream& operator>>(istream& cin, Point& point) {
	cin >> point.m_x;
	cin >> point.m_y;
	return cin;
}