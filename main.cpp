#include <locale.h>
#include <ncurses.h>
#include <panel.h>

int main(void)
{
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

    WINDOW *overlay_win = newwin(5, 28, 0, 0);

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

        /*
         * Draw the underlying screen.
         */
        if (rows > 0 && cols > 4) {
            int center_row = rows / 2;
            int center_col = cols / 2;

            if (has_colors())
                attron(COLOR_PAIR(1));

            mvaddstr(center_row, center_col - 2, "█");

            if (has_colors()) {
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
            }

            mvaddstr(center_row, center_col + 1, "█");

            if (has_colors())
                attroff(COLOR_PAIR(2));
        }

        /*
         * Draw the overlay window.
         */
        werase(overlay_win);

        if (has_colors())
            wattron(overlay_win, COLOR_PAIR(3));

        box(overlay_win, 0, 0);

        mvwprintw(overlay_win, 1, 2, "Terminal overlay");
        mvwprintw(overlay_win, 2, 2, "Rows: %d", rows);
        mvwprintw(overlay_win, 3, 2, "Cols: %d", cols);

        if (has_colors())
            wattroff(overlay_win, COLOR_PAIR(3));

        /*
         * Tell panels to update their stacking.
         */
        update_panels();

        /*
         * doupdate() actually renders everything.
         */
        doupdate();

        int ch = getch();

        if (ch == 'q' || ch == 'Q')
            break;

        if (ch == KEY_RESIZE) {
            /*
             * If desired, reposition/resize the panel here.
             */
            wclear(overlay_win);
        }
    }

    del_panel(overlay_panel);
    delwin(overlay_win);

    endwin();

    return 0;
}

