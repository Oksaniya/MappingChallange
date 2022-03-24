#include "../inc/common.h"

t_buff buff;

int main(int argc, char **argv)
{
  t_buff buff;
  int fd;
  char *lineptr;
  FILE *fp;
  FILE *fp2;
  mode_t mode;

  mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  
  argc_check(argc);
  input_name_exe_check(argv[1]);
  output_name_exe_check(argv[2]);

  fp = fopen(argv[1], "r+");
  fd = creat(argv[2], mode);
  fp2 = fopen(argv[2], "r+");
  if (fp == NULL)
  {
    exit(EXIT_FAILURE);
  }
  
  read_f(&lineptr, fp, &buff, fp2);
  fclose(fp);

  return 0;
}