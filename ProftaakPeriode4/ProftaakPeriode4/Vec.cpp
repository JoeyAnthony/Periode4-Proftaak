#include "Vec.h"

Vec3f::Vec3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vec3f::Vec3f()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
Vec3f::Vec3f(Vec3f &other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

float& Vec3f::operator [](int index)
{
	return v[index];
}

Vec3f Vec3f::operator-(const Vec3f& other) const
{
	return Vec3f(this->x - other.x, this->y - other.y, this->z - other.z);
}

void Vec3f::operator-=(const Vec3f& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

Vec3f Vec3f::operator+(const Vec3f& other) const
{
	return Vec3f(this->x + other.x, this->y + other.y, this->z + other.z);
}

void Vec3f::operator+=(const Vec3f& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}

Vec3f Vec3f::operator-(const float& number) const
{
	return Vec3f(x - number, y - number, z - number);
}

void Vec3f::operator-=(const float& number)
{
	x -= number;
	y -= number;
	z -= number;
}

Vec3f Vec3f::operator+(const float& number) const
{
	return Vec3f(x + number, y + number, z + number);
}

void Vec3f::operator+=(const float& number)
{
	x += number;
	y += number;
	z += number;
}

Vec3f Vec3f::operator/(const float& number) const
{
	return Vec3f(x / number, y / number, z / number);
}

void Vec3f::operator/=(const float& number)
{
	x /= number;
	y /= number;
	z /= number;
}

Vec3f Vec3f::operator*(const float& number) const
{
	return {
		x * number,
		y * number,
		z * number
	};
}

void Vec3f::operator*=(const float& number)
{
	x *= number;
	y *= number;
	z *= number;
}

Vec2f::Vec2f(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vec2f::Vec2f()
{
	this->x = 0;
	this->y = 0;
}
Vec2f::Vec2f(Vec2f &other)
{
	this->x = other.x;
	this->y = other.y;
}

float& Vec2f::operator [](int index)
{
	return v[index];
}

Vec2i::Vec2i(int x, int y)
{
	this->x = x;
	this->y = y;
}
Vec2i::Vec2i()
{
	this->x = 0;
	this->y = 0;
}
Vec2i::Vec2i(Vec2i &other)
{
	this->x = other.x;
	this->y = other.y;
}

int& Vec2i::operator [](int index)
{
	return v[index];
}
