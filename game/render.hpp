#pragma once 

#include "./player.hpp"

struct Screen {
  int cols;
  int rows;
};


void drawScreen(const Screen& screen, const Position& player1_pos, const Position& player2_pos);
