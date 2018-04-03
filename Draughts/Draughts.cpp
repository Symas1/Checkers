#include "Draughts.h"

Draughts::Draughts(Draughts& old_board, const Position & position, Move_type move_type, int number_of_squares)
{
	this->board = old_board.get_board();
	Pieces moved_piece = this->board[position.rows][position.cols];
	this->board[position.rows][position.cols] = Pieces::empty;
	Position new_position{ position };

	switch (move_type)
	{
	case(Move_type::step_right_up):  //step right up
	{
		for (int i = 0; i < number_of_squares; ++i)
		{
			--new_position.rows;
			++new_position.cols;
		}
		break;
	}
	case(Move_type::step_right_down):  //step right down
	{
		for (int i = 0; i < number_of_squares; ++i)
		{
			++new_position.rows;
			++new_position.cols;
		}
		break;
	}
	case(Move_type::jump_right_up): //jump right up
	{
		for (int i = 0; i < number_of_squares; ++i)
		{
			--new_position.rows;
			++new_position.cols;
			if (board[new_position.rows][new_position.cols] != Pieces::empty)
			{
				board[new_position.rows][new_position.cols] = Pieces::empty;
			}
		}
		break;
	}
	case(Move_type::jump_right_down): //jump right down
	{
		for (int i = 0; i < number_of_squares; ++i)
		{
			++new_position.rows;
			++new_position.cols;
			if (board[new_position.rows][new_position.cols] != Pieces::empty)
			{
				board[new_position.rows][new_position.cols] = Pieces::empty;
			}
		}
		break;
	}
	case(Move_type::step_left_up):  //step left up
	{
		for (int i = 0; i < number_of_squares; ++i)
		{
			--new_position.rows;
			--new_position.cols;
		}
		break;
	}
	case(Move_type::step_left_down): //step left down
	{
		for (int i = 0; i < number_of_squares; ++i)
		{
			++new_position.rows;
			--new_position.cols;
		}
		break;
	}
	case(Move_type::jump_left_up): //jump left up
	{
		for (int i = 0; i < number_of_squares; ++i)
		{
			--new_position.rows;
			--new_position.cols;
			if (board[new_position.rows][new_position.cols] != Pieces::empty)
			{
				board[new_position.rows][new_position.cols] = Pieces::empty;
			}
		}
		break;
	}
	case(Move_type::jump_left_down): //jump left down
	{
		for (int i = 0; i < number_of_squares; ++i)
		{
			++new_position.rows;
			--new_position.cols;
			if (board[new_position.rows][new_position.cols] != Pieces::empty)
			{
				board[new_position.rows][new_position.cols] = Pieces::empty;
			}
		}
		break;
	}
	default:
	{
		break;
	}
	}

	if (should_make_king(new_position, moved_piece))
	{
		moved_piece = make_king(moved_piece);
	}
	board[new_position.rows][new_position.cols] = moved_piece;

}

Pieces Draughts::make_king(Pieces moved_piece)
{
	if (moved_piece == Pieces::light_piece)  //king it
	{
		return Pieces::light_piece_promoted;
	}
	else if (moved_piece == Pieces::dark_piece)   //king it
	{
		return Pieces::dark_piece_promoted;
	}
}

bool Draughts::should_make_king(const Position& new_position, Pieces moved_piece)
{
	if (new_position.rows == 0 && moved_piece == Pieces::light_piece)  //king it
	{
		return true;
	}
	else if (new_position.rows == 7 && moved_piece == Pieces::dark_piece)   //king it
	{
		return true;
	}
	return false;
}

Draughts::Draughts(std::string&& file_name)
{
	std::ifstream file(file_name);
	if (file.is_open())
	{
		std::string line{};
		int counter = 0;
		while (std::getline(file, line))
		{
			board.push_back(std::vector<Pieces>{});
			for (auto& x : line)
			{
				if (x == '0')board[counter].push_back(Pieces::empty);
				else if (x == '1')board[counter].push_back(Pieces::dark_piece);
				else if (x == '2')board[counter].push_back(Pieces::light_piece);
				else if (x == '3')board[counter].push_back(Pieces::dark_piece_promoted);
				else if (x == '4')board[counter].push_back(Pieces::light_piece_promoted);
			}
			++counter;
		}
	}
	file.close();
}

void Draughts::generate_new_board()
{
	for (int i = 0; i < 8; ++i)
	{
		board.push_back(std::vector<Pieces>{});
		for (int j = 0; j < 8; ++j)
		{
			if (i < 3)
			{
				if ((i + j) % 2 == 0)
				{
					board[i].push_back(Pieces::empty);
				}
				else
				{
					board[i].push_back(Pieces::dark_piece);
				}
			}
			else if (i >= 3 && i < 5)
			{
				board[i].push_back(Pieces::empty);
			}
			else if (i >= 5)
			{
				if ((i + j) % 2 == 0)
				{
					board[i].push_back(Pieces::empty);
				}
				else
				{
					board[i].push_back(Pieces::light_piece);
				}
			}
		}
	}
}

std::vector<std::vector<Pieces>>& Draughts::get_board()
{
	return this->board;
}

void Draughts::draw_board()
{
	std::cout << std::setw(cell_width);
	std::cout << " ";
	std::cout << std::setw(cell_width) << " A" << std::setw(cell_width) << " B" << std::setw(cell_width) << " C" << std::setw(cell_width) << " D" << std::setw(cell_width) << " E" << std::setw(cell_width) << " F" << std::setw(cell_width) << " G" << std::setw(cell_width) << " H" << std::endl;
	for (int i = 0; i < board.size(); ++i)
	{
		rlutil::saveDefaultColor();
		std::cout << std::setw(cell_width);
		std::cout << 8 - i << " ";
		for (int j = ((i % 2) == 1) ? 0 : 1; j < board[0].size(); j += 2)
		{

			if (j % 2 != 0)
			{
				std::cout << std::setw(cell_width);
				rlutil::setBackgroundColor(rlutil::WHITE);
				std::cout << " ";
			}

			std::cout << std::setw(cell_width);
			if (board[i][j] == Pieces::dark_piece)
			{
				rlutil::setBackgroundColor(rlutil::BLUE);
				rlutil::setColor(rlutil::LIGHTCYAN);
				std::cout << "o ";
			}
			else if (board[i][j] == Pieces::light_piece)
			{
				rlutil::setBackgroundColor(rlutil::BLUE);
				rlutil::setColor(rlutil::WHITE);
				std::cout << "o ";
			}
			else if (board[i][j] == Pieces::dark_piece_promoted)
			{
				rlutil::setBackgroundColor(rlutil::BLUE);
				rlutil::setColor(rlutil::LIGHTCYAN);
				std::cout << "* ";
			}
			else if (board[i][j] == Pieces::light_piece_promoted)
			{
				rlutil::setBackgroundColor(rlutil::BLUE);
				rlutil::setColor(rlutil::WHITE);
				std::cout << "* ";
			}
			else if (board[i][j] == Pieces::empty)
			{
				rlutil::setBackgroundColor(rlutil::BLUE);
				std::cout << " ";
			}

			if (j % 2 == 0)
			{
				std::cout << std::setw(cell_width);
				rlutil::setBackgroundColor(rlutil::WHITE);
				std::cout << " ";
			}
		}
		rlutil::resetColor();
		std::cout << std::setw(cell_width - 1);
		std::cout << 8 - i;
		std::cout << std::endl;
	}
	std::cout << std::setw(cell_width);
	std::cout << " ";
	std::cout << std::setw(cell_width) << " A" << std::setw(cell_width) << " B" << std::setw(cell_width) << " C" << std::setw(cell_width) << " D" << std::setw(cell_width) << " E" << std::setw(cell_width) << " F" << std::setw(cell_width) << " G" << std::setw(cell_width) << " H" << std::endl;
	rlutil::resetColor();
}

std::vector<std::unique_ptr<Draughts>> Draughts::get_moves(bool player1)
{
	std::vector<std::unique_ptr<Draughts>>moves{};
	std::vector<std::thread>outer_thread{};

	for (int i = 0; i < board.size(); ++i) // get jump moves first
	{
		if (outer_thread.size() >= outer_threads)
		{
			for (auto& x : outer_thread)
			{
				x.join();
			}
			outer_thread.clear();
		}
		outer_thread.push_back(std::thread(&Draughts::outer_thread_jump_func, this, std::ref(moves), i, player1));
	}
	for (auto& x : outer_thread)
	{
		x.join();
	}
	outer_thread.clear();

	if (moves.empty()) // if there are no jump moves, then look for step moves
	{
		for (int i = 0; i < board.size(); ++i)
		{
			if (outer_thread.size() >= outer_threads)
			{
				for (auto& x : outer_thread)
				{
					x.join();
				}
				outer_thread.clear();
			}
			outer_thread.push_back(std::thread(&Draughts::outer_thread_step_func, this, std::ref(moves), i, player1));
		}
		for (auto& x : outer_thread)
		{
			x.join();
		}
		outer_thread.clear();
	}

	return moves;
}

std::vector<std::unique_ptr<Draughts>> Draughts::get_jump_moves(const Position & position)
{
	std::vector<std::unique_ptr<Draughts>>jump_moves{};

	Pieces piece_type = board[position.rows][position.cols];

	if (piece_type == Pieces::dark_piece || piece_type == Pieces::light_piece)//jumps for usual pieces
	{
		if (jump_ok(position, Position{ position.rows - 1,position.cols + 1 }, Position{ position.rows - 2,position.cols + 2 }))//jump right up
		{
			auto new_board = std::make_unique<Draughts>(*this, position, Move_type::jump_right_up, 2);
			std::vector<std::unique_ptr<Draughts>>next_jumps = new_board->get_jump_moves(Position{ position.rows - 2,position.cols + 2 });//continue looking for jumps from new position
			if (next_jumps.empty())
			{
				jump_moves.push_back(std::move(new_board));
			}
			else jump_moves.insert(jump_moves.end(), std::make_move_iterator(next_jumps.begin()), std::make_move_iterator(next_jumps.end()));
		}
		if (jump_ok(position, Position{ position.rows + 1,position.cols + 1 }, Position{ position.rows + 2,position.cols + 2 }))//jump right down
		{
			auto new_board = std::make_unique<Draughts>(*this, position, Move_type::jump_right_down, 2);
			std::vector<std::unique_ptr<Draughts>>next_jumps = new_board->get_jump_moves(Position{ position.rows + 2,position.cols + 2 });
			if (next_jumps.empty())
			{
				jump_moves.push_back(std::move(new_board));
			}
			else jump_moves.insert(jump_moves.end(), std::make_move_iterator(next_jumps.begin()), std::make_move_iterator(next_jumps.end()));
		}
		if (jump_ok(position, Position{ position.rows - 1,position.cols - 1 }, Position{ position.rows - 2,position.cols - 2 }))//jump left up
		{
			auto new_board = std::make_unique<Draughts>(*this, position, Move_type::jump_left_up, 2);
			std::vector<std::unique_ptr<Draughts>>next_jumps = new_board->get_jump_moves(Position{ position.rows - 2,position.cols - 2 });
			if (next_jumps.empty())
			{
				jump_moves.push_back(std::move(new_board));
			}
			else jump_moves.insert(jump_moves.end(), std::make_move_iterator(next_jumps.begin()), std::make_move_iterator(next_jumps.end()));
		}
		if (jump_ok(position, Position{ position.rows + 1,position.cols - 1 }, Position{ position.rows + 2,position.cols - 2 }))//jump left down
		{
			auto new_board = std::make_unique<Draughts>(*this, position, Move_type::jump_left_down, 2);
			std::vector<std::unique_ptr<Draughts>>next_jumps = new_board->get_jump_moves(Position{ position.rows + 2,position.cols - 2 });
			if (next_jumps.empty())
			{
				jump_moves.push_back(std::move(new_board));
			}
			else jump_moves.insert(jump_moves.end(), std::make_move_iterator(next_jumps.begin()), std::make_move_iterator(next_jumps.end()));
		}
	}

	if (piece_type == Pieces::dark_piece_promoted || piece_type == Pieces::light_piece_promoted)//jumps for promoted pieces
	{
		auto enemy = find_enemy_on_the_diagonal(position, Move_type::jump_right_up);//jump right up
		if (enemy)
		{
			for (int i = enemy->rows - 1, j = enemy->cols + 1; i >= 0 && j <= 7; --i, ++j)
			{
				if (jump_ok(position, *enemy, Position{ i,j }))
				{
					auto new_board = std::make_unique<Draughts>(*this, position, Move_type::jump_right_up, position.rows - i);
					std::vector<std::unique_ptr<Draughts>>next_jumps = new_board->get_jump_moves(Position{ i,j });
					if (next_jumps.empty())
					{
						jump_moves.push_back(std::move(new_board));
					}
					else jump_moves.insert(jump_moves.end(), std::make_move_iterator(next_jumps.begin()), std::make_move_iterator(next_jumps.end()));
				}
			}
		}
		enemy.reset(find_enemy_on_the_diagonal(position, Move_type::jump_right_down).release());//jump right down
		if (enemy)
		{
			for (int i = enemy->rows + 1, j = enemy->cols + 1; i <= 7 && j <= 7; ++i, ++j)
			{
				if (jump_ok(position, *enemy, Position{ i,j }))
				{
					auto new_board = std::make_unique<Draughts>(*this, position, Move_type::jump_right_down, i - position.rows);
					std::vector<std::unique_ptr<Draughts>>next_jumps = new_board->get_jump_moves(Position{ i,j });
					if (next_jumps.empty())
					{
						jump_moves.push_back(std::move(new_board));
					}
					else jump_moves.insert(jump_moves.end(), std::make_move_iterator(next_jumps.begin()), std::make_move_iterator(next_jumps.end()));
				}
			}
		}
		enemy.reset(find_enemy_on_the_diagonal(position, Move_type::jump_left_up).release());//jump left up
		{
			if (enemy)
			{
				for (int i = enemy->rows - 1, j = enemy->cols - 1; i >= 0 && j >= 0; --i, --j)
				{
					if (jump_ok(position, *enemy, Position{ i,j }))
					{
						auto new_board = std::make_unique<Draughts>(*this, position, Move_type::jump_left_up, position.rows - i);
						std::vector<std::unique_ptr<Draughts>>next_jumps = new_board->get_jump_moves(Position{ i,j });
						if (next_jumps.empty())
						{
							jump_moves.push_back(std::move(new_board));
						}
						else jump_moves.insert(jump_moves.end(), std::make_move_iterator(next_jumps.begin()), std::make_move_iterator(next_jumps.end()));
					}
				}
			}
		}
		enemy.reset(find_enemy_on_the_diagonal(position, Move_type::jump_left_down).release());//jump left down
		{
			if (enemy)
			{
				for (int i = enemy->rows + 1, j = enemy->cols - 1; i <= 7 && j >= 0; ++i, --j)
				{
					if (jump_ok(position, *enemy, Position{ i,j }))
					{
						auto new_board = std::make_unique<Draughts>(*this, position, Move_type::jump_left_down, i - position.rows);
						std::vector<std::unique_ptr<Draughts>>next_jumps = new_board->get_jump_moves(Position{ i,j });
						if (next_jumps.empty())
						{
							jump_moves.push_back(std::move(new_board));
						}
						else jump_moves.insert(jump_moves.end(), std::make_move_iterator(next_jumps.begin()), std::make_move_iterator(next_jumps.end()));
					}
				}
			}
		}
	}

	return jump_moves;
}

std::vector<std::unique_ptr<Draughts>> Draughts::get_step_moves(const Position & position)
{
	std::vector<std::unique_ptr<Draughts>>step_moves{};

	Pieces piece_type = board[position.rows][position.cols];

	if (piece_type == Pieces::dark_piece || piece_type == Pieces::light_piece)//steps for usual pieces
	{
		if (piece_type == Pieces::dark_piece) // usual dark pieces step only left down and right down
		{
			if (step_ok(position, Position{ position.rows + 1,position.cols + 1 })) // right down
			{
				step_moves.push_back(std::make_unique<Draughts>(*this, position, Move_type::step_right_down, 1));
			}
			if (step_ok(position, Position{ position.rows + 1,position.cols - 1 })) // left down
			{
				step_moves.push_back(std::make_unique<Draughts>(*this, position, Move_type::step_left_down, 1));
			}
		}
		else if (piece_type == Pieces::light_piece) // usual light pieces step only left up and right up
		{
			if (step_ok(position, Position{ position.rows - 1,position.cols + 1 })) // right up
			{
				step_moves.push_back(std::make_unique<Draughts>(*this, position, Move_type::step_right_up, 1));
			}
			if (step_ok(position, Position{ position.rows - 1,position.cols - 1 })) // left up
			{
				step_moves.push_back(std::make_unique<Draughts>(*this, position, Move_type::step_left_up, 1));
			}
		}
	}

	if (piece_type == Pieces::dark_piece_promoted || piece_type == Pieces::light_piece_promoted) // steps for promoted pieces
	{
		for (int i = position.rows - 1, j = position.cols + 1; i >= 0 && j <= 7; --i, ++j) // steps right up
		{
			if (step_ok(position, Position{ i,j }))
			{
				step_moves.push_back(std::make_unique<Draughts>(*this, position, Move_type::step_right_up, position.rows - i));
			}
			else break;
		}

		for (int i = position.rows + 1, j = position.cols + 1; i <= 7 && j <= 7; ++i, ++j) // steps right down
		{
			if (step_ok(position, Position{ i,j }))
			{
				step_moves.push_back(std::make_unique<Draughts>(*this, position, Move_type::step_right_down, i - position.rows));
			}
			else break;
		}

		for (int i = position.rows - 1, j = position.cols - 1; i >= 0 && j >= 0; --i, --j) // steps left up
		{
			if (step_ok(position, Position{ i,j }))
			{
				step_moves.push_back(std::make_unique<Draughts>(*this, position, Move_type::step_left_up, position.rows - i));
			}
			else break;
		}

		for (int i = position.rows + 1, j = position.cols - 1; i <= 7 && j >= 0; ++i, --j) // steps left down
		{
			if (step_ok(position, Position{ i,j }))
			{
				step_moves.push_back(std::make_unique<Draughts>(*this, position, Move_type::step_left_down, i - position.rows));
			}
			else break;
		}
	}

	return step_moves;
}

bool Draughts::jump_ok(const Position & jump_from, const Position & jump_over, const Position& jump_to)
{
	return  is_open(jump_to) && diagonal_between_pieces_is_empty(jump_from, jump_over) && is_enemy(jump_from, jump_over)
		&& diagonal_between_pieces_is_empty(jump_over, jump_to);
}

bool Draughts::step_ok(const Position& step_from, const Position& step_to)
{
	return is_open(step_to) && diagonal_between_pieces_is_empty(step_from, step_to);
}

std::unique_ptr<Position> Draughts::find_enemy_on_the_diagonal(const Position& start_piece, Move_type move_type)
{
	if (move_type == Move_type::jump_right_up)
	{
		for (int i = start_piece.rows - 1, j = start_piece.cols + 1; i >= 0 && j <= 7; --i, ++j)
		{
			if (board[i][j] == Pieces::empty)continue;
			else if (!is_enemy(start_piece, Position{ i,j }))
			{
				return nullptr;
			}
			else return std::make_unique<Position>(i, j);
		}
	}
	else if (move_type == Move_type::jump_right_down)
	{
		for (int i = start_piece.rows + 1, j = start_piece.cols + 1; i <= 7 && j <= 7; ++i, ++j)
		{
			if (board[i][j] == Pieces::empty)continue;
			else if (!is_enemy(start_piece, Position{ i,j }))
			{
				return nullptr;
			}
			else return std::make_unique<Position>(i, j);
		}
	}
	else if (move_type == Move_type::jump_left_up)
	{
		for (int i = start_piece.rows - 1, j = start_piece.cols - 1; i >= 0 && j >= 0; --i, --j)
		{
			if (board[i][j] == Pieces::empty)continue;
			else if (!is_enemy(start_piece, Position{ i,j }))
			{
				return nullptr;
			}
			else return std::make_unique<Position>(i, j);
		}
	}
	else if (move_type == Move_type::jump_left_down)
	{
		for (int i = start_piece.rows + 1, j = start_piece.cols - 1; i <= 7 && j >= 0; ++i, --j)
		{
			if (board[i][j] == Pieces::empty)continue;
			else if (!is_enemy(start_piece, Position{ i,j }))
			{
				return nullptr;
			}
			else return std::make_unique<Position>(i, j);
		}
	}
	return nullptr;
}

int Draughts::board_value()
{
	int value{ 0 };
	for (int i = 0; i < board.size(); ++i) // loop throught the whole board
	{
		for (int j = ((i % 2) == 1) ? 0 : 1; j < board[0].size(); j += 2)
		{
			if (board[i][j] == Pieces::light_piece)value += 1;
			if (board[i][j] == Pieces::light_piece_promoted)value += 2;
			if (board[i][j] == Pieces::dark_piece)value -= 1;
			if (board[i][j] == Pieces::dark_piece_promoted)value -= 2;
		}
	}
	return value;
}

void Draughts::outer_thread_jump_func(std::vector<std::unique_ptr<Draughts>>&moves, int i, bool player1)
{
	for (int j = ((i % 2) == 1) ? 0 : 1; j < board[0].size(); j += 2)
	{
		if (
			(player1 && (board[i][j] == Pieces::light_piece || board[i][j] == Pieces::light_piece_promoted))
			||
			(!player1 && (board[i][j] == Pieces::dark_piece || board[i][j] == Pieces::dark_piece_promoted))
			)
		{
			auto new_moves = get_jump_moves(Position{ i,j });
			m.lock();
			moves.insert(moves.end(), std::make_move_iterator(new_moves.begin()), std::make_move_iterator(new_moves.end()));
			m.unlock();
		}
	}
}

void Draughts::outer_thread_step_func(std::vector<std::unique_ptr<Draughts>>& moves, int i, bool player1)
{
	for (int j = ((i % 2) == 1) ? 0 : 1; j < board[0].size(); j += 2)
	{
		if (
			(player1 && (board[i][j] == Pieces::light_piece || board[i][j] == Pieces::light_piece_promoted))
			||
			(!player1 && (board[i][j] == Pieces::dark_piece || board[i][j] == Pieces::dark_piece_promoted))
			)
		{
			auto new_moves = get_step_moves(Position{ i,j });
			m.lock();
			moves.insert(moves.end(), std::make_move_iterator(new_moves.begin()), std::make_move_iterator(new_moves.end()));
			m.unlock();
		}
	}
}

bool Draughts::diagonal_between_pieces_is_empty(const Position& start_piece, const Position& end_piece)
{
	if (end_piece.cols > start_piece.cols)//end_piece is to the right of the start_piece
	{
		if (end_piece.rows < start_piece.rows)//end_piece is above the start_piece
		{
			Position current_position{ start_piece.rows - 1,start_piece.cols + 1 };
			while ((current_position.rows != end_piece.rows) && (current_position.cols != end_piece.cols))
			{
				if (board[current_position.rows][current_position.cols] != Pieces::empty)
				{
					return false;
				}
				--current_position.rows;
				++current_position.cols;
			}
			return true;
		}
		if (end_piece.rows > start_piece.rows)//end_piece is under the start_piece
		{
			Position current_position{ start_piece.rows + 1,start_piece.cols + 1 };
			while ((current_position.rows != end_piece.rows) && (current_position.cols != end_piece.cols))
			{
				if (board[current_position.rows][current_position.cols] != Pieces::empty)
				{
					return false;
				}
				++current_position.rows;
				++current_position.cols;
			}
			return true;
		}
	}
	else if (end_piece.cols < start_piece.cols)//end_piece is to the left of the start_piece
	{
		if (end_piece.rows < start_piece.rows)//end_piece is above the start_piece
		{
			Position current_position{ start_piece.rows - 1,start_piece.cols - 1 };
			while ((current_position.rows != end_piece.rows) && (current_position.cols != end_piece.cols))
			{
				if (board[current_position.rows][current_position.cols] != Pieces::empty)
				{
					return false;
				}
				--current_position.rows;
				--current_position.cols;
			}
			return true;
		}
		if (end_piece.rows > start_piece.rows)//end_piece is under the start_piece
		{
			Position current_position{ start_piece.rows + 1,start_piece.cols - 1 };
			while ((current_position.rows != end_piece.rows) && (current_position.cols != end_piece.cols))
			{
				if (board[current_position.rows][current_position.cols] != Pieces::empty)
				{
					return false;
				}
				++current_position.rows;
				--current_position.cols;
			}
			return true;
		}
	}
	return false;
}

bool Draughts::is_enemy(const Position& first_piece, const Position& second_piece)
{
	return 		(
		(
		(board[second_piece.rows][second_piece.cols] == Pieces::dark_piece || board[second_piece.rows][second_piece.cols] ==
			Pieces::dark_piece_promoted) &&
			(board[first_piece.rows][first_piece.cols] == Pieces::light_piece || board[first_piece.rows][first_piece.cols] == Pieces::light_piece_promoted)
			) ||
			(
		(board[second_piece.rows][second_piece.cols] == Pieces::light_piece || board[second_piece.rows][second_piece.cols] ==
			Pieces::light_piece_promoted) &&
			(board[first_piece.rows][first_piece.cols] == Pieces::dark_piece || board[first_piece.rows][first_piece.cols] == Pieces::dark_piece_promoted)
				)
		);
}

bool Draughts::is_open(const Position & position)
{
	return in_bounds(position) && board[position.rows][position.cols] == Pieces::empty;
}

bool Draughts::in_bounds(const Position & position)
{
	return (position.rows >= 0 && position.rows < board.size() &&
		position.cols >= 0 && position.cols < board[0].size());
}

bool Draughts::game_over(bool player1)
{
	return get_moves(player1).empty();
}

bool Draughts::check_for_row()
{
	int light = 0;
	int dark = 0;
	int light_promoted = 0;
	int dark_promoted = 0;
	for (int i = 0; i < board.size(); ++i)
	{
		for (int j = ((i % 2) == 1) ? 0 : 1; j < board[0].size(); j += 2)
		{
			if (board[i][j] == Pieces::light_piece)light++;
			else if (board[i][j] == Pieces::dark_piece)dark++;
			else if (board[i][j] == Pieces::light_piece_promoted)light_promoted++;
			else if (board[i][j] == Pieces::dark_piece_promoted)dark_promoted++;
		}
	}
	if (light_promoted == 1 && dark_promoted == 1 && light == 0 && dark == 0)return true;
	return false;
}

std::vector<std::vector<Pieces>> Draughts::make_move(std::string move, bool player1)
{
	auto copy_board = this->board;

	int start_x{};
	try {
		start_x = letter_to_int(move[0]);
	}
	catch (std::string error)
	{
		throw;
	}

	int start_y = 8-std::stoi(std::string{ move[1] });

	try {
		check_entered_number_of_row(start_y);
	}
	catch (std::string error)
	{
		throw;
	}

	move = move.substr(3);

	Pieces moving_piece = copy_board[start_y][start_x];


	std::vector<std::string>moves{};
	if (player1 &&
		(moving_piece == Pieces::light_piece || moving_piece == Pieces::light_piece_promoted) ||
		!player1 &&
		(moving_piece == Pieces::dark_piece || moving_piece == Pieces::dark_piece_promoted))
	{
		for (int i = move.length() - 1; i >= 0; i = i - 3)
		{
			std::string new_move = std::string{ move[i - 1] } +std::string{ move[i] };
			moves.insert(moves.begin(), new_move);
		}

		for (auto& x : moves)
		{
			int new_pos_x{};
			try {
				new_pos_x = letter_to_int(x[0]);
			}
			catch (std::string error)
			{
				throw;
			}
			int new_pos_y = 8-std::stoi(std::string{ x[1] });

			try {
				check_entered_number_of_row(new_pos_y);
			}
			catch (std::string error)
			{
				throw;
			}

			if (new_pos_x > start_x) // right
			{
				if (new_pos_y < start_y) // up
				{
					for (int i = start_y, j = start_x; i >= new_pos_y && j <= new_pos_x; --i, ++j)
					{
						copy_board[i][j] = Pieces::empty;
					}
					if (should_make_king(Position{new_pos_y,new_pos_x}, moving_piece))
					{
						moving_piece = make_king(moving_piece);
					}
					copy_board[new_pos_y][new_pos_x] = moving_piece;
					start_x = new_pos_x;
					start_y = new_pos_y;
				}
				else if (new_pos_y > start_y) // down
				{
					for (int i = start_y, j = start_x; i <= new_pos_y && j <= new_pos_x; ++i, ++j)
					{
						copy_board[i][j] = Pieces::empty;
					}
					if (should_make_king(Position{ new_pos_y,new_pos_x }, moving_piece))
					{
						moving_piece = make_king(moving_piece);
					}
					copy_board[new_pos_y][new_pos_x] = moving_piece;
					start_x = new_pos_x;
					start_y = new_pos_y;
				}
			}
			else if (new_pos_x < start_x) // left
			{
				if (new_pos_y < start_y) // up
				{
					for (int i = start_y, j = start_x; i >= new_pos_y && j >= new_pos_x; --i, --j)
					{
						copy_board[i][j] = Pieces::empty;
					}
					if (should_make_king(Position{ new_pos_y,new_pos_x }, moving_piece))
					{
						moving_piece = make_king(moving_piece);
					}
					copy_board[new_pos_y][new_pos_x] = moving_piece;
					start_x = new_pos_x;
					start_y = new_pos_y;
				}
				else if (new_pos_y > start_y) // down
				{
					for (int i = start_y, j = start_x; i <= new_pos_y && j >= new_pos_x; ++i, --j)
					{
						copy_board[i][j] = Pieces::empty;
					}
					if (should_make_king(Position{ new_pos_y,new_pos_x }, moving_piece))
					{
						moving_piece = make_king(moving_piece);
					}
					copy_board[new_pos_y][new_pos_x] = moving_piece;
					start_x = new_pos_x;
					start_y = new_pos_y;
				}
			}
		}
	}

	return copy_board;
}

int Draughts::letter_to_int(const char letter)
{
	if (letter== 'a')return 0;
	else if (letter == 'b')return 1;
	else if (letter == 'c')return 2;
	else if (letter == 'd')return 3;
	else if (letter == 'e')return 4;
	else if (letter == 'f')return 5;
	else if (letter == 'g')return 6;
	else if (letter == 'h')return 7;
	else throw std::string("Wrong number of column: " + std::string{ letter });
}

void Draughts::check_entered_number_of_row(const int number)
{
	if (number >= 8 || number < 0)throw std::string("Wrong number of row: " + std::to_string(number));
}

