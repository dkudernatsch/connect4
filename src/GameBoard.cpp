//
// Created by daniel on 4/19/18.
//
#include <vector>
#include <cctype>
#include <iostream>
#include <cassert>
#include "connect4_function.h"

game_board::game_board(std::size_t width, std::size_t height)
        : height(height)
        , width(width)
        , field(width, std::vector<char>(height, '.'))
{

    for(int i = 0; i < height-1; ++i){
        field[width-1][i] = static_cast<char>('1' + i);
    }

    for(int i = 0; i < width-1; ++i){
        field[i][height-1] = static_cast<char>('1' + i);
    }

    field[width-1][height-1] = ' ';
}

bool game_board::is_full() const {
    for(size_t i = 0; i < width-1; ++i){
        if(field[i][0] == '.') return true;
    }
    return false;
}

bool game_board::put_coin(int column, char player) {
    assert(("Column is to big", column < width));
    assert(("Column has to be bigger than 0", column >= 1));
    //if line is full return
    if(field[column-1][0] != '.') return false;

    for(auto it = field[column-1].rbegin()+1; it != field[column].rend(); ++it){
        if(*it == '.'){
            *it = player;
            if(check_win(player, column-1, (int) std::distance(it, field[column-1].rend()) - 1)){
                won = player;
            }
            return true;
        }
    }
    assert(("Should never happen", false));
}

bool game_board::win(char player) const {
    return won == player;
}

void game_board::print_board() const {
    for(size_t y = 0; y < height; ++y){
        for(size_t x = 0; x < width; ++x){
            std::cout << field[x][y];
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

const std::vector <std::vector<char>> &game_board::getField() const {
    return field;
}




int game_board::connected_squares(char p, int x, int y, int dx, int dy) const {
    int connected = 0;
    //go dir
    int _x = x;
    int _y = y;

    while(index_check(_x, _y) && field[_x][_y] == p){
        connected++;
        _x += dx;
        _y += dy;
    }

    //go -dir
    _x = x - dx;
    _y = y - dy;

    while(index_check(_x, _y) && field[_x][_y] == p){
        connected++;
        _x -= dx;
        _y -= dy;
    }

    return connected;
}

bool game_board::index_check(int x, int y) const {
    return     x >= 0
            && x <= width-2
            && y >= 0
            && y <= height-2;
}

bool game_board::check_win(char p, int x, int y) const {
    return connected_squares(p, x, y, 1, 0) >= 4
        || connected_squares(p, x, y, 0, 1) >= 4
        || connected_squares(p, x, y, 1, 1) >= 4
        || connected_squares(p, x, y, 1,-1) >= 4;
}
