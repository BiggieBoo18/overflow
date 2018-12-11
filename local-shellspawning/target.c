#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int   flag=0;
  char  buf[256]={0};
  
  if (argc<=1) {
    return (1);
  }
  printf("%p\n", &buf);
  strcpy(buf, argv[1]);
  if (strcmp(buf, "p@ssw0rd!")==0) {
    flag = 1;
  }
  if (flag) {
    puts("correct!");
  } else {
    puts("wrong!");
  }

  return (0);
}
