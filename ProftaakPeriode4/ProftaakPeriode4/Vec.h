#pragma once

// 3 dimensional float matrix
class Vec3f
{
public:
	union
	{
		struct
		{
			float x, y, z;
		};
		float v[3];
	};
	Vec3f();
	Vec3f(Vec3f &other);
	Vec3f(float x, float y, float z);
	float& operator [](int);

	Vec3f operator -(const Vec3f&) const;
	void operator -=(const Vec3f&);

	Vec3f operator +(const Vec3f&) const;
	void operator +=(const Vec3f&);

	Vec3f operator -(const float&) const;
	void operator -=(const float&);

	Vec3f operator +(const float&) const;
	void operator +=(const float&);

	Vec3f operator /(const float&) const;
	void operator /=(const float&);

	Vec3f operator *(const float&) const;
	void operator *=(const float&);
};

// 2 dimensional float matrix
class Vec2f
{
public:
	union
	{
		struct
		{
			float x, y;
		};
		float v[2];
	};
	Vec2f();
	Vec2f(float x, float y);
	Vec2f(Vec2f &other);
	float& operator [](int);
};

// 2 dimensional int matrix
class Vec2i
{
public:
	union
	{
		struct
		{
			int x, y;
		};
		int v[2];
	};
	Vec2i();
	Vec2i(int x, int y);
	Vec2i(Vec2i &other);
	int& operator [](int);
};