#include <stdio.h>

#include <stdlib.h>

#include <conio.h>

#include <windows.h>

#include <time.h>

int height = 20, width = 20;
int x, y, fruitX, fruitY;
int score = 0, gameEnd = 0, flag = 0;
int tailX[100], tailY[100], piece = 0;

void gotoxy(int r, int c) {
  COORD pos;
  pos.X = c;
  pos.Y = r;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void hideCursor() {
  CONSOLE_CURSOR_INFO c;
  c.bVisible = FALSE;
  c.dwSize = 1;
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), & c);
}

void setup() {
  x = height / 2;
  y = width / 2;
  fruitX = rand() % (height - 2) + 1;
  fruitY = rand() % (width - 2) + 1;
}

void draw() {
  gotoxy(0, 0);

  for (int i = 0; i <= height; i++) {
    for (int j = 0; j <= width; j++) {
      if (i == 0 || i == height || j == 0 || j == width)
        printf("#");
      else if (i == x && j == y)
        printf("O");
      else if (i == fruitX && j == fruitY)
        printf("@");
      else {
        int print = 0;
        for (int k = 0; k < piece; k++) {
          if (tailX[k] == i && tailY[k] == j) {
            printf("o");
            print = 1;
            break;
          }
        }
        if (!print) printf(" ");
      }
    }
    printf("\n");
  }
  printf("Score: %d\n", score);
}

void input() {
  if (kbhit()) {
    char ch = getch();
    if (ch == 'w') flag = 1;
    if (ch == 's') flag = 2;
    if (ch == 'a') flag = 3;
    if (ch == 'd') flag = 4;
    if (ch == 'x') gameEnd = 1;
  }
}

void logic() {
  int prevX = tailX[0], prevY = tailY[0];
  tailX[0] = x;
  tailY[0] = y;

  for (int i = 1; i < piece; i++) {
    int tempX = tailX[i], tempY = tailY[i];
    tailX[i] = prevX;
    tailY[i] = prevY;
    prevX = tempX;
    prevY = tempY;
  }

  if (flag == 1) x--;
  if (flag == 2) x++;
  if (flag == 3) y--;
  if (flag == 4) y++;

  if (x <= 0 || x >= height || y <= 0 || y >= width)
    gameEnd = 1;

  if (x == fruitX && y == fruitY) {
    score += 10;
    fruitX = rand() % (height - 2) + 1;
    fruitY = rand() % (width - 2) + 1;
    piece++;
  }

  for (int i = 0; i < piece; i++) {
    if (tailX[i] == x && tailY[i] == y)
      gameEnd = 1;
  }
}

int main() {
  srand(time(0));
  hideCursor();
  setup();

  while (!gameEnd) {
    draw();
    input();
    logic();
    Sleep(120);
  }

  system("cls");
  printf("GAME OVER\nFinal Score: %d\n", score);
  return 0;
}