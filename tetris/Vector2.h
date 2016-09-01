#pragma once

// a simple vector2 class for handling x y pairs
template <class t> class Vector2
{
public:
	t x;
	t y;

	Vector2() { };

	Vector2(t _x, t _y)
	{
		set(_x, _y);
	}

	void set(t _x, t _y)
	{
		x = _x;
		y = _y;
	}
};