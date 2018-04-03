#ifndef GAME_TREE_H_
#define GAME_TREE_H_

#include <memory>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>

#include "Draughts.h"

class Game_tree
{
public:
	Game_tree(std::unique_ptr<Draughts>&&board) { this->board = std::move(board); };

	/*
	moves through the tree until it reaches the end, where it creates an additional generation
	*/
	void create_generation_of_moves(bool player1);

	int alpha_beta_prunning(bool player1, int depth, int lower_bound, int upper_bound);

	std::unique_ptr<Game_tree> get_best_move(bool player1);

	Draughts& get_board();

	std::vector<std::unique_ptr<Game_tree>>& get_possible_moves();

	std::unique_ptr<Game_tree> make_move_helper(bool player1);

	void set_tree_depth(int new_tree_depth);
private:
	std::vector<std::unique_ptr<Game_tree>>possible_moves{};
	std::unique_ptr<Draughts> board;
	int tree_depth = 3; // max possible - 8
}; // Game_tree

namespace Game 
{
	void start(int tree_depth);
	void start_computers(int tree_depth);
} // Game

#endif // GAME_TREE_H_