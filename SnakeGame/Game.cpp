#include "Game.hpp"
#include "Random.hpp"

#include <algorithm>
#include <stdexcept>

Game::Game(
	const Point& apple_position,
	const Point& snake_position,
	const Direction input_direction,
	const uint32_t board_width,
	const uint32_t board_height
):
	_apple_position(apple_position),
	_snake(snake_position),
	_input_direction(input_direction),
	_last_game_state(GameState::ONGOING),
	_board_width(board_width),
	_board_height(board_height)
{}

uint32_t Game::get_width() const
{
	return _board_width;
}

uint32_t Game::get_height() const
{
	return _board_height;
}

Game Game::generate_game(const uint32_t board_scale_rate)
{
	uint32_t board_width = get_board_width(board_scale_rate);
	uint32_t board_height = get_board_width(board_scale_rate);
	
	Point snake_position{ 0, 0 };
	Direction snake_direction = Direction::UNINITIALIZED;

	Point apple_position = generate_apple_position({ snake_position }, board_width, board_height);
	return Game{apple_position, snake_position, snake_direction, board_width, board_height};
}

GameState Game::perform_next_screen()
{
	if (_last_game_state != GameState::ONGOING)
	{
		throw std::runtime_error("Game done already");
	}

	_snake.perform_step(_input_direction);

	if (_snake.get_head_position() == _apple_position)
	{
		_snake.eat_apple();
		_apple_position = generate_apple_position(_snake.get_points(), _board_width, _board_height);
	}

	if (_snake.get_points_count() == _board_width * _board_height)
	{
		_last_game_state = GameState::WON;
	}
	else if (_snake.head_collides_in_body())
	{
		_last_game_state = GameState::COLLIDE_IN_SELF;
	}
	else if (!_snake.is_head_within_borders(_board_width, _board_height))
	{
		_last_game_state = GameState::COLLIDE_IN_BORDER;
	}

	return _last_game_state;
}

void Game::set_head_direction(const Direction head_direction)
{
	_input_direction = head_direction;
}

uint32_t Game::get_board_width(const uint32_t board_scale_rate)
{
	static constexpr uint32_t BOARD_WIDTH_SCALE = 4;
	return board_scale_rate * BOARD_WIDTH_SCALE;
}

uint32_t Game::get_board_height(const uint32_t board_scale_rate)
{
	static constexpr uint32_t BOARD_HEIGHT_SCALE = 3;
	return board_scale_rate * BOARD_HEIGHT_SCALE;
}

Point Game::generate_apple_position(
	const std::deque<Point>& invalid_positions, 
	const uint32_t board_width, 
	const uint32_t board_height
)
{
	Point apple_position{ 0, 0 };

	do
	{
		apple_position.set_x(randint(0, board_width));
		apple_position.set_y(randint(0, board_height));
	} while (std::find(invalid_positions.cbegin(), invalid_positions.cend(), apple_position) != invalid_positions.cend());

	return apple_position;
}

uint32_t Game::get_score() const
{
	return _snake.get_points_count();
}

Point Game::get_snake_head() const
{
	return _snake.get_head_position();
}

Point Game::get_snake_tail() const
{
	return _snake.get_tail_position();
}

Point Game::get_apple_position() const
{
	return _apple_position;
}

std::deque<Point> Game::get_snake_points() const
{
	return _snake.get_points();
}
