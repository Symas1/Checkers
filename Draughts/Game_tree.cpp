#include "Game_tree.h"

void Game_tree::create_generation_of_moves(bool player1)
{
	for (auto& x : possible_moves)
	{
		x->create_generation_of_moves(!player1);
	}

	if (possible_moves.empty())
	{
		auto moves = board->get_moves(player1);
		for (auto& x : moves)
		{
			possible_moves.push_back(std::make_unique<Game_tree>(std::move(x)));
		}
	}
}

int Game_tree::alpha_beta_prunning(bool player1, int depth, int lower_bound, int upper_bound)
{
	if (depth == 0)
	{
		return board->board_value();
	}
	if (possible_moves.empty())
	{
		this->create_generation_of_moves(player1);
	}

	if (player1)
	{
		int best = INT_MIN;
		for (auto& x : possible_moves)
		{
			best = (std::max)(best, x->alpha_beta_prunning(!player1, depth - 1, lower_bound, upper_bound));
			lower_bound = (std::max)(best, lower_bound);
			if (upper_bound <= lower_bound)break;
		}
		return best;
	}
	else
	{
		int best = INT_MAX;
		for (auto& x : possible_moves)
		{
			best = (std::min)(best, x->alpha_beta_prunning(!player1, depth - 1, lower_bound, upper_bound));
			upper_bound = (std::min)(best, upper_bound);
			if (upper_bound <= lower_bound)break;
		}
		return upper_bound;
	}
}

std::unique_ptr<Game_tree> Game_tree::get_best_move(bool player1)
{
	if (possible_moves.empty())
	{
		this->create_generation_of_moves(player1);
	}

	std::unique_ptr<Game_tree> best_move{ nullptr };

	int max_score = player1 ? INT_MIN : INT_MAX;
	for (auto& x : possible_moves)
	{
		int value = x->alpha_beta_prunning(!player1, this->tree_depth, INT_MIN, INT_MAX);
		if (player1)
		{
			if (best_move == nullptr || value > max_score)
			{
				max_score = value;
				best_move.reset(x.release());
			}
		}
		else if (!player1)
		{
			if (best_move == nullptr || value < max_score)
			{
				max_score = value;
				best_move.reset(x.release());
			}
		}
	}
	return best_move;
}

Draughts & Game_tree::get_board()
{
	return *(this->board);
}

std::vector<std::unique_ptr<Game_tree>>& Game_tree::get_possible_moves()
{
	return this->possible_moves;
}

std::unique_ptr<Game_tree> Game_tree::make_move_helper(bool player1)
{
	do {
		try {
			std::string move{};
			std::getline(std::cin, move);
			auto move_board=this->board->make_move(move, player1);

			for (auto& x : this->get_possible_moves())
			{
				if (x->get_board().get_board() != move_board)continue;
				else
				{
					x->create_generation_of_moves(!player1);
					return std::move(x);
				}
			}
		}
		catch (std::string error)
		{
			std::cout << error << std::endl;
		}
		catch (...)
		{
		}
		std::cout << "Please, make another move" << std::endl;
	} while (true);
}

void Game_tree::set_tree_depth(int new_tree_depth) {
	this->tree_depth = new_tree_depth;
}

void Game::start(int tree_depth)
{
	auto tree = std::make_unique<Game_tree>(std::make_unique<Draughts>());
	tree->set_tree_depth(tree_depth);

	bool player1 = true;
	tree->create_generation_of_moves(player1);

	tree->get_board().draw_board();
	while (true)
	{
		if (tree->get_possible_moves().empty())
		{
			if (player1)std::cout << "White player lost" << std::endl;
			else std::cout << "Black player lost" << std::endl;
			break;
		}
		if (tree->get_board().check_for_row())
		{
			std::cout << "This is a row" << std::endl;
			break;
		}
		if (player1)
		{
			std::cout << "LIGHTS TURN" << std::endl;

			auto new_move = tree->make_move_helper(player1);
			tree=std::move(new_move);
		}
		else
		{
			std::cout << "DARKS TURN" << std::endl;
			tree=std::move(tree->get_best_move(player1));
		}

		tree->get_board().draw_board();
		player1 = !player1;
	}
}

void Game::start_computers(int tree_depth)
{
	auto tree = std::make_unique<Game_tree>(std::make_unique<Draughts>());
	tree->set_tree_depth(tree_depth);

	bool player1 = true;
	tree->create_generation_of_moves(player1);

	while (true)
	{
		if (tree->get_possible_moves().empty())
		{
			if (player1)std::cout << "White player lost" << std::endl;
			else std::cout << "Black player lost" << std::endl;
			break;
		}
		if (tree->get_board().check_for_row())
		{
			std::cout << "This is a row" << std::endl;
			break;
		}
		if (player1)
		{
			std::cout << "LIGHTS TURN" << std::endl;
			tree = std::move(tree->get_best_move(player1));
		}
		else
		{
			std::cout << "DARKS TURN" << std::endl;
			tree = std::move(tree->get_best_move(player1));
		}

		tree->get_board().draw_board();
		player1 = !player1;
	}
}
