#include <stdio.h>

#define MIN(a, b) ((a<b)?a:b)
#define MAX(a, b) ((a>b)?a:b)

#define PUZZLE 2

int is_possible(int a, int b, int c) {
  printf("a=%d, b=%d, c=%d\n", a,b, c);
  return (a + b > c) && (b + c > a) && (c + a > b);
}

int main() {
  FILE *fp;
  int a, b, c;
  int num_possible = 0;
  fp = fopen("input/3.txt", "r");
  if (fp) {
    if (PUZZLE == 1) {
      while (fscanf(fp, "%d %d %d", &a, &b, &c) != EOF) {
        if (is_possible(a, b, c)) {
          num_possible++;
        }
      }
    } else {
      while (1) {
        int a2, b2, c2, a3, b3, c3;
        int rv;
        // assuming good input, since there's only one input file possible
        rv = fscanf(fp, "%d %d %d", &a, &a2, &a3);
        if (rv == EOF) {
          break;
        }
        fscanf(fp, "%d %d %d", &b, &b2, &b3);
        rv = fscanf(fp, "%d %d %d", &c, &c2, &c3);

        num_possible += is_possible(a, b, c);
        num_possible += is_possible(a2, b2, c2);
        num_possible += is_possible(a3, b3, c3);
        if (rv == EOF) {
          break;
        }
      }
    }
    fclose(fp);
    printf("Number of possible triangles: %d", num_possible);
  } else {
    printf("Could not open file input/3.txt!");
    return -1;
  }
  return 0;
}
