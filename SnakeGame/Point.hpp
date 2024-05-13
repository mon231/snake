#pragma once
#include <cstdint>

class Point final
{
public:
	explicit Point(int32_t x, int32_t y);
	~Point() = default;

public:
	bool operator==(const Point& other) const;
	bool operator!=(const Point& other) const;

	int32_t get_x() const;
	int32_t get_y() const;

	void set_x(int32_t x);
	void set_y(int32_t y);

	bool is_within_borders(const uint32_t width, const uint32_t height) const;

private:
	int32_t _x;
	int32_t _y;
};
