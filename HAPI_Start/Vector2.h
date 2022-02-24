#pragma once

#include <iostream>
using namespace std;

/*
	Vector2 implements positions and vectors.
*/

class Vector2 {
private:

public:
	float x{ 0 }, y{ 0 };

	Vector2() = default;
	Vector2(float X, float Y);
	Vector2(const Vector2& p);

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;

	Vector2 operator*(const float& other) const;
	Vector2 operator/(const float& other) const;

	void operator=(const Vector2& other);

	bool operator==(const Vector2& rhs) const;
	bool operator!=(const Vector2& rhs) const;

	bool isNull() const;
	float lenght() const;
	void normalize();
};

float Distance(Vector2 a, Vector2 b);
Vector2 Interpolate(Vector2 Start, Vector2 End, float f);

