#pragma once
#include "Vector2.h"

/*
	BoundingBox implements a rectangle used for rendering and collisions.
*/
class BoundingBox
{
private:

public:
	int left{ 0 }, right{ 0 }, top{ 0 }, bottom{ 0 };

	BoundingBox() = default;
	BoundingBox(int L, int R, int T, int B);
	BoundingBox(int R, int B);

	int GetWidth() const;
	int GetHeight() const;
	int Size() const;

	BoundingBox operator+(const Vector2& other) const;
	BoundingBox operator-(const Vector2& other) const;
	void operator=(const BoundingBox& other);

	bool IsValid() const;

	bool HoldsPosition(Vector2 position) const;
	Vector2 GetRandomPosition() const;
	Vector2 GetPosition() const;
	Vector2 GetCenter() const;
};

BoundingBox Clip(const BoundingBox& B1, const BoundingBox& B2);