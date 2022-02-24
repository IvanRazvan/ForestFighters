#include "BoundingBox.h"

// This constructor sets the size of the rectangle.
BoundingBox::BoundingBox(int L, int R, int T, int B)
	: left(L), right(R), top(T), bottom(B)
{

}

// This constructor sets the size of the rectangle placed at the origin.
BoundingBox::BoundingBox(int R, int B)
	: left(0), right(R), top(0), bottom(B)
{
}

// This function returns the width of the rectangle.
int BoundingBox::GetWidth() const
{
	return right - left;
}

// This function returns the height of the rectangle.
int BoundingBox::GetHeight() const
{
	return bottom - top;
}

// This function returns the area of the rectangle.
int BoundingBox::Size() const
{
	return GetWidth() * GetHeight();
}

// This overload returns the rectangle moved using the vector
BoundingBox BoundingBox::operator+(const Vector2& other) const
{
	return BoundingBox(left + round(other.x), right + round(other.x), top + round(other.y), bottom + round(other.y));
}

// This overload returns the rectangle moved using the vector
BoundingBox BoundingBox::operator-(const Vector2& other) const
{
	return BoundingBox(left - round(other.x), right - round(other.x),top - round(other.y), bottom - round(other.y));
}

// This overload copies the rectangle
void BoundingBox::operator=(const BoundingBox& other)
{
	left = other.left;
	right = other.right;
	top = other.top;
	bottom = other.bottom;
}

// This functions returs true if a rectangle is set correctly.
bool BoundingBox::IsValid() const
{
	return left < right && top < bottom;
}

// This functions returs true if the position is inside the rectangle.
bool BoundingBox::HoldsPosition(Vector2 position) const
{
	return position.x >= left && position.x < right && position.y >= top && position.y < bottom;
}

// This functions returs a random position inside the rectangle, with a small margin of 5 units.
Vector2 BoundingBox::GetRandomPosition() const
{
	return Vector2(rand() % (right - left - 5) + left + 5, rand() % (bottom-top - 5) + top + 5);
}

// This functions returs the top left corner of the rectangle.
Vector2 BoundingBox::GetPosition() const
{
	return Vector2(left,top);
}

// This functions returs the center of the rectangle.
Vector2 BoundingBox::GetCenter() const
{
	return Vector2((left + right) / 2, (top + bottom) / 2);
}

// This functions returs the clip between 2 rectangles.
BoundingBox Clip(const BoundingBox& B1, const BoundingBox& B2)
{
	BoundingBox result;
	result.left	= std::max(B1.left, B2.left);
	result.right = std::min(B1.right, B2.right);
	result.bottom = std::min(B1.bottom, B2.bottom);
	result.top = std::max(B1.top, B2.top);
	return result;
}
