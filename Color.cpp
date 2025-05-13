#include "Color.h"
#include "MyMath.h"

Color::Color()
	:r(1), g(1), b(1), a(1)
{
}

Color::Color(const float& r, const float& g, const float& b, const float& a)
	:r(r), g(g), b(b), a(a)
{
}

Color Color::operator+(const Color& rightColor) const
{
	Color tem(this->r + rightColor.r, this->g + rightColor.g, this->b + rightColor.b, this->a + rightColor.a);

	tem.r = Clamp(tem.r, 0, 1);
	tem.g = Clamp(tem.g, 0, 1);
	tem.b = Clamp(tem.b, 0, 1);
	tem.a = Clamp(tem.a, 0, 1);

	return tem;
}

Color Color::operator+(const float& value) const
{
	Color tem(this->r + value, this->g + value, this->b + value, this->a + value);

	tem.r = Clamp(tem.r, 0, 1);
	tem.g = Clamp(tem.g, 0, 1);
	tem.b = Clamp(tem.b, 0, 1);
	tem.a = Clamp(tem.a, 0, 1);

	return tem;
}

Color Color::operator-(const Color& rightColor) const
{
	Color tem(this->r - rightColor.r, this->g - rightColor.g, this->b - rightColor.b, this->a - rightColor.a);

	tem.r = Clamp(tem.r, 0, 1);
	tem.g = Clamp(tem.g, 0, 1);
	tem.b = Clamp(tem.b, 0, 1);
	tem.a = Clamp(tem.a, 0, 1);

	return tem;
}

Color Color::operator-(const float& value) const
{
	Color tem(this->r - value, this->g - value, this->b - value, this->a - value);

	tem.r = Clamp(tem.r, 0, 1);
	tem.g = Clamp(tem.g, 0, 1);
	tem.b = Clamp(tem.b, 0, 1);
	tem.a = Clamp(tem.a, 0, 1);

	return tem;
}

Color Color::operator*(const Color& rightColor) const
{
	Color tem(this->r * rightColor.r, this->g * rightColor.g, this->b * rightColor.b, this->a * rightColor.a);

	tem.r = Clamp(tem.r, 0, 1);
	tem.g = Clamp(tem.g, 0, 1);
	tem.b = Clamp(tem.b, 0, 1);
	tem.a = Clamp(tem.a, 0, 1);

	return tem;
}

Color Color::operator*(const float& value) const
{
	Color tem(this->r * value, this->g * value, this->b * value, this->a * value);

	tem.r = Clamp(tem.r, 0, 1);
	tem.g = Clamp(tem.g, 0, 1);
	tem.b = Clamp(tem.b, 0, 1);
	tem.a = Clamp(tem.a, 0, 1);

	return tem;
}

Color Color::operator/(const Color& rightColor) const
{
	Color tem(this->r / rightColor.r, this->g / rightColor.g, this->b / rightColor.b, this->a / rightColor.a);

	tem.r = Clamp(tem.r, 0, 1);
	tem.g = Clamp(tem.g, 0, 1);
	tem.b = Clamp(tem.b, 0, 1);
	tem.a = Clamp(tem.a, 0, 1);

	return tem;
}

Color Color::operator/(const float& value) const
{
	Color tem(this->r / value, this->g / value, this->b / value, this->a / value);

	tem.r = Clamp(tem.r, 0, 1);
	tem.g = Clamp(tem.g, 0, 1);
	tem.b = Clamp(tem.b, 0, 1);
	tem.a = Clamp(tem.a, 0, 1);

	return tem;
}

Color Color::Lerp(const Color& c1, const Color& c2, const float& t)
{
	return (c1 * (1 - t)) + (c2 * t);
}

bool Color::operator==(const Color& aim) const
{
	return this->r == aim.r && this->g == aim.g && this->b == aim.b && this->a == aim.a;
}

Color Color::white{ 1, 1, 1, 1 };
