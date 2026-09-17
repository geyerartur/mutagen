#include "./game.hpp"

#include <random>
#include <stdexcept>

namespace Game {
int random_int(int min, int max) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(min, max);

  return dist(gen);
}

GameState init(int starting_health, int ammo, int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Game dimensions must be positive");
  }
  Game::GameState game_state{
      .player1 = {.id = Game::PlayerId::Player1,
                  .position = {.x = random_int(0, cols - 1),
                               .y = random_int(0, rows - 1)},
                  .aiming_at = {.x = 0, .y = 0},
                  .name = "Player 1",
                  .health = starting_health,
                  .reloading = false,
                  .ammo = ammo,
                  .max_ammo = ammo},
      .player2 = {.id = Game::PlayerId::Player2,
                  .position = {.x = random_int(0, cols - 1),
                               .y = random_int(0, rows - 1)},

                  .aiming_at = {.x = 0, .y = 0},
                  .name = "Player 2",
                  .health = starting_health,
                  .reloading = false,
                  .ammo = ammo,
                  .max_ammo = ammo},
      .rows = rows,
      .cols = cols,
      .step = 0,
      .bullets = {}

  };

  return game_state;
}

void move_player(GameState &state, Player &player, int dx, int dy) {
  player.position.x += dx;
  player.position.y += dy;

  // Ensure the player stays within bounds
  if (player.position.x < 0)
    player.position.x = 0;
  else if (player.position.x >= state.cols)
    player.position.x = state.cols - 1;

  if (player.position.y < 0)
    player.position.y = 0;
  else if (player.position.y >= state.rows)
    player.position.y = state.rows - 1;
}

void shoot(GameState &state, Player &player) {
  if (player.ammo > 0 && !player.reloading) {
    Bullet new_bullet{.position = player.position,
                      .origin = player.position,
                      .target = player.aiming_at,
                      .owner = player.id};
    state.bullets.push_back(new_bullet);
    player.ammo--;
  }
}

void reload(Player &player) {
  if (!player.reloading && player.ammo < player.max_ammo) {
    player.reloading = true;
    player.reload_steps = 2;
  }
  if (player.reloading) {
    player.reload_steps -= 1;
  }
  if (player.reloading && player.reload_steps <= 0) {
    player.ammo = player.max_ammo;
    player.reloading = false;
    player.reload_steps = 2;
  }
}
} // namespace Game
