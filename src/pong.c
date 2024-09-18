#include <stdio.h>
void screen(int x, int y, int shir, int vis, int xrocket1, int yrocket1, int xrocket2, int yrocket2, int left,
            int right);
int change_direction_x(int x, int vertic, int vis);
int change_direction_y(int x, int y, int horiz, int shir, int xrocket1,
           int xrocket2);
int move_ball_by_x(int x, int vertic);
int move_ball_by_y(int y, int horiz);
int defaultpos(int y, int width);

void check_results(int score1, int score2);

int get_new_coordinate(int y, char direction);

int main() {
    int width = 80, height = 25;
    int x_circle_pos = 10, y_circle_pos = 10;
    int xrocket1 = 1, yrocket1 = 9;
    int xrocket2 = width - 2, yrocket2 = 9;
    int score1 = 0, score2 = 0;

    int v = 0, h = 0;
    char c;
    char a;
    screen(y_circle_pos, x_circle_pos, width, height, xrocket1, yrocket1, xrocket2, yrocket2, score1, score2);

    char turn = 'l';

    while (score1 != 21 && score2 != 21) {
        if (y_circle_pos == 1)
            score1++;
        else if (y_circle_pos == width - 2)
            score2++;

        scanf("%c%c", &a, &c);
        printf("input is:%c%c, turn is:%c\n", a, c, turn);

        if ((yrocket1 == 2 && a == 'a') || (yrocket2 == 2 && a == 'k')) {
            printf("you can't move\n");
        } else if ((yrocket1 == 22 && a == 'z') || (yrocket2 == 22 && a == 'm')) {
            printf("you can't move\n");
        } else {
            if (a == ' ') {
                if (turn == 'l') {
                    printf("skip move r\n");
                    turn = 'r';
                } else {
                    printf("skip move l\n");
                    turn = 'l';
                }
                v = change_direction_x(x_circle_pos, v, height);
                h = change_direction_y(x_circle_pos, y_circle_pos, h, width, yrocket1, yrocket2);
                x_circle_pos = move_ball_by_x(x_circle_pos, v);
                y_circle_pos = move_ball_by_y(y_circle_pos, h);
                y_circle_pos = defaultpos(y_circle_pos, width);
            } else {
                if (turn == 'l') {
                    if (a == 'k' || a == 'm') {
                        printf("not your turn\n");
                    } else {
                        if (a == 'a') {
                            printf("go top\n");
                            yrocket1 = get_new_coordinate(yrocket1, 't');
                        }
                        if (a == 'z') {
                            printf("go bottom\n");
                            yrocket1 = get_new_coordinate(yrocket1, 'b');
                        }
                        v = change_direction_x(x_circle_pos, v, height);
                        h = change_direction_y(x_circle_pos, y_circle_pos, h, width, yrocket1, yrocket2);
                        x_circle_pos = move_ball_by_x(x_circle_pos, v);
                        y_circle_pos = move_ball_by_y(y_circle_pos, h);
                        y_circle_pos = defaultpos(y_circle_pos, width);
                        turn = 'r';
                    }
                } else if (turn == 'r') {
                    if (a == 'a' || a == 'z') {
                        printf("not your turn\n");
                    } else {
                        if (a == 'k') {
                            printf("go top\n");
                            yrocket2 = get_new_coordinate(yrocket2, 't');
                        }
                        if (a == 'm') {
                            printf("go bottom\n");
                            yrocket2 = get_new_coordinate(yrocket2, 'b');
                        }
                        v = change_direction_x(x_circle_pos, v, height);
                        h = change_direction_y(x_circle_pos, y_circle_pos, h, width, yrocket1, yrocket2);
                        x_circle_pos = move_ball_by_x(x_circle_pos, v);
                        y_circle_pos = move_ball_by_y(y_circle_pos, h);
                        y_circle_pos = defaultpos(y_circle_pos, width);
                        turn = 'l';
                    }
                }
            }
        }
        screen(y_circle_pos, x_circle_pos, width, height, xrocket1, yrocket1, xrocket2, yrocket2, score1, score2);
    }
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
                printf("%d", left);
                j++;
            }
            if (i == 0 && j == 44) {
                printf("%d", right);
                j++;
            }

            if (i == 1 || i == vis || ((j == 0 || j == shir - 1) && i != 0))
                printf("#");
            else {
                if ((i >= yrocket1 && i <= yrocket1 + 2 && j == xrocket1) ||
                    (i >= yrocket2 && i <= yrocket2 + 2 && j == xrocket2))
                    printf("|");
                else if (i == y && j == x)
                    printf("*");
                else if (j == 40)
                    printf("-");
                else
                    printf(" ");
            }
        }
        printf("\n");
    }
}

int change_direction_x(int x, int vertic, int vis) {
    if (x == 1 && vertic == 0)
        vertic = 1;
    else if (vis - x == 1 && vertic == 1)
        vertic = 0;
    return vertic;
}

int change_direction_y(int x, int y, int horiz, int shir, int xrocket1, int xrocket2) {
    if (y == 2 && horiz == 1) {
        if (x >= xrocket1 && x <= xrocket1 + 2) horiz = 0;
    }
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

int defaultpos(int y, int width) {
    if (y <= 0 || y >= width)
        return width / 2;
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
