#include <locale.h>
#include <ncurses.h>
#include <panel.h>

#include "./game/game.hpp"
#include "./input/input.hpp"
#include "./renderer/renderer.hpp"

int main(void) {
  if (!Renderer::init()) {
    return 1;
  }
  int rows, cols;
  getmaxyx(stdscr, rows, cols);

  Game::GameState state = Game::init(100, 10, rows, cols);

  bool running = true;

  while (running) {
    Renderer::RenderResult render_result = Renderer::render(state);

    if (render_result == Renderer::RenderResult::Quit) {
      Renderer::shutdown();
      running = false;
      break;
    }
  }

  return 0;
}
