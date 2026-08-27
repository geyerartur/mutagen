#include <iostream>
#include <string>



int main() {
    // Enter alternate screen buffer, clear it, move cursor home,
    // and hide the cursor.
    std::cout << "\033[?1049h"
              << "\033[2J"
              << "\033[H"
              << "\033[?25l"
              << std::flush;

    std::cout << "Full-screen terminal application\n";
    std::cout << "Press Enter to exit..." << std::flush;

    std::string input;
    std::getline(std::cin, input);

    // Show the cursor, leave alternate screen buffer,
    // and restore the original terminal contents.
    std::cout << "\033[?25h"
              << "\033[?1049l"
              << std::flush;

    return 0;
}
