#pragma once

#include <iostream>
using namespace std;

class Point {
	friend ostream& operator<<(ostream&, const Point&);
	friend istream& operator>>(istream&, Point&);
	int m_x;
	int m_y;
public:
	Point(int x, int y);

	// 运算符（操作符）重载
	Point operator+(const Point& point) const;
	Point operator-(const Point& point) const;
	// 负号
	const Point operator-() const;
	// 自增自减不需要创建新对象
	Point& operator+=(const Point& point);
	Point& operator-=(const Point& point);

	bool operator==(const Point& point);
	bool operator!=(const Point& point);

	// 前++
	Point& operator++();
	// 后++：注意要写int，一般都这样写。返回了中间对象
	const Point operator++(int);
};