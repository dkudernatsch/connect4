#ifdef TESTS

#include <iostream>
#include "connect4_function.h"
#include <gtest/gtest.h>

TEST(GAMEBOARD, CONSTRUCTOR_SET_WIDTH_AND_HEIGHT)
{
    game_board* gameboard = new game_board(9, 6);
    ASSERT_EQ(gameboard->width, 9);
    ASSERT_EQ(gameboard->height, 6);
    delete(gameboard);
}

TEST(GAMEBOARD, CONSTRUCTOR_INIT_FIELD)
{
    game_board* gameboard = new game_board(9, 6);
    for (int i = 0; i < gameboard->width; ++i) {
        for (int j = 0; j < gameboard->height; ++j) {
            if (i == 8 && j == 5) {
                ASSERT_EQ(gameboard->field[i][j], ' ');
            }
            else if (i == 8) {

                ASSERT_EQ(gameboard->field[i][j], j + '1');
            }
            else if (j == 5) {
                ASSERT_EQ(gameboard->field[i][j], i + 49);
            }
            else {
                ASSERT_EQ(gameboard->field[i][j], '.');
            }
        }
    }
    delete(gameboard);
}

TEST(HUMAN_PLAYER, GET_NAME)
{
    players* player = new human_player('A');
    ASSERT_EQ(player->getmName(), 'A');
    delete(player);
}

TEST(COMPUTER_PLAYER, GET_NAME)
{
    game_board* gameboard = new game_board(9, 6);
    players* player = new computer_player('A', gameboard);
    ASSERT_EQ(player->getmName(), 'A');

    delete(player);
    delete(gameboard);
}

TEST(COMPUTER_PLAYER, THROW_COIN)
{
    game_board* gameboard = new game_board(9, 6);
    players* player = new computer_player('A', gameboard);
    int column = player->throw_coin();
    EXPECT_TRUE(column > 0 && column < 9);

    delete(player);
    delete(gameboard);
}

TEST(GAMEBOARD, PUT_COIN_COLUMN_NOT_FULL)
{
    game_board* gameboard = new game_board(9, 6);
    bool next_turn = false;

    next_turn = gameboard->put_coin(1, 'A');
    EXPECT_TRUE(next_turn);
    ASSERT_EQ(gameboard->field[0][4], 'A');

    delete(gameboard);
}

TEST(GAMEBOARD, PUT_COIN_COLUMN_FULL)
{
    game_board* gameboard = new game_board(9, 6);
    bool next_turn = false;

    next_turn = gameboard->put_coin(1, 'A');
    EXPECT_TRUE(next_turn);
    ASSERT_EQ(gameboard->field[0][4], 'A');

    next_turn = gameboard->put_coin(1, 'A');
    EXPECT_TRUE(next_turn);
    ASSERT_EQ(gameboard->field[0][3], 'A');

    next_turn = gameboard->put_coin(1, 'A');
    EXPECT_TRUE(next_turn);
    ASSERT_EQ(gameboard->field[0][2], 'A');

    next_turn = gameboard->put_coin(1, 'A');
    EXPECT_TRUE(next_turn);
    ASSERT_EQ(gameboard->field[0][1], 'A');

    next_turn = gameboard->put_coin(1, 'A');
    EXPECT_TRUE(next_turn);
    ASSERT_EQ(gameboard->field[0][0], 'A');

    next_turn = gameboard->put_coin(1, 'A');
    EXPECT_TRUE(!next_turn);

    delete(gameboard);
}

TEST(GAMEBOARD, PUT_4_COINS)
{
    game_board* gameboard = new game_board(9, 6);
    players* a = new computer_player('A', gameboard);
    players* b = new computer_player('B', gameboard);
    int column = 0;
    int count_a = 0;
    int count_b = 0;

    column = a->throw_coin();
    gameboard->put_coin(column, 'A');

    column = b->throw_coin();
    gameboard->put_coin(column, 'B');

    column = a->throw_coin();
    gameboard->put_coin(column, 'A');

    column = b->throw_coin();
    gameboard->put_coin(column, 'B');

    for (int i = 0; i<gameboard->width; ++i) {
        for (int j = 0; j<gameboard->height; ++j) {
            if (gameboard->field[i][j] == 'A') {
                count_a++;
            }
            else if (gameboard->field[i][j] == 'B') {
                count_b++;
            }
        }
    }

    ASSERT_EQ(count_a, 2);
    ASSERT_EQ(count_b, 2);

    delete(a);
    delete(b);
    delete(gameboard);
}

TEST(GAMEBOARD, PRINT_BOARD)
{
    game_board* gameboard = new game_board(9, 6);

    testing::internal::CaptureStdout();
    gameboard->print_board();
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "........1\n........2\n........3\n........4\n........5\n12345678 \n\n";

    ASSERT_EQ(output, expected);

    delete(gameboard);
}

TEST(GAMEBOARD, WIN_CONDITION_HORIZONTAL)
{
    game_board* gameboard = new game_board(9, 6);
    bool win = false;

    gameboard->put_coin(1, 'A');
    gameboard->put_coin(2, 'A');
    gameboard->put_coin(3, 'A');
    gameboard->put_coin(4, 'A');

    win = gameboard->win('A');

    EXPECT_TRUE(win);

    delete(gameboard);
}

TEST(GAMEBOARD, WIN_CONDITION_VERTICAL)
{
    game_board* gameboard = new game_board(9, 6);
    bool win = false;

    gameboard->put_coin(1, 'A');
    gameboard->put_coin(1, 'A');
    gameboard->put_coin(1, 'A');
    gameboard->put_coin(1, 'A');

    win = gameboard->win('A');

    EXPECT_TRUE(win);

    delete(gameboard);
}

TEST(GAMEBOARD, WIN_CONDITION_DIAGONAL_BOT_TOP)
{
    game_board* gameboard = new game_board(9, 6);
    bool win = false;

    gameboard->put_coin(1, 'A');

    gameboard->put_coin(2, 'B');
    gameboard->put_coin(2, 'A');

    gameboard->put_coin(3, 'B');
    gameboard->put_coin(3, 'B');
    gameboard->put_coin(3, 'A');

    gameboard->put_coin(4, 'B');
    gameboard->put_coin(4, 'B');
    gameboard->put_coin(4, 'B');
    gameboard->put_coin(4, 'A');

    win = gameboard->win('A');

    EXPECT_TRUE(win);

    delete(gameboard);
}

TEST(GAMEBOARD, WIN_CONDITION_DIAGONAL_TOP_BOT)
{
    game_board* gameboard = new game_board(9, 6);
    bool win = false;

    gameboard->put_coin(1, 'B');
    gameboard->put_coin(1, 'B');
    gameboard->put_coin(1, 'B');
    gameboard->put_coin(1, 'A');

    gameboard->put_coin(2, 'B');
    gameboard->put_coin(2, 'B');
    gameboard->put_coin(2, 'A');

    gameboard->put_coin(3, 'B');
    gameboard->put_coin(3, 'A');

    gameboard->put_coin(4, 'A');

    win = gameboard->win('A');

    EXPECT_TRUE(win);

    delete(gameboard);
}

TEST(GAMEBOARD, NO_WIN_HORIZONTAL)
{
    game_board* gameboard = new game_board(9, 6);
    bool win = true;

    gameboard->put_coin(1, 'A');
    gameboard->put_coin(2, 'A');
    gameboard->put_coin(3, 'A');
    gameboard->put_coin(5, 'A');

    win = gameboard->win('A');

    EXPECT_TRUE(!win);

    delete(gameboard);
}

TEST(GAMEBOARD, NO_WIN_VERTICAL)
{
    game_board* gameboard = new game_board(9, 6);
    bool win = true;

    gameboard->put_coin(1, 'A');
    gameboard->put_coin(1, 'A');
    gameboard->put_coin(1, 'A');
    gameboard->put_coin(1, 'B');
    gameboard->put_coin(1, 'A');

    win = gameboard->win('A');

    EXPECT_TRUE(!win);

    delete(gameboard);
}

TEST(GAMEBOARD, NO_WIN_DIAGONAL_BOT_TOP)
{
    game_board* gameboard = new game_board(9, 6);
    bool win = false;

    gameboard->put_coin(1, 'A');

    gameboard->put_coin(2, 'B');
    gameboard->put_coin(2, 'A');

    gameboard->put_coin(3, 'B');
    gameboard->put_coin(3, 'A');
    gameboard->put_coin(3, 'B');

    gameboard->put_coin(4, 'B');
    gameboard->put_coin(4, 'B');
    gameboard->put_coin(4, 'B');
    gameboard->put_coin(4, 'A');

    win = gameboard->win('A');

    EXPECT_TRUE(!win);

    delete(gameboard);
}

TEST(GAMEBOARD, NO_WIN_DIAGONAL_TOP_BOT)
{
    game_board* gameboard = new game_board(9, 6);
    bool win = false;

    gameboard->put_coin(1, 'B');
    gameboard->put_coin(1, 'B');
    gameboard->put_coin(1, 'A');
    gameboard->put_coin(1, 'B');

    gameboard->put_coin(2, 'B');
    gameboard->put_coin(2, 'B');
    gameboard->put_coin(2, 'A');

    gameboard->put_coin(3, 'B');
    gameboard->put_coin(3, 'A');

    gameboard->put_coin(4, 'A');

    win = gameboard->win('A');

    EXPECT_TRUE(!win);

    delete(gameboard);
}



int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif