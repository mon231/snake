#include "Point.hpp"
#include <stdexcept>

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

Point Point::get_vector_from_direction(Direction direction)
{
	switch (direction)
	{
	case Direction::UP:
		return get_up_vector();

	case Direction::DOWN:
		return get_down_vector();

	case Direction::LEFT:
		return get_left_vector();

	case Direction::RIGHT:
		return get_right_vector();

	default:
		throw std::runtime_error("Invalid direction with no vector");
	}
}

Direction Point::get_direction_from_vector(const Point& vector)
{
	if (vector == get_up_vector())
	{
		return Direction::UP;
	}
	else if (vector == get_down_vector())
	{
		return Direction::DOWN;
	}
	else if (vector == get_left_vector())
	{
		return Direction::LEFT;
	}
	else if (vector == get_right_vector())
	{
		return Direction::RIGHT;
	}

	throw std::runtime_error("Invalid vector with no direction");
}
