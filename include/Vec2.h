#ifndef Vec2_H
#define Vec2_H
#include <cmath>
struct Vec2{
	float x, y;
};

inline
Vec2 Vec2FromAngle(float rad)
{
	return Vec2{cos(rad), sin(rad)};
}

inline
float Vec2Length(Vec2 v)const
{
	return sqrt(v.x * v.x + v.y * v.y);
}

inline
float Vec2Angle(Vec2 v)const
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
Vec2 operator*(Vec2 a, float k)
{
	return Vec2{a.x * k, a.y * k};
}

inline
Vec2 operator*(float k, Vec2 a)
{
	return Vec2{a.x * k, a.y * k};
}

inline
void operator *=(Vec2 & a, float k)
{
	a.x *= k;
	a.y *= k;
}

inline
Vec2 operator/(Vec2 a, float k)
{
	return Vec2{a.x / k, a.y / k};
}

inline
Vec2 operator/(float k, Vec2 a)
{
	return Vec2{k / a.x,  k / a.y};
}

inline
void operator /=(Vec2 & a, float k)
{
	a.x /= k;
	a.y /= k;
}
#endif
