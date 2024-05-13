#pragma once

#include "Game.hpp"
#include <functional>

using MoveDirectionGetter = std::function<Direction()>;
using FinalScoreHandler = std::function<void(GameState game_end_reason, uint32_t final_score)>;
using PreFrameHandler = std::function<void(const std::deque<Point>& snake_positions, const Point& apple_position)>;

void play_game(
	const uint32_t board_scale_rate,
	const PreFrameHandler& pre_frame_handler,
	const MoveDirectionGetter& move_direction_generator,
	const FinalScoreHandler& final_score_handler);
