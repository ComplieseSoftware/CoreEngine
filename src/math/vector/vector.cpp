#include <cmath>
#include "vector.h"

void Vector2D::setVector(float xV, float yV) {
	Vector2D::x = xV;
	Vector2D::y = yV;
}

Vector2D Vector2D::addVectors(Vector2D a, Vector2D b) {
	Vector2D res{};

	res.setVector(a.x + b.x, a.y + b.y);
	return res;
}

float Vector2D::getVectorLength(Vector2D vec) {
	return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}