#include "Snake.hpp"
#include <stdexcept>

Snake::Snake(const Point& head_position) :
	_head_position(head_position),
	_removed_tail_position(head_position)
{
	_points.push_back(head_position);
}

Point Snake::get_head_position() const
{
	return _head_position;
}

uint32_t Snake::get_points_count() const
{
	return static_cast<uint32_t>(_points.size());
}

bool Snake::head_collides_in_body() const
{
	for (uint32_t i = 0; i < _points.size() - 1; ++i)
	{
		if (_points[i] == _head_position)
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
	_head_position = get_next_head(head_direction);
	_points.push_back(_head_position);

	_removed_tail_position = _points.front();
	_points.pop_front();
}

Point Snake::get_next_head(const Direction head_direction) const
{
	switch (head_direction)
	{
	case Direction::UP:
		return Point{ _head_position.get_x(), _head_position.get_y() + 1 };

	case Direction::DOWN:
		return Point{ _head_position.get_x(), _head_position.get_y() - 1 };

	case Direction::LEFT:
		return Point{ _head_position.get_x() - 1, _head_position.get_y() };

	case Direction::RIGHT:
		return Point{ _head_position.get_x() + 1, _head_position.get_y() };

	default:
		throw std::runtime_error("Snake got invalid head direction");
	}
}

bool Snake::is_head_within_borders(const uint32_t width, const uint32_t height) const
{
	return _head_position.is_within_borders(width, height);
}
