#include "renderer.hpp"
#include "../game/game.hpp"

#include <locale.h>
#include <ncurses.h>
#include <panel.h>

namespace Renderer {

WINDOW *overlay_win = nullptr;
PANEL *overlay_panel = nullptr;

void print_player(WINDOW *win, int y, int x, const Game::Player &player) {
  mvwprintw(win, y++, x, "Name: %s", player.name.c_str());
  mvwprintw(win, y++, x, "Position: (%d, %d)", player.position.x,
            player.position.y);
  mvwprintw(win, y++, x, "Aiming at: (%d, %d)", player.aiming_at.x,
            player.aiming_at.y);
  mvwprintw(win, y++, x, "Health: %d", player.health);
  mvwprintw(win, y++, x, "Reloading: %s", player.reloading ? "true" : "false");
  mvwprintw(win, y++, x, "Ammo: %d", player.ammo);
}

bool init() {
  setlocale(LC_ALL, "");

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  timeout(100);

  if (has_colors()) {
    start_color();
    use_default_colors();

    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_BLUE, -1);
    init_pair(3, COLOR_WHITE, -1);
  }

  overlay_win = newwin(10, 44, 0, 0);

  if (!overlay_win) {
    endwin();
    return false;
  }

  overlay_panel = new_panel(overlay_win);

  if (!overlay_panel) {
    delwin(overlay_win);
    endwin();
    return false;
  }

  return true;
}

void render_overlay(const Game::GameState &state) {
  werase(overlay_win);

  if (has_colors())
    wattron(overlay_win, COLOR_PAIR(3));

  box(overlay_win, 0, 0);

  mvwprintw(overlay_win, 1, 2, "MUTAGEN");
  print_player(overlay_win, 3, 2, state.player1);
  print_player(overlay_win, 3, 25, state.player2);

  if (has_colors())
    wattroff(overlay_win, COLOR_PAIR(3));

  update_panels();

  doupdate();
}

void render_game(const Game::GameState &state) {
  for (int y = 0; y < state.rows; ++y) {
    for (int x = 0; x < state.cols; ++x) {

      if (x == state.player1.position.x && y == state.player1.position.y) {

        if (has_colors())
          attron(COLOR_PAIR(1));

        mvaddstr(y, x, "█");

        if (has_colors())
          attroff(COLOR_PAIR(1));
      }

      else if (x == state.player2.position.x && y == state.player2.position.y) {

        if (has_colors())
          attron(COLOR_PAIR(2));

        mvaddstr(y, x, "█");

        if (has_colors())
          attroff(COLOR_PAIR(2));
      }
    }
  }
}

RenderResult render(const Game::GameState &state) {
  werase(stdscr);

  render_game(state);
  render_overlay(state);

  update_panels();
  doupdate();

  int ch = getch();

  if (ch == 'q' || ch == 'Q') {
    return RenderResult::Quit;
  }

  return RenderResult::Continue;
}

void shutdown() {
  if (overlay_panel)
    del_panel(overlay_panel);

  if (overlay_win)
    delwin(overlay_win);

  endwin();
}
} // namespace Renderer
