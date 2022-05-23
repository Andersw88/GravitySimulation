#include "Vector.h"
#include "math.h"

Vector::Vector()
{
	x = 0;
	y = 0;
}

Vector::Vector(double x, double y)
{
	this->x = x;
	this->y = y;
}

Vector& Vector::Add(const Vector& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector& Vector::Substract(const Vector& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector& Vector::Multiply(const Vector& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector& Vector::Divide(const Vector& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

// Rotate around origo
Vector& Vector::Rotate(const double& Alpha)
{
	double x0 = x * cos(Alpha) - y * sin(Alpha);
	y = x * sin(Alpha) + y * cos(Alpha);
	x = x0;

	return *this;
}

Vector& Vector::Extend(const double& dLen)
{
	double alpha = atan2( this->y, this->x );
	this->y += sin(alpha) * dLen;
	this->x += cos(alpha) * dLen;

	return *this;
}

Vector operator+(const Vector& vec1, const Vector& vec2)
{
	return { vec1.x + vec2.x, vec1.y + vec2.y };
}

Vector operator-(const Vector& vec1, const Vector& vec2)
{
	return { vec1.x - vec2.x, vec1.y - vec2.y };
}

Vector operator*(const Vector& vec1, const Vector& vec2)
{
	return { vec1.x * vec2.x, vec1.y * vec2.y };
}

Vector operator/(const Vector& vec1, const Vector& vec2)
{
	return { vec1.x / vec2.x, vec1.y / vec2.y };
}

Vector& Vector::operator+=(const Vector vec)
{
	return this->Add(vec);
}

Vector& Vector::operator-=(const Vector vec)
{
	return this->Substract(vec);
}

Vector& Vector::operator*=(const Vector vec)
{
	return this->Multiply(vec);
}

Vector& Vector::operator/=(const Vector vec)
{
	return this->Divide(vec);
}

Vector Vector::operator/(const double& i)
{
	return { this->x / i, this->y / i };
}

Vector Vector::operator*(const double& i)
{
	return { this->x * i, this->y * i };
}

Vector& Vector::Zero()
{
	this->x = 0;
	this->y = 0;

	return *this;
}

double Vector::Lenght()
{
	return sqrt(this->x * this->x + this->y * this->y);
}

std::ostream& operator<<(std::ostream& stream, const Vector vec)
{
	stream << "Vector(" << vec.x << ", " << vec.y << ")";
	return stream;
}