#include "GameRunner.hpp"

#include <iostream>
#include <functional>
#include <type_traits>

Direction cli_get_move_direction()
{
	Direction input = Direction::UNINITIALIZED;
	std::cout << "Enter move direction ("
		"UP: " << static_cast<uint8_t>(Direction::UP) << ", "
		"DOWN: " << static_cast<uint8_t>(Direction::DOWN) << ", "
		"LEFT: " << static_cast<uint8_t>(Direction::LEFT) << ", "
		"RIGHT: " << static_cast<uint8_t>(Direction::RIGHT) << "):";
	std::cin >> reinterpret_cast<std::underlying_type_t<Direction>&>(input);

	if (
		input != Direction::UP &&
		input != Direction::DOWN &&
		input != Direction::LEFT &&
		input != Direction::RIGHT)
	{
		throw std::runtime_error("Invalid input for move direction");
	}
}

void cli_print_frame(const std::deque<Point>& snake_positions, const Point& apple_position)
{
	// TODO: impl
}

void cli_print_score(const GameState game_end_reason, const uint32_t final_score)
{
	// TODO: impl
}

int main()
{
	static constexpr uint32_t GAME_SCREEN_SCALE = 6;
	play_game(GAME_SCREEN_SCALE, cli_print_frame, cli_get_move_direction, cli_print_score);

	return EXIT_SUCCESS;
}
