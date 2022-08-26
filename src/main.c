#include "../inc/common.h"

t_buff buff;

int main(const int argc, const char **argv)
{
  t_buff buff;
  FILE *fp;
  FILE *fp2;
  
  argc_check(argc);
  input_name_exe_check(argv[1]);
  output_name_exe_check(argv[2]);

  fp = fopen((const char *restrict)argv[1], "r+");
  fp2 = fopen((const char *restrict)argv[2], "w");
  if ((fp == NULL) || (fp2 == NULL))
  {
    exit(EXIT_FAILURE);
  }
  
  read_f(fp, &buff, fp2);
  fclose(fp);
  fclose(fp2);

  return 0;
}