#pragma once

#include "Direction.hpp"
#include <cstdint>

class Point final
{
public:
	explicit constexpr Point(const int32_t x, const int32_t y) :
		_x(x),
		_y(y)
	{}

	~Point() = default;

public:
	bool operator==(const Point& other) const;
	bool operator!=(const Point& other) const;

	int32_t get_x() const;
	int32_t get_y() const;

	void set_x(int32_t x);
	void set_y(int32_t y);

	bool is_within_borders(const uint32_t width, const uint32_t height) const;

public:
	static Point get_vector_from_direction(Direction direction);
	static Direction get_direction_from_vector(const Point& vector);

	friend Point operator+(const Point& left, const Point& right)
	{
		return Point{ left.get_x() + right.get_x(), left.get_y() + right.get_y() };
	}

	friend Point operator-(const Point& left, const Point& right)
	{
		return Point{ left.get_x() - right.get_x(), left.get_y() - right.get_y() };
	}

public:
	static constexpr Point get_up_vector() { return Point{ 0, 1 }; }
	static constexpr Point get_down_vector() { return Point{ 0, -1 }; }
	static constexpr Point get_left_vector() { return Point{ -1, 0 }; }
	static constexpr Point get_right_vector() { return Point{ 1, 0 }; }

private:
	int32_t _x;
	int32_t _y;
};
