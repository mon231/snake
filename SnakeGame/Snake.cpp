#include "Snake.hpp"
#include <stdexcept>

Snake::Snake(const Point& head_position) :
	_removed_tail_position(head_position)
{
	_points.push_back(head_position);
}

Point Snake::get_head_position() const
{
	return _points.back();
}

Point Snake::get_tail_position() const
{
	return _points.front();
}

uint32_t Snake::get_points_count() const
{
	return static_cast<uint32_t>(_points.size());
}

bool Snake::head_collides_in_body() const
{
	for (uint32_t i = 0; i < _points.size() - 1; ++i)
	{
		if (_points[i] == get_head_position())
		{
			return true;
		}
	}

	return false;
}

std::deque<Point> Snake::get_points() const
{
	return _points;
}

void Snake::eat_apple()
{
	_points.push_front(_removed_tail_position);
}

void Snake::perform_step(const Direction head_direction)
{
	Point new_head_position = get_head_position() + Point::get_vector_from_direction(head_direction);
	_points.push_back(new_head_position);

	_removed_tail_position = get_tail_position();
	_points.pop_front();
}

bool Snake::is_head_within_borders(const uint32_t width, const uint32_t height) const
{
	return get_head_position().is_within_borders(width, height);
}
