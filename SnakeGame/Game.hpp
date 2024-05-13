#pragma once

#include <cstdint>
#include "Snake.hpp"

enum class GameState
{
	ONGOING,
	WON,
	COLLIDE_IN_SELF,
	COLLIDE_IN_BORDER
};

class Game final
{
public:
	~Game() = default;

private:
	explicit Game(
		const Point& apple_position,
		const Point& snake_position,
		Direction input_direction,
		uint32_t board_width,
		uint32_t board_height
	);

public:
	uint32_t get_width() const;
	uint32_t get_height() const;

public:
	uint32_t get_score() const;
	GameState perform_next_screen();
	void set_head_direction(Direction head_direction);

	Point get_apple_position() const;
	std::deque<Point> get_snake_points() const;

public:
	static Game generate_game(uint32_t board_scale_rate);

private:
	static uint32_t get_board_width(uint32_t board_scale_rate);
	static uint32_t get_board_height(uint32_t board_scale_rate);
	
	static Point generate_apple_position(
		const std::deque<Point>& invalid_positions, 
		uint32_t board_width, 
		uint32_t board_height
	);

private:
	Snake _snake;
	Point _apple_position;
	Direction _input_direction;
	GameState _last_game_state;
	const uint32_t _board_width;
	const uint32_t _board_height;
};
