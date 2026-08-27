#include <iostream>
#include <string>
#include <vector>
#include <random>

#include "./game/ansi.hpp"

constexpr int ROWS = 32;
constexpr int COLS = 128;

int main() {
    std::vector<std::vector<bool>> grid(
        ROWS,
        std::vector<bool>(COLS, false)
    );

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distX(0, ROWS - 1);
    std::uniform_int_distribution<> distY(0, COLS - 1);

    std::vector<int> player1_pos = {distX(gen), distY(gen)};
    std::vector<int> player2_pos = {distX(gen), distY(gen)};



    std::cout << "Player 1 position: " << player1_pos[0] << ", " << player1_pos[1] << std::endl;
    std::cout << "Player 2 position: " << player2_pos[0] << ", " << player2_pos[1] << std::endl;





    std::cout << ansi::bg::BLACK;

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (row == player1_pos[0] && col == player1_pos[1]) {
                std::cout << ansi::fg::RED << ansi::BLOCK;
            } else if (row == player2_pos[0] && col == player2_pos[1]) {
                std::cout << ansi::fg::BLUE << ansi::BLOCK;
            } else {
                std::cout << ' ';
            }
        }

        std::cout << '\n';
    }

    std::cout << ansi::RESET << std::flush;
}

