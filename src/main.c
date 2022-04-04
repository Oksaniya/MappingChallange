#include "common.h"

t_buff buff;

int main(int argc, char **argv)
{
  t_buff buff;
  FILE *fp;
  FILE *fp2;
  
  argc_check(argc);
  input_name_exe_check(argv[1]);
  output_name_exe_check(argv[2]);

  fp = fopen(argv[1], "r+");
  fp2 = fopen(argv[2], "w");
  if (fp == NULL)
  {
    exit(EXIT_FAILURE);
  }
  
  read_f(fp, &buff, fp2);
  fclose(fp);

  return 0;
}