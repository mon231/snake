#include "GameRunner.hpp"

void play_game(
	const uint32_t board_scale_rate,
	const PreFrameHandler& pre_frame_handler,
	const MoveDirectionGetter& move_direction_generator,
	const FinalScoreHandler& final_score_handler)
{
	Game game = Game::generate_game(board_scale_rate);
	GameState current_game_state = GameState::ONGOING;

	do
	{
		pre_frame_handler(game.get_snake_points(), game.get_apple_position());
		game.set_head_direction(move_direction_generator());

		current_game_state = game.perform_next_screen();
	} while (current_game_state == GameState::ONGOING);

	final_score_handler(current_game_state, game.get_score());
}
