#include "Vector2.h"

// This constructor sets the vector.
Vector2::Vector2(float X, float Y) : x(X), y(Y)
{

}

// This copy constructor sets the vector.
Vector2::Vector2(const Vector2& p)
{
	x = p.x;
	y = p.y;
}

// This overload returns the sum of the 2 vectors.
Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

// This overload returns the subtraction of the 2 vectors.
Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

// This overload returns the multiplication of the vector by the scalar.
Vector2 Vector2::operator*(const float& other) const
{
	return Vector2(x * other, y * other);
}

// This overload returns the division of the vector by the scalar.
Vector2 Vector2::operator/(const float& other) const
{
	return Vector2(x / other, y / other);
}

// This overload copies the vector
void Vector2::operator=(const Vector2& other)
{
	x = other.x;
	y = other.y;
}

// This overload returns true if the vectors are the same
bool Vector2::operator==(const Vector2& rhs) const
{
	return x == rhs.x && y && rhs.y;
}

// This overload returns true if the vectors are different
bool Vector2::operator!=(const Vector2& rhs) const
{
	return x != rhs.x || y != rhs.y;
}

// This function returns true if the lenght of the vector is null
bool Vector2::isNull() const
{
	return lenght() < 0.01f;
}

// This function returns the lenght of the vector
float Vector2::lenght() const
{
	return sqrt(x * x + y * y);
}

// This function normalizes the lenght of the vector
void Vector2::normalize()
{
	if (isNull() == false)
		*this = *this / lenght();
	else
		*this = Vector2();
}

// This function returns the distance between 2 positions
float Distance(Vector2 a, Vector2 b)
{
	Vector2 p = a - b;
	return sqrt(p.x * p.x + p.y * p.y);
}

// This function returns the interpolation between 2 positions
Vector2 Interpolate(Vector2 Start, Vector2 End, float f)
{
	return Vector2(Start.x * (1.0f - f) + End.x * f, Start.y * (1.0f - f) + End.y * f);
}
