#pragma once

#include <string>
#include <vector>

namespace Game {
enum class PlayerId { Player1, Player2 };

struct Vec2 {
  int x;
  int y;
};

struct Player {
  PlayerId id;
  Vec2 position;
  Vec2 aiming_at;

  std::string name;

  int health;

  bool reloading;
  int reload_steps;

  int ammo;
  int max_ammo;
};

struct Bullet {
  Vec2 position;
  Vec2 origin;
  Vec2 target;

  PlayerId owner;
};

struct GameState {
  Player player1;
  Player player2;

  int rows;
  int cols;
  int step;

  std::vector<Bullet> bullets;
};

GameState init(int starting_health, int ammo, int rows, int cols);

void move_player(GameState &state, int player, Vec2 direction);
void aim(GameState &state, int player, Vec2 target);
void shoot(GameState &state, int player);
void reload(GameState &state, int player);

void step(GameState &state);

} // namespace Game
