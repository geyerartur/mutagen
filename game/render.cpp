#include <iostream>
#include <ncursesw/ncurses.h>



#include "./ansi.hpp"
#include "./player.hpp"
#include "./render.hpp"



void drawScreen(
    const Screen& screen,
    const Position& player1_pos,
    const Position& player2_pos
) {

    attron(COLOR_PAIR(1));
    mvaddwstr(player1_pos.y, player1_pos.x, L"█");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    mvaddwstr(player2_pos.y, player2_pos.x, L"█");
    attroff(COLOR_PAIR(2));
}
