#ifndef Vec2_H
#define Vec2_H
#include <cmath>
struct Vec2{
	double x, y;
};

inline
Vec2 Vec2FromAngle(double rad)
{
	return Vec2{cos(rad), sin(rad)};
}

inline
double Vec2Length(Vec2 v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

inline
double Vec2Angle(Vec2 v)
{
	return atan2(v.y, v.x);
}

inline
Vec2 operator+(Vec2 a, Vec2 b)
{
	return Vec2{a.x + b.x, a.y + b.y};
}

inline
void operator+=(Vec2 & a, Vec2 b)
{
	a.x += b.x;
	a.y += b.y;
}

inline
Vec2 operator-(Vec2 a, Vec2 b)
{
	return Vec2{a.x - b.x, a.y - b.y};
}

inline
void operator-=(Vec2 & a, Vec2 b)
{
	a.x -= b.x;
	a.y -= b.y;
}

inline
Vec2 operator-(Vec2 a)
{
	return Vec2{-a.x, -a.y};
}

inline
Vec2 operator*(Vec2 a, double k)
{
	return Vec2{a.x * k, a.y * k};
}

inline
Vec2 operator*(double k, Vec2 a)
{
	return Vec2{a.x * k, a.y * k};
}

inline
void operator *=(Vec2 & a, double k)
{
	a.x *= k;
	a.y *= k;
}

inline
Vec2 operator/(Vec2 a, double k)
{
	return Vec2{a.x / k, a.y / k};
}

inline
Vec2 operator/(double k, Vec2 a)
{
	return Vec2{k / a.x,  k / a.y};
}

inline
void operator /=(Vec2 & a, double k)
{
	a.x /= k;
	a.y /= k;
}
#endif
