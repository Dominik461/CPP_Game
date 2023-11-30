#include "Header/Int2.h"
#include <ostream>

int2::int2()
	:x(0), y(0)
{};

int2::int2(int _x, int _y)
	:x(_x), y(_y)
{};

int2 int2::operator+(const int2 val)
{
	return int2(x + val.x, y + val.y);
}

int2 int2::operator-(const int2 val)
{
	return int2(x - val.x, y - val.y);
}

int2 int2::operator*(const int2 val)
{
	return int2(x * val.x, y * val.y);
}

int2 int2::operator/(const int2 val)
{
	return int2(x / val.x, y / val.y);
}

int2 int2::operator*(const int val)
{
	return int2(x * val, y * val);
}

int2 int2::operator/(const int val)
{
	return int2(x / val, y / val);
}

int2& int2::operator+=(const int2& val)
{
	x += val.x;
	y += val.y;
	return *this;
}

int2& int2::operator-=(const int2& val)
{
	x -= val.x;
	y -= val.y;
	return *this;
}

int2& int2::operator*=(const int2& val)
{
	x *= val.x;
	y *= val.y;
	return *this;
}

int2& int2::operator/=(const int2& val)
{
	x /= val.x;
	y /= val.y;
	return *this;
}

int2& int2::operator*=(const int val)
{
	x *= val;
	y *= val;
	return *this;
}

int2& int2::operator/=(const int val)
{
	x /= val;
	y /= val;
	return *this;
}

bool operator==(const int2& lhs, const int2& rhs)
{
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool operator!=(const int2& lhs, const int2& rhs)
{
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const int2& a)
{
	os << "(" << a.x << "|" << a.y << ")";
	return os;
}