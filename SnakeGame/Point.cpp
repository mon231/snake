#include "Point.hpp"

Point::Point(const int32_t x, const int32_t y):
	_x(x),
	_y(y)
{
}

int32_t Point::get_x() const
{
	return _x;
}

int32_t Point::get_y() const
{
	return _y;
}

void Point::set_x(const int32_t x)
{
	_x = x;
}

void Point::set_y(const int32_t y)
{
	_y = y;
}

bool Point::is_within_borders(const uint32_t width, const uint32_t height) const
{
	static constexpr int32_t MINIMUM_UINT32 = 0;
	return
		(_x >= MINIMUM_UINT32) &&
		(static_cast<uint32_t>(_x) < width) &&

		(_y >= MINIMUM_UINT32) &&
		(static_cast<uint32_t>(_y) < height);
}

bool Point::operator==(const Point& other) const
{
	return (_x == other.get_x()) && (_y == other.get_y());
}

bool Point::operator!=(const Point& other) const
{
	return !(*this == other);
}
