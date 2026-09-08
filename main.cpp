#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ncursesw/ncurses.h>
#include <chrono>
#include <thread>

#include "./game/ansi.hpp"
#include "./game/render.hpp"
#include "./game/player.hpp"

//const int ROWS = 32;
//const int COLS = 128;

char key;

int main() {
    std::vector<std::vector<bool>> grid(
        32,
        std::vector<bool>(32, false)
    );

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distX(0, 32 - 1);
    std::uniform_int_distribution<> distY(0, 32 - 1);

    
    const Screen screen{
      .cols = 32,
      .rows = 32
    };
    
    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    noecho();
    curs_set(0);

    nodelay(stdscr, TRUE); // Non-blocking input
    
    if (has_colors()) {
      start_color();
      init_pair(1, COLOR_RED, COLOR_BLACK);
      init_pair(2, COLOR_BLUE, COLOR_BLACK);
    }

    while (true) {
        Position player1_pos{
      .x = distX(gen),
      .y = distY(gen)
    };

    Position player2_pos{
      .x = distX(gen),
      .y = distY(gen)
    };


        // Clear the console
        
        clear();

        // Draw the grid with players
        drawScreen(screen, player1_pos, player2_pos);

        refresh();

        // Handle player input
        int input = getch();
        if (input == 'q') {
            endwin();
            std::cout << ansi::RESET << std::flush;
            break; // Exit the game loop
        };

        std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Control the game speed
    }
}

