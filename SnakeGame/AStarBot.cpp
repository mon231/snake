#include "AStarBot.hpp"
#include "Random.hpp"

AStarBot::AStarBot(const uint32_t board_scale_rate) :
	GameRunner(board_scale_rate),
	_paths_generator(_game.get_width(), _game.get_height())
{
}

void AStarBot::handle_game_over()
{
	// NOTE: no learning to do
}

void AStarBot::prepare_to_next_frame()
{
	if (_ongoing_path.has_value() && _ongoing_path->size() != 0)
	{
		return;
	}

	_paths_generator.clearCollisions();
	for (const Point& snake_point : _game.get_snake_points())
	{
		_paths_generator.addCollision(snake_point);
	}

	const auto path_to_apple =
		_paths_generator.findPathDirections(_game.get_snake_head(), _game.get_apple_position());

	if (path_to_apple.has_value())
	{
		_ongoing_path = path_to_apple.value();
		return;
	}

	const auto path_to_tail =
		_paths_generator.findPathDirections(_game.get_snake_head(), _game.get_snake_tail());

	if (path_to_tail.has_value())
	{
		_ongoing_path = path_to_tail.value();
		return;
	}

	_ongoing_path = std::nullopt;
}

Direction AStarBot::get_move_direction()
{
	if (_ongoing_path.has_value())
	{
		const auto current_direction =_ongoing_path->back();
		_ongoing_path->pop_back();

		return current_direction;
	}

	static constexpr Direction POSSIBLE_DIRECTIONS[] =
		{ Direction::UP, Direction::DOWN, Direction::RIGHT, Direction::LEFT };

	// NOTE: it'd be a bit smarter to return random that does not fail, if possible
	return POSSIBLE_DIRECTIONS[randint(0, _countof(POSSIBLE_DIRECTIONS))];
}
