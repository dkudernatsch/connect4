//
// Created by daniel on 4/19/18.
//

#include <cstdlib>
#include "connect4_function.h"

computer_player::computer_player(const char &name, game_board *spielfeld)
    : mName(name)
    , gameboard(spielfeld)
{}

int computer_player::throw_coin() const {
    return 1;
}

const char &computer_player::getmName() const {
    return mName;
}
