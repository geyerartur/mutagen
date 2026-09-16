#include <locale.h>
#include <ncurses.h>
#include <panel.h>
#include <random>

#include "./game.hpp"

int random_int(int min, int max) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(min, max);

  return dist(gen);
}

const bool headless = false;

void print_player(WINDOW *win, int y, int x, const Player &player) {
  mvwprintw(win, y++, x, "Name: %s", player.name.c_str());
  mvwprintw(win, y++, x, "Position: (%d, %d)", player.position.x,
            player.position.y);
  mvwprintw(win, y++, x, "Aiming at: (%d, %d)", player.aiming_at.x,
            player.aiming_at.y);
  mvwprintw(win, y++, x, "Health: %d", player.health);
  mvwprintw(win, y++, x, "Reloading: %s", player.reloading ? "true" : "false");
  mvwprintw(win, y++, x, "Ammo: %d", player.ammo);
}

int main(void) {

  GameState game_state{.player1 = {.position = {.x = 5, .y = 5},
                                   .aiming_at = {.x = 0, .y = 0},
                                   .name = "Player 1",
                                   .health = 100,
                                   .reloading = false,
                                   .ammo = 10},
                       .player2 = {.position = {.x = 10, .y = 10},
                                   .aiming_at = {.x = 0, .y = 0},
                                   .name = "Player 2",
                                   .health = 100,
                                   .reloading = false,
                                   .ammo = 10},
                       .bulets = {}};
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

  WINDOW *overlay_win = newwin(10, 44, 0, 0);

  if (overlay_win == NULL) {
    endwin();
    return 1;
  }

  PANEL *overlay_panel = new_panel(overlay_win);

  if (overlay_panel == NULL) {
    delwin(overlay_win);
    endwin();
    return 1;
  }

  while (1) {
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    werase(stdscr);

    game_state.player1.position.x = random_int(0, cols - 1);
    game_state.player1.position.y = random_int(0, rows - 1);

    game_state.player2.position.x = random_int(0, cols - 1);
    game_state.player2.position.y = random_int(0, rows - 1);

    if (rows > 0 && cols > 4) {
      for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
          if (x == game_state.player1.position.x &&
              y == game_state.player1.position.y) {
            if (has_colors())
              attron(COLOR_PAIR(1));
            mvaddstr(y, x, "█");
            if (has_colors())
              attroff(COLOR_PAIR(1));
          } else if (x == game_state.player2.position.x &&
                     y == game_state.player2.position.y) {
            if (has_colors())
              attron(COLOR_PAIR(2));
            mvaddstr(y, x, "█");
            if (has_colors())
              attroff(COLOR_PAIR(2));
          } // else {
            // mvaddstr(y, x, ".");
          //}
        }
      }

      /*
       * Draw the overlay window.
       */
      werase(overlay_win);

      if (has_colors())
        wattron(overlay_win, COLOR_PAIR(3));

      box(overlay_win, 0, 0);

      mvwprintw(overlay_win, 1, 2, "MUTAGEN");
      print_player(overlay_win, 3, 2, game_state.player1);
      print_player(overlay_win, 3, 25, game_state.player2);

      if (has_colors())
        wattroff(overlay_win, COLOR_PAIR(3));

      update_panels();

      doupdate();

      int ch = getch();

      if (ch == 'q' || ch == 'Q')
        break;

      if (ch == KEY_RESIZE) {
        wclear(overlay_win);
      }
    }
  }
  del_panel(overlay_panel);
  delwin(overlay_win);

  endwin();

  return 0;
}
