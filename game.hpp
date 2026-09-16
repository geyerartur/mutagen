#pragma once
#include <vector>
#include <string>

struct Vec2 {
  int x;
  int y;
};

struct Player {
  Vec2 position;
  Vec2 aiming_at;

  std::string name;
  int health;

  bool reloading;
  int ammo;
};

struct Bulet {
  Vec2 position;
  Vec2 origin;
  Vec2 target;

  Player* owner;
};

struct GameState {
  Player player1;
  Player player2;



  std::vector<Bulet> bulets;
};
