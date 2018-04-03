#include "catch.hpp"
#include "../Draughts/Draughts.h"

TEST_CASE("diagonal_between_pieces_is_empty()")
{
	Draughts draughts{ "diagonal_between_pieces_is_empty().txt" };

	SECTION("end_piece is to the right of the start_piece")
	{
		SECTION("end_piece is above the start_piece")
		{
			CHECK(true == draughts.diagonal_between_pieces_is_empty(Position{ 3,4 }, Position{ 1,6 }));
			CHECK(true == draughts.diagonal_between_pieces_is_empty(Position{ 1,6 }, Position{ 0,7 }));
			CHECK(false == draughts.diagonal_between_pieces_is_empty(Position{ 3,4 }, Position{ 0,7 }));
		}
		SECTION("end_piece is under the start_piece")
		{
			CHECK(true == draughts.diagonal_between_pieces_is_empty(Position{ 3,4 }, Position{ 5,6 }));
			CHECK(true == draughts.diagonal_between_pieces_is_empty(Position{ 5,6 }, Position{ 6,7 }));
			CHECK(false == draughts.diagonal_between_pieces_is_empty(Position{ 3,4 }, Position{ 6,7 }));
		}
	}
	SECTION("end_piece is to the left of the start_piece")
	{
		SECTION("end_piece is above the start_piece")
		{
			CHECK(true == draughts.diagonal_between_pieces_is_empty(Position{ 3,4 }, Position{ 1,2 }));
			CHECK(true == draughts.diagonal_between_pieces_is_empty(Position{ 1,2 }, Position{ 0,1 }));
			CHECK(false == draughts.diagonal_between_pieces_is_empty(Position{ 3,4 }, Position{ 0,1 }));
		}
		SECTION("end_piece is under the start_piece")
		{
			CHECK(true == draughts.diagonal_between_pieces_is_empty(Position{ 3,4 }, Position{ 6,1 }));
			CHECK(true == draughts.diagonal_between_pieces_is_empty(Position{ 6,1 }, Position{ 7,0 }));
			CHECK(false == draughts.diagonal_between_pieces_is_empty(Position{ 3,4 }, Position{ 7,0 }));
		}
	}
}


TEST_CASE("in_bounds()")
{
	Draughts draughts{ "in_bounds().txt" };

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			CHECK(true == draughts.in_bounds(Position{ i,j }));
		}
	}

	CHECK(false == draughts.in_bounds(Position{ 8,8 }));
	CHECK(false == draughts.in_bounds(Position{ 8,0 }));
	CHECK(false == draughts.in_bounds(Position{ 0,8 }));
	CHECK(false == draughts.in_bounds(Position{ -1,0 }));
}


TEST_CASE("is_open()")
{
	SECTION("is_open() true")
	{
		Draughts draughts{ "is_open_true().txt" };
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				CHECK(true == draughts.is_open(Position{ i,j }));
			}
		}
	}

	SECTION("is_open() false")
	{
		Draughts draughts{ "is_open_false().txt" };
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				CHECK(false == draughts.is_open(Position{ i,j }));
			}
		}
	}
}


TEST_CASE("is_enemy()")
{
	Draughts draughts{ "is_enemy().txt" };
	SECTION("Enemy for dark_piece")
	{
		CHECK(true == draughts.is_enemy(Position{ 0,0 }, Position{ 0,1 }));
		CHECK(true == draughts.is_enemy(Position{ 0,0 }, Position{ 0,2 }));
		CHECK(false == draughts.is_enemy(Position{ 0,0 }, Position{ 0,3 }));
		CHECK(false == draughts.is_enemy(Position{ 0,0 }, Position{ 0,4 }));
	}

	SECTION("Enemy for light_piece")
	{
		CHECK(true == draughts.is_enemy(Position{ 1,0 }, Position{ 1,1 }));
		CHECK(true == draughts.is_enemy(Position{ 1,0 }, Position{ 1,2 }));
		CHECK(false == draughts.is_enemy(Position{ 1,0 }, Position{ 1,3 }));
		CHECK(false == draughts.is_enemy(Position{ 1,0 }, Position{ 1,4 }));
	}

	SECTION("Enemy for dark_piece_promoted")
	{
		CHECK(true == draughts.is_enemy(Position{ 2,0 }, Position{ 2,1 }));
		CHECK(true == draughts.is_enemy(Position{ 2,0 }, Position{ 2,2 }));
		CHECK(false == draughts.is_enemy(Position{ 2,0 }, Position{ 2,3 }));
		CHECK(false == draughts.is_enemy(Position{ 2,0 }, Position{ 2,4 }));
	}

	SECTION("Enemy for light_piece_promoted")
	{
		CHECK(true == draughts.is_enemy(Position{ 3,0 }, Position{ 3,1 }));
		CHECK(true == draughts.is_enemy(Position{ 3,0 }, Position{ 3,2 }));
		CHECK(false == draughts.is_enemy(Position{ 3,0 }, Position{ 3,3 }));
		CHECK(false == draughts.is_enemy(Position{ 3,0 }, Position{ 3,4 }));
	}
}


TEST_CASE("find_enemy_on_the_diagonal()")
{
	SECTION("Test for empty diagonals (diagonal has neither enemy pieces nor friend pieces)")
	{
		Draughts draughts{ "find_enemy_on_the_diagonal_empty_diagonals().txt" };
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				CHECK(nullptr == draughts.find_enemy_on_the_diagonal(Position{ i,j }, Move_type::jump_right_up));
				CHECK(nullptr == draughts.find_enemy_on_the_diagonal(Position{ i,j }, Move_type::jump_right_down));
				CHECK(nullptr == draughts.find_enemy_on_the_diagonal(Position{ i,j }, Move_type::jump_left_up));
				CHECK(nullptr == draughts.find_enemy_on_the_diagonal(Position{ i,j }, Move_type::jump_left_down));
			}
		}
	}

	SECTION("Test for diagonals with all friendly pieces")
	{
		Draughts draughts{ "find_enemy_on_the_diagonal_friend_diagonals().txt" };
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				CHECK(nullptr == draughts.find_enemy_on_the_diagonal(Position{ i,j }, Move_type::jump_right_up));
				CHECK(nullptr == draughts.find_enemy_on_the_diagonal(Position{ i,j }, Move_type::jump_right_down));
				CHECK(nullptr == draughts.find_enemy_on_the_diagonal(Position{ i,j }, Move_type::jump_left_up));
				CHECK(nullptr == draughts.find_enemy_on_the_diagonal(Position{ i,j }, Move_type::jump_left_down));
			}
		}
	}

	SECTION("Test for diagonals with enemy pieces")
	{
		Draughts draughts{ "find_enemy_on_the_diagonal_enemy_diagonals().txt" };
		CHECK(draughts.find_enemy_on_the_diagonal(Position{ 3 ,4 }, Move_type::jump_right_up) != nullptr);
		CHECK(draughts.find_enemy_on_the_diagonal(Position{ 3 ,4 }, Move_type::jump_right_down) != nullptr);
		CHECK(draughts.find_enemy_on_the_diagonal(Position{ 3 ,4 }, Move_type::jump_left_up) != nullptr);
		CHECK(draughts.find_enemy_on_the_diagonal(Position{ 3 ,4 }, Move_type::jump_left_down) != nullptr);

		SECTION("friend goes first before enemy")
		{
			CHECK(draughts.find_enemy_on_the_diagonal(Position{ 3 ,3 }, Move_type::jump_right_up) == nullptr);
			CHECK(draughts.find_enemy_on_the_diagonal(Position{ 3 ,3 }, Move_type::jump_right_down) == nullptr);
			CHECK(draughts.find_enemy_on_the_diagonal(Position{ 3 ,3 }, Move_type::jump_left_up) == nullptr);
			CHECK(draughts.find_enemy_on_the_diagonal(Position{ 3 ,3 }, Move_type::jump_left_down) == nullptr);
		}
	}
}


TEST_CASE("jump_ok()")
{
	SECTION("jump_ok_1().txt")
	{
		Draughts draughts{ "jump_ok_1().txt" };
		SECTION("Try to jump out of board")
		{
			SECTION("Right up")
			{
				CHECK(false == draughts.jump_ok(Position{ 1,1 }, Position{ 0,2 }, Position{ -1,3 }));
			}
			SECTION("Right down")
			{
				CHECK(false == draughts.jump_ok(Position{ 1,6 }, Position{ 2,7 }, Position{ 3,8 }));
			}
			SECTION("Left up")
			{
				CHECK(false == draughts.jump_ok(Position{ 1,1 }, Position{ 0,0 }, Position{ -1,-1 }));
			}
			SECTION("Left down")
			{
				CHECK(false == draughts.jump_ok(Position{ 1,1 }, Position{ 2,0 }, Position{ 3,-1 }));
			}
		}

		SECTION("Proper jump")
		{
			SECTION("Right up")
			{
				CHECK(true == draughts.jump_ok(Position{ 5,2 }, Position{ 4,3 }, Position{ 3,4 }));
			}
			SECTION("Right down")
			{
				CHECK(true == draughts.jump_ok(Position{ 5,2 }, Position{ 6,3 }, Position{ 7,4 }));
			}
			SECTION("Left up")
			{
				CHECK(true == draughts.jump_ok(Position{ 5,2 }, Position{ 4,1 }, Position{ 3,0 }));
			}
			SECTION("Left down")
			{
				CHECK(true == draughts.jump_ok(Position{ 5,2 }, Position{ 6,1 }, Position{ 7,0 }));
			}
		}

		SECTION("Try to jump to occupied cell")
		{
			SECTION("Right up")
			{
				CHECK(false == draughts.jump_ok(Position{ 5,5 }, Position{ 4,6 }, Position{ 3,7 }));
			}
			SECTION("Right down")
			{
				CHECK(false == draughts.jump_ok(Position{ 5,5 }, Position{ 6,6 }, Position{ 7,7 }));
			}
			SECTION("Left up")
			{
				CHECK(false == draughts.jump_ok(Position{ 5,5 }, Position{ 4,4 }, Position{ 3,3 }));
			}
			SECTION("Left down")
			{
				CHECK(false == draughts.jump_ok(Position{ 5,5 }, Position{ 6,4 }, Position{ 7,3 }));
			}
		}
	}

	SECTION("jump_ok_2().txt")
	{
		Draughts draughts{ "jump_ok_2().txt" };
		SECTION("Try to jump over empty cell")
		{
			SECTION("Right up")
			{
				CHECK(false == draughts.jump_ok(Position{ 2,2 }, Position{ 1,3 }, Position{ 0,4 }));
			}
			SECTION("Right down")
			{
				CHECK(false == draughts.jump_ok(Position{ 2,2 }, Position{ 3,3 }, Position{ 4,4 }));
			}
			SECTION("Left up")
			{
				CHECK(false == draughts.jump_ok(Position{ 2,2 }, Position{ 1,1 }, Position{ 0,0 }));
			}
			SECTION("Left down")
			{
				CHECK(false == draughts.jump_ok(Position{ 2,2 }, Position{ 3,1 }, Position{ 4,0 }));
			}
		}

		SECTION("Try to jump over friend")
		{
			SECTION("Right up")
			{
				CHECK(false == draughts.jump_ok(Position{ 5,5 }, Position{ 4,6 }, Position{ 3,7 }));
			}
			SECTION("Right down")
			{
				CHECK(false == draughts.jump_ok(Position{ 5,5 }, Position{ 6,6 }, Position{ 7,7 }));
			}
			SECTION("Left up")
			{
				CHECK(false == draughts.jump_ok(Position{ 5,5 }, Position{ 4,4 }, Position{ 3,3 }));
			}
			SECTION("Left down")
			{
				CHECK(false == draughts.jump_ok(Position{ 5,5 }, Position{ 6,4 }, Position{ 7,3 }));
			}
		}
	}
}


TEST_CASE("step_ok()")
{
	Draughts draughts{ "step_ok().txt" };
	SECTION("Usual pieces")
	{
		SECTION("Step is allowed")
		{
			CHECK(true == draughts.step_ok(Position{ 1,1 }, Position{ 0,2 })); // step right up
			CHECK(true == draughts.step_ok(Position{ 1,1 }, Position{ 2,2 })); // step right down
			CHECK(true == draughts.step_ok(Position{ 1,1 }, Position{ 0,0 })); // step left up
			CHECK(true == draughts.step_ok(Position{ 1,1 }, Position{ 2,0 })); // step left down
		}

		SECTION("Step is not allowed")
		{
			CHECK(false == draughts.step_ok(Position{ 1,4 }, Position{ 0,5 })); // step right up
			CHECK(false == draughts.step_ok(Position{ 1,4 }, Position{ 2,5 })); // step right down
			CHECK(false == draughts.step_ok(Position{ 1,4 }, Position{ 0,3 })); // step left up
			CHECK(false == draughts.step_ok(Position{ 1,4 }, Position{ 2,3 })); // step left down
		}

		SECTION("Step out of field")
		{
			CHECK(false == draughts.step_ok(Position{ 0,7 }, Position{ -1,8 })); // step right up
			CHECK(false == draughts.step_ok(Position{ 0,7 }, Position{ 1,8 })); // step right down
			CHECK(false == draughts.step_ok(Position{ 0,7 }, Position{ -1,6 })); // step left up
			CHECK(false == draughts.step_ok(Position{ 5,0 }, Position{ 6,-1 })); // step left down
		}
	}

	SECTION("Promoted pieces")
	{
		SECTION("Step is allowed")
		{
			CHECK(true == draughts.step_ok(Position{ 5,2 }, Position{ 3,4 })); // step right up
			CHECK(true == draughts.step_ok(Position{ 5,2 }, Position{ 7,4 })); // step right down
			CHECK(true == draughts.step_ok(Position{ 5,2 }, Position{ 3,0 })); // step left up
			CHECK(true == draughts.step_ok(Position{ 5,2 }, Position{ 7,0 })); // step left down
		}

		SECTION("Step is not allowed")
		{
			CHECK(false == draughts.step_ok(Position{ 5,5 }, Position{ 3,7 })); // step right up
			CHECK(false == draughts.step_ok(Position{ 5,5 }, Position{ 7,7 })); // step right down
			CHECK(false == draughts.step_ok(Position{ 5,5 }, Position{ 3,3 })); // step left up
			CHECK(false == draughts.step_ok(Position{ 5,5 }, Position{ 7,3 })); // step left down
		}

		SECTION("Step out of field")
		{
			CHECK(false == draughts.step_ok(Position{ 3,1 }, Position{ -1,5 })); // step right up
			CHECK(false == draughts.step_ok(Position{ 5,2 }, Position{ 8,5 })); // step right down
			CHECK(false == draughts.step_ok(Position{ 3,1 }, Position{ 1,-1 })); // step left up
			CHECK(false == draughts.step_ok(Position{ 5,2 }, Position{ 8,-1 })); // step left down
		}
	}
}


TEST_CASE("board_value()")
{
	Draughts draughts{ "board_value().txt" };

	SECTION("board value for light pieces")
	{
		CHECK(0 == draughts.board_value());
	}

	SECTION("board value for dark pieces")
	{
		CHECK(0 == draughts.board_value());
	}
}