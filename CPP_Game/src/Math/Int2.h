#pragma once
#include <iostream>

struct int2
{
public:
	int x;
	int y;

	int2();
	int2(int _x, int _y);

	int2 operator+(const int2 val);

	int2 operator-(const int2 val);

	int2 operator*(const int2 val);

	int2 operator/(const int2 val);

	int2 operator*(const int val);

	int2 operator/(const int val);

	int2& operator+=(const int2& val);	

	int2& operator-=(const int2& val);

	int2& operator*=(const int2& val);

	int2& operator/=(const int2& val);

	int2& operator*=(const int val);

	int2& operator/=(const int val);

	friend bool operator==(const int2& lhs, const int2& rhs);
	friend bool operator!=(const int2& lhs, const int2& rhs);

	friend std::ostream& operator<<(std::ostream& os, const int2& a);
};