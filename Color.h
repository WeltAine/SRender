#pragma once

#include "Vector.h"

class Color {

public:
	float r, g, b, a;

	Color();
	Color(const float& r, const float& g, const float& b, const float& a);

	Color operator + (const Color& rightColor) const;
	Color operator + (const float& value) const;

	Color operator - (const Color& rightColor) const;
	Color operator - (const float& value) const;

	Color operator * (const Color& rightColor) const;
	Color operator * (const float& value) const;

	Color operator / (const Color& rightColor) const;
	Color operator / (const float& value) const;

	static Color Lerp(const Color& c1, const Color& c2, const float& t);

	static Color white;

	bool operator == (const Color& aim) const;
};
