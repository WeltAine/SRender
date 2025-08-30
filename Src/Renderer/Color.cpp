#include "../../Header/Resources/Color.h"
#include "../../Header/Math/MyMath.h"

///值域在[0, 255]之间，默认纯白
Color::Color()
	:r(255), g(255), b(255), a(255)
{
}

///值域在[0, 1]之间，使用前需要自己手动映射到该范围
Color::Color(const int& r, const int& g, const int& b, const int& a = 255)
	:r(Clamp(r, 0, 255)), g(Clamp(g, 0, 255)), b(Clamp(b, 0, 255)), a(Clamp(a, 0, 255))
{
}

Color Color::operator+(const Color& rightColor) const
{
	Color tem(this->r + rightColor.r, this->g + rightColor.g, this->b + rightColor.b, 255);

	return tem;
}

Color Color::operator+(const int& value) const
{
	Color tem(this->r + value, this->g + value, this->b + value, 255);

	return tem;
}

Color Color::operator-(const Color& rightColor) const
{
	Color tem(this->r - rightColor.r, this->g - rightColor.g, this->b - rightColor.b, 255);

	return tem;
}

Color Color::operator-(const int& value) const
{
	Color tem(this->r - value, this->g - value, this->b - value, 255);

	return tem;
}

Color Color::operator*(const Color& rightColor) const
{
	Color tem(this->r * rightColor.r, this->g * rightColor.g, this->b * rightColor.b, 255);

	return tem;
}

Color Color::operator*(const float& value) const
{
	Color tem(this->r * value, this->g * value, this->b * value, 255);

	return tem;
}

Color Color::operator/(const Color& rightColor) const
{
	Color tem(this->r / rightColor.r, this->g / rightColor.g, this->b / rightColor.b, 255);

	return tem;
}

Color Color::operator/(const float& value) const
{
	Color tem(this->r / value, this->g / value, this->b / value, 255);

	return tem;
}


/// <summary>
/// 在c1与c2之间t%位置的值
/// </summary>
/// <param name="c1"></param>
/// <param name="c2"></param>
/// <param name="t"></param>
/// <returns></returns>
Color Color::Lerp(const Color& c1, const Color& c2, const float& t)
{
	return (c1 * (1 - t)) + (c2 * t);
}

bool Color::operator==(const Color& aim) const
{
	return this->r == aim.r && this->g == aim.g && this->b == aim.b;
}

Color Color::white{ 255, 255, 255, 255 };

Color Color::black{ 0, 0, 0, 255 };
