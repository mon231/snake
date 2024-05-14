#pragma once
#include <optional>

#include "AStar.hpp"
#include "GameRunner.hpp"

class AStarBot final : public GameRunner
{
public:
	explicit AStarBot(uint32_t board_scale_rate);
	~AStarBot() = default;

protected:
	void handle_game_over() override;
	void prepare_to_next_frame() override;
	Direction get_move_direction() override;

private:
	AStar::Generator _paths_generator;
	std::optional<std::vector<Direction>> _ongoing_path;
};
