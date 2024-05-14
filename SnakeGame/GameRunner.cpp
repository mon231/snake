#include "GameRunner.hpp"

GameRunner::GameRunner(const uint32_t board_scale_rate) :
	_game(Game::generate_game(board_scale_rate))
{
}

void GameRunner::play_game()
{
	GameState current_game_state = GameState::ONGOING;

	do
	{
		prepare_to_next_frame();
		_game.set_head_direction(get_move_direction());

		current_game_state = _game.perform_next_screen();
	} while (current_game_state == GameState::ONGOING);

	handle_game_over();
}
