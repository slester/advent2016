#include <stdio.h>
#include <string.h>

#define MIN(a, b) ((a<b)?a:b)
#define MAX(a, b) ((a>b)?a:b)
// Pt. 1 "SQUARE" = 3x3 grid
// Pt. 2 "DIAMOND" = 5x5 grid (diamond shape)
#define PATTERN "DIAMOND"
#define ROWS 5
#define COLS 5

void make_keypad(int keypad[ROWS][COLS]) {
  if (PATTERN == "SQUARE") {
    keypad[0][0] = 1;
    keypad[1][0] = 2;
    keypad[2][0] = 3;
    keypad[0][1] = 4;
    keypad[1][1] = 5;
    keypad[2][1] = 6;
    keypad[0][2] = 7;
    keypad[1][2] = 8;
    keypad[2][2] = 9;
  } else {
    keypad[0][0] = 0;
    keypad[1][0] = 0;
    keypad[2][0] = 1;
    keypad[3][0] = 0;
    keypad[4][0] = 0;
    keypad[0][1] = 0;
    keypad[1][1] = 2;
    keypad[2][1] = 3;
    keypad[3][1] = 4;
    keypad[4][1] = 0;
    keypad[0][2] = 5;
    keypad[1][2] = 6;
    keypad[2][2] = 7;
    keypad[3][2] = 8;
    keypad[4][2] = 9;
    keypad[0][3] = 0;
    keypad[1][3] = 10;
    keypad[2][3] = 11;
    keypad[3][3] = 12;
    keypad[4][3] = 0;
    keypad[0][4] = 0;
    keypad[1][4] = 0;
    keypad[2][4] = 13;
    keypad[3][4] = 0;
    keypad[4][4] = 0;
  }
}

int move_x_neg(int keypad[ROWS][COLS], int x, int y) {
  int new_x = MAX(0, x - 1);
  if ((x != new_x) && (keypad[new_x][y] != 0)) {
    return new_x;
  } else {
    return x;
  }
}

int move_x_pos(int keypad[ROWS][COLS], int x, int y) {
  int new_x = MIN(ROWS - 1, x + 1);
  if ((x != new_x) && (keypad[new_x][y] != 0)) {
    return new_x;
  } else {
    return x;
  }
}

int move_y_neg(int keypad[ROWS][COLS], int x, int y) {
  int new_y = MAX(0, y - 1);
  if ((y != new_y) && (keypad[x][new_y] != 0)) {
    return new_y;
  } else {
    return y;
  }
}

int move_y_pos(int keypad[ROWS][COLS], int x, int y) {
  int new_y = MIN(ROWS - 1, y + 1);
  if ((y != new_y) && (keypad[x][new_y] != 0)) {
    return new_y;
  } else {
    return y;
  }
}

int main() {
  FILE *fp;
  char str[2048];
  int code[5]; // the code is 5 digits long for my input
  int x;
  int y;
  int keypad[ROWS][COLS];
  make_keypad(keypad);
  if (PATTERN == "SQUARE") {
    x = 1;
    y = 1;
  } else {
    x = 0;
    y = 2;
  }
  int line = 0;
  fp = fopen("input/2.txt", "r");
  if (fp) {
    while (fscanf(fp, "%s", str) != EOF) {
      for (int i = 0; i < strlen(str); i++) {
        switch (str[i]) {
          case 'U':
            y = move_y_neg(keypad, x, y);
            break;
          case 'L':
            x = move_x_neg(keypad, x, y);
            break;
          case 'D':
            y = move_y_pos(keypad, x, y);
            break;
          case 'R':
            x = move_x_pos(keypad, x, y);
            break;
        }
      }
      code[line] = keypad[x][y];
      line++;
    }
    for (int i = 0; i < line; i++) {
      printf("%X", code[i]);
    }
    fclose(fp);
  } else {
    printf("Could not open file input/2.txt!");
  }
}
