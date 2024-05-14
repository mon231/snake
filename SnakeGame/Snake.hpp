#pragma once

#include <deque>
#include <cstdint>

#include "Point.hpp"
#include "Direction.hpp"

class Snake final
{
public:
	Snake(const Point& head_position);
	~Snake() = default;

public:
	Point get_head_position() const;
	Point get_tail_position() const;
	
	uint32_t get_points_count() const;
	std::deque<Point> get_points() const;
	
	bool head_collides_in_body() const;
	bool is_head_within_borders(uint32_t width, uint32_t height) const;

public:
	void eat_apple();
	void perform_step(Direction head_direction);

private:
	Point _removed_tail_position;
	std::deque<Point> _points;
};
