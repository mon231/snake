#pragma once

#include "Game.hpp"
#include <functional>

class GameRunner
{
public:
	explicit GameRunner(uint32_t board_scale_rate);
	~GameRunner() = default;

public:
	void play_game();

protected:
	virtual void handle_game_over() = 0;
	virtual void prepare_to_next_frame() = 0;
	virtual Direction get_move_direction() = 0;

protected:
	Game _game;
};
