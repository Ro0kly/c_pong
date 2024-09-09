#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
void screen(int x, int y, int shir, int vis, int xrocket1, int yrocket1, int xrocket2, int yrocket2, int left,
            int right);                  //вывод
int change_direction_x(int x, int vertic, int vis);  //смена направления мяча вниз-вверх
int change_direction_y(int x, int y, int horiz, int shir, int xrocket1,
           int xrocket2);          //смена направления мяча вправо-влево
int move_ball_by_x(int x, int vertic);  // движение мяча
int move_ball_by_y(int y, int horiz);
int defaultpos(int y, int shirina);

void check_results(int score1, int score2);

int get_new_coordinate(int y, char direction);

int main() {
    initscr();
    nodelay(stdscr, true);
    int shirina = 80, visota = 25;             //параметры поля
    int xshar = 10, yshar = 10;                // позиция мяча
    int xrocket1 = 1, yrocket1 = 9;            // позиция первой ракетки
    int xrocket2 = shirina - 2, yrocket2 = 9;  // позиция второй ракетки
    int score1 = 0, score2 = 0;

    int v = 0, h = 0;  // флажки направлений
    // char c;

    screen(yshar, xshar, shirina, visota, xrocket1, yrocket1, xrocket2, yrocket2, score1, score2);

    char turn = 'l';

    while (score1 != 21 && score2 != 21) {
        if (yshar == 1)
            score2++;
        else if (yshar == shirina - 2)
            score1++;
        // scanw("%c", &a);
        char a = getch();
        printw("input is:%c, turn is:%c\n", a, turn);

        if ((yrocket1 == 2 && a == 'a') || (yrocket2 == 2 && a == 'k')) {
            printw("you can't move\n");
        } else if ((yrocket1 == 22 && a == 'z') || (yrocket2 == 22 && a == 'm')) {
            printw("you can't move\n");
        } else {
            if (a == ' ') {
                if (turn == 'l') {
                    printw("skip move r\n");
                    turn = 'r';
                } else {
                    printw("skip move l\n");
                    turn = 'l';
                }
                v = change_direction_x(xshar, v, visota);
                h = change_direction_y(xshar, yshar, h, shirina, yrocket1, yrocket2);
                xshar = move_ball_by_x(xshar, v);
                yshar = move_ball_by_y(yshar, h);
                yshar = defaultpos(yshar, shirina);
            } else {
                if (turn == 'l') {
                    if (a == 'k' || a == 'm') {
                        printw("not your turn\n");
                    } else {
                        if (a == 'a') {
                            printw("go top\n");
                            yrocket1 = get_new_coordinate(yrocket1, 't');
                        }
                        if (a == 'z') {
                            printw("go bottom\n");
                            yrocket1 = get_new_coordinate(yrocket1, 'b');
                        }
                        v = change_direction_x(xshar, v, visota);
                        h = change_direction_y(xshar, yshar, h, shirina, yrocket1, yrocket2);
                        xshar = move_ball_by_x(xshar, v);
                        yshar = move_ball_by_y(yshar, h);
                        yshar = defaultpos(yshar, shirina);
                        turn = 'r';
                    }
                } else if (turn == 'r') {
                    if (a == 'a' || a == 'z') {
                        printw("not your turn\n");
                    } else {
                        if (a == 'k') {
                            printw("go top\n");
                            yrocket2 = get_new_coordinate(yrocket2, 't');
                        }
                        if (a == 'm') {
                            printw("go bottom\n");
                            yrocket2 = get_new_coordinate(yrocket2, 'b');
                        }
                        v = change_direction_x(xshar, v, visota);
                        h = change_direction_y(xshar, yshar, h, shirina, yrocket1, yrocket2);
                        xshar = move_ball_by_x(xshar, v);
                        yshar = move_ball_by_y(yshar, h);
                        yshar = defaultpos(yshar, shirina);
                        turn = 'l';
                    }
                }
            }
        }
        clear();
        screen(yshar, xshar, shirina, visota, xrocket1, yrocket1, xrocket2, yrocket2, score1, score2);
        usleep(46000);
    }
    endwin();
    check_results(score1, score2);
}

int get_new_coordinate(int y, char direction) {
    int _y = y;
    if (direction == 't') {
        _y -= 1;
    } else {
        _y += 1;
    }
    return _y;
}

void screen(int x, int y, int shir, int vis, int xrocket1, int yrocket1, int xrocket2, int yrocket2, int left,
            int right) {
    for (int i = 0; i <= vis; i++) {
        for (int j = 0; j < shir; j++) {
            if (i == 0 && j == 36) {
                printw("%d", left);
                j++;
            }
            if (i == 0 && j == 44) {
                printw("%d", right);
                j++;
            }

            if (i == 1 || i == vis || ((j == 0 || j == shir - 1) && i != 0))
                printw("#");
            else {
                if ((i >= yrocket1 && i <= yrocket1 + 2 && j == xrocket1) ||
                    (i >= yrocket2 && i <= yrocket2 + 2 && j == xrocket2))
                    printw("|");
                else if (i == y && j == x)
                    printw("*");
                else if (j == 40)
                    printw("-");
                else
                    printw(" ");
            }
        }
        printw("\n");
    }
}

int change_direction_x(int x, int vertic, int vis) {
    // vertic 0 - vverh 1 - vniz
    if (x == 1 && vertic == 0)
        vertic = 1;
    else if (vis - x == 1 && vertic == 1)
        vertic = 0;
    return vertic;
}

int change_direction_y(int x, int y, int horiz, int shir, int xrocket1, int xrocket2) {
    // horiz 0 - vpravo 1 - vlevo
    if (y == 2 && horiz == 1) {
        if (x >= xrocket1 && x <= xrocket1 + 2) horiz = 0;
    }
    //  else
    else if (shir - y == 3 && horiz == 0) {
        if (x >= xrocket2 && x <= xrocket2 + 2) horiz = 1;
    }
    return horiz;
}

int move_ball_by_x(int x, int vertic) {
    if (vertic == 0)
        x = x - 1;
    else
        x = x + 1;
    return x;
}

int move_ball_by_y(int y, int horiz) {
    if (horiz == 0)
        y = y + 1;
    else
        y = y - 1;
    return y;
}

int defaultpos(int y, int shirina) {
    if (y <= 0 || y >= shirina)
        return shirina / 2;
    else
        return y;
}

void check_results(int score1, int score2) {
    if (score1 > score2)
        printf("Победил левый игрок");
    else if (score2 > score1)
        printf("Победил правый игрок");
    else
        printf("Ничья");
}
