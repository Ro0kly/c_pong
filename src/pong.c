#include <stdio.h>

void screen(int x, int y, int shir, int vis, int xrocket1, int yrocket1, int xrocket2, int yrocket2, int left,
            int right);                  //вывод
int smenax(int x, int vertic, int vis);  //смена направления мяча вниз-вверх
int smenay(int x, int y, int horiz, int shir, int xrocket1,
           int xrocket2);          //смена направления мяча вправо-влево
int movesharx(int x, int vertic);  // движение мяча
int moveshary(int y, int horiz);
int defaultpos(int y, int shirina);

int proverka(int x, int left, int right, int shirina);
void itogimatcha(int score1, int score2);

int get_new_coordinate(int y, char direction);

int main() {
    int shirina = 80, visota = 25;             //параметры поля
    int xshar = 10, yshar = 10;                // позиция мяча
    int xrocket1 = 1, yrocket1 = 9;            // позиция первой ракетки
    int xrocket2 = shirina - 2, yrocket2 = 9;  // позиция второй ракетки
    int score1 = 0, score2 = 0;

    int v = 0, h = 0;  // флажки направлений
    char c;
    char a;
    char turn = 'l';
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

int moveshary(int y, int horiz) {
    if (horiz == 0)
        y = y + 1;
    else
        y = y - 1;
    return y;
}