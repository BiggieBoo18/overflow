#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int   flag=1;
  char  buf[256]={0};
  
  if (argc<=1) {
    return (1);
  }
  printf("%p\n", &buf);
  strcpy(buf, argv[1]);
  flag = strcmp(buf, "p@ssw0rd!");
  if (flag==0) {
    puts("correct!");
  } else {
    puts("wrong!");
  }

  return (0);
}
