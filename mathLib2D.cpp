#include <cmath>
#include "mathLib2D.h"

Point2D::Point2D() {
	this->mX = 0.0f;
	this->mY = 0.0f;
}

Point2D::Point2D(float inX, float inY) {
	this->mX = inX;
	this->mY = inY;
}


float Point2D::distanceTo(Point2D other) {
	return sqrt(pow(this->mX - other.mX, 2) + pow(this->mY - other.mY, 2));
}

float Point2D::fastDistanceTo(Point2D other) {
	return pow(this->mX - other.mX, 2) + pow(this->mY - other.mY, 2);
}

Vec2D::Vec2D() {
	this->mX = 1.0f;
	this->mY = 1.0f;
}

Vec2D::Vec2D(float inX, float inY) {
	this->mX = inX;
	this->mY = inY;
}

float Vec2D::length() {
	return sqrt(pow(this->mX, 2) + pow(this->mY, 2));
}

Vec2D Vec2D::normalize() {
	float length = this->length();
	float normX = this->mX / length;
	float normY = this->mY / length;

	return Vec2D(normX, normY);
}

Vec2D Vec2D::multiply(float scaler) {
	return Vec2D(scaler * this->mX, scaler * this->mY);
}

Vec2D Vec2D::add(Vec2D other) {
	return Vec2D(other.mX + this->mX, other.mY + this->mY);
}

Point2D Vec2D::movePoint(Point2D source, float scale) {
	return Point2D(source.mX + (this->mX * scale), source.mY + (this->mY * scale));
}

Vec2D Vec2D::createVector(Point2D p1, Point2D p2) {
	return Vec2D(p2.mX - p1.mX, p2.mY - p1.mY);
}