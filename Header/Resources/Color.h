#pragma once

#include "../Math/Vector.h"

class Color {

public:
	int r, g, b, a;

	Color();
	Color(const int& r, const int& g, const int& b, const int& a);

	Color operator + (const Color& rightColor) const;
	Color operator + (const int& value) const;

	Color operator - (const Color& rightColor) const;
	Color operator - (const int& value) const;

	Color operator * (const Color& rightColor) const;
	Color operator * (const float& value) const;

	Color operator / (const Color& rightColor) const;
	Color operator / (const float& value) const;

	static Color Lerp(const Color& c1, const Color& c2, const float& t);

	static Color white, black;

	bool operator == (const Color& aim) const;
};
