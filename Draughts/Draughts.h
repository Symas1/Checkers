#ifndef DRAUGHTS_H_
#define DRAUGHTS_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>

#include "utilities\rlutil.h"

enum  class Pieces { empty, dark_piece, light_piece, dark_piece_promoted, light_piece_promoted };
enum class Move_type { step_right_up, step_right_down, jump_right_up, jump_right_down,step_left_up,step_left_down,jump_left_up,jump_left_down};

struct Position
{
	Position(int rows, int cols) :rows{rows}, cols{cols}{};
	int rows;
	int cols;
};

const int cell_width = 3;
const int outer_threads = 8;
const int inner_threads = 1;
static std::mutex m;

class Draughts
{
public:
	Draughts() { this->generate_new_board(); };

	/*
	Creates new board from existing one
	@param board to copy from
	@param piece to move
	@param new place
	*/
	Draughts(Draughts& old_board,const Position& position, Move_type move_type,int number_of_squares);

	/*
	reads board from the file
	@param file_name
	*/
	Draughts(std::string&& file_name);

	/*
	generates new board with pieces on the right places
	*/
	void generate_new_board();

	std::vector<std::vector<Pieces>>& get_board();

	void draw_board();

	/*
	returns true if this is an ending position
	@return
	*/
	bool game_over(bool player1);

	/*
	returns the vector of legal deviant board positions
	@return
	*/
	std::vector<std::unique_ptr<Draughts>> get_moves(bool player1);

	/*
	returns jump moves for the given piece
	@param position of piece
	@return
	*/
	std::vector<std::unique_ptr<Draughts>> get_jump_moves(const Position & position);

	/*
	returns step moves for the given piece
	@param position of piece
	@return
	*/
	std::vector<std::unique_ptr<Draughts>> get_step_moves(const Position & position);

	/*
	returns true if a piece can jump from jump_from, over jump_over to jump_to
	@param jump_from position
	@param jump_over position
	@param jump_to position
	@return
	*/
	bool jump_ok(const Position& jump_from,const Position & jump_over,const Position& jump_to);

	/*
	returns true if a piece can step from step_from to step_to
	@param step_from position
	@param step_to position
	@return
	*/
	bool Draughts::step_ok(const Position& step_from, const Position& step_to);

	/*
	true if the given coordinates are open
	@param position
	@return
	*/
	bool is_open(const Position& position);

	/*
	returns true if given position belongs to board 
	@param position
	@return
	*/
	bool in_bounds(const Position& position);

	/*
	returns true if diagonal between pieces is empty
	@param starting piece position
	@param ending piece position
	@return
	*/
	bool Draughts::diagonal_between_pieces_is_empty(const Position& start_piece,const Position& end_piece);

	/*
	returns true if two pieces are enemies
	@param first_piece
	@param second_piece
	@return
	*/
	bool Draughts::is_enemy(const Position& first_piece,const Position& second_piece);

	/*
	return position of first enemy on the diagonal or nullptr if there is a friend piece before first enemy piece or nullptr in other case
	@param starting piece
	@param what direction look to
	@return
	*/
	std::unique_ptr<Position> Draughts::find_enemy_on_the_diagonal(const Position& start_piece, Move_type move_type);

	/*
	returns value for the board
	@return
	*/
	int board_value();

	void outer_thread_jump_func(std::vector<std::unique_ptr<Draughts>>&moves,int i,bool player1);
	void inner_thread_jump_func(std::vector<std::unique_ptr<Draughts>>&moves, int i,int j);

	void outer_thread_step_func(std::vector<std::unique_ptr<Draughts>>&moves, int i, bool player1);
	void inner_thread_step_func(std::vector<std::unique_ptr<Draughts>>&moves, int i, int j);
	bool check_for_row();

	Pieces make_king(Pieces moved_piece);
	bool should_make_king(const Position& new_position, Pieces moved_piece);

	std::vector<std::vector<Pieces>> make_move(std::string move,bool player1);

	int letter_to_int(const char letter);

	void Draughts::check_entered_number_of_row(const int number);
private:
	std::vector<std::vector<Pieces>>board;
};

#endif // DRAUGHTS_H_

