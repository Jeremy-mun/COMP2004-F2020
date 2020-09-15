#include <stdio.h>

int main() {
  char mystring[10];
  FILE* fd = fopen("inputfile.txt", "rw");

  while (fscanf(fd, "%s", mystring) != EOF) {
    printf("String: %s\n", mystring);
  }
  fclose(fd);
}
