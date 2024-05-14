#include <iostream>
#include "AStarBot.hpp"

int main()
{
	static constexpr uint32_t GAME_SCREEN_SCALE = 6;
	AStarBot a_start_bot{ GAME_SCREEN_SCALE };

	a_start_bot.play_game();
	return EXIT_SUCCESS;
}
