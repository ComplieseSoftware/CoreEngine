#pragma once

class Vector2D {
private:
	float x;
	float y;
public:
	void setVector(float x, float y);

	Vector2D addVectors(Vector2D a, Vector2D b);

	float getVectorLength(Vector2D vec);
};