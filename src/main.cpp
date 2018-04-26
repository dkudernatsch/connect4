//
// Created by daniel on 4/19/18.
//
#include "connect4_function.h"
#include <memory>
#include <iostream>

#ifndef TESTS

int main() {
    auto gameboard = std::make_unique<game_board>(9, 6);

    const auto p1 = std::make_unique<human_player>('H');
    const auto p2 = std::make_unique<computer_player>('C', gameboard.get());

    const players* current_player = (players*) p2.get();


    while(!gameboard->win(current_player->getmName())){
        current_player = (current_player == (players*) p1.get())
                         ? (players*) p2.get()
                         : (players*) p1.get();

        gameboard->print_board();
        while (!gameboard->put_coin(current_player->throw_coin(), current_player->getmName()));
    }

    /*while (!gameboard->win(p1->getmName())
       &&  !gameboard->win(p2->getmName())) {

        while (!gameboard->put_coin(p1->throw_coin(), p1->getmName()));
        gameboard->print_board();
        while (!gameboard->put_coin(p2->throw_coin(), p2->getmName()));
        gameboard->print_board();
    }*/

    gameboard->print_board();
    std::cout
            << "congratulations player "
                 << (gameboard->win(p1->getmName())
                    ? p1->getmName()
                    : p2->getmName())
            << ". You have won!" << std::endl;
}

#endif