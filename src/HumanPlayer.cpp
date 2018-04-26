//
// Created by daniel on 4/19/18.
//
#include <iostream>
#include "connect4_function.h"
human_player::human_player(const char &name)
    : mName(name)
{}

int human_player::throw_coin() const {
    std::cout << mName << "'s turn:\n";
    std::cout << "Throw a coin by typing the column number\n";
    std::cout << "> " << std::flush;
    int i = -1;
    std::cin >> i;
    return i;
}

const char &human_player::getmName() const {
    return mName;
}
