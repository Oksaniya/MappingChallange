#include "common.h"

void argc_check(int argc)
{
    if (argc != 3)
    {
        printf("Help information how to use a program (you shpuld enter three arguments: log_decoder.exe input_log.csv output_log.csv. Than the program will work properly)\n");
        exit(1);
    }
}

void input_name_exe_check(char *argv)
{
    int i;
    int c;
    char **words;
    const char example1[] = "input_log";
    const char example2[] = "csv";

    i = 0;
    c = 0;

    //words = ((char *)malloc(sizeof(char) * strlen(argv)));
    //bzero((void *)words, strlen(argv));

    words = ft_strsplit(argv, '.');

    while (words[0][c] != '\0')
    {
        c++;
    }
    if (c != 9)
    {
        printf("\nThe input file has incorrect name\n");
        exit(1);
    }
    
    i = strncmp((const char *)words[0],example1, c);
    
    if (i != 0)
    {
        printf("\nThe input file name is incorrect\n");
        exit(1);
    }
    i = 0;
    c = 0;

    while (words[1][c] != '\0')
    {
        c++;
    }
    if (c != 3)
    {
        printf("\nThe input file name should have a .csv format\n");
        exit(1);
    }

    i = strncmp((const char *)words[1], example2, c);
    
    if (i != 0)
    {
        printf("\nThe input file name should have a .csv format\n");
        exit(1);
    }
}

void output_name_exe_check(char *argv)
{
    int i;
    int c;
    char **words;
    const char example1[] = "output_log";
    const char example2[] = "csv";

    i = 0;
    c = 0;

    words = ft_strsplit(argv, '.');

    while (words[0][c] != '\0')
    {
        c++;
    }
    if (c != 10)
    {
        printf("\nThe output file has incorrect name\n");
        exit(1);
    }
    
    i = strncmp((const char *)words[0],example1, c);
    
    if (i != 0)
    {
        printf("\nThe output file name is incorrect\n");
        exit(1);
    }
    i = 0;
    c = 0;

    while (words[1][c] != '\0')
    {
        c++;
    }
    if (c != 3)
    {
        printf("\nThe output file name should have a .csv format\n");
        exit(1);
    }

    i = strncmp((const char *)words[1], example2, c);
    
    if (i != 0)
    {
        printf("\nThe output file name should have a .csv format\n");
        exit(1);
    }
}




void name_col_check(char **line)
{
    int i;
    int c;
    char **names;
    const char ID[] = "ID";
    const char FrameNb[] = "FrameNb";
    const char Timestamp[] = "Timestamp";
    const char Payload[] = "Payload";
    const char Checksum[] = "Checksum\r\n";

    i = 0;
    c = 0;

    names = ft_strsplit(*line, ',');

    while (names[c])
    {
        c++;
    }
    if (c != 5)
    {
        printf("\nThe input file has incorect number of columns\n");
        exit(1);
    }
    c = 0;
    while (names[0][c] != '\0')
    {
        c++;
    }
    if (c != 2)
    {
        printf("\nThe first column should have a name ID\n");
        exit(1);
    }
    
    i = strncmp((const char *)names[0],ID, c);
    
    if (i != 0)
    {
        printf("\nThe first column name is not ID\n");
        exit(1);
    }
    i = 0;
    c = 0;

    while (names[1][c] != '\0')
    {
        c++;
    }
    if (c != 7)
    {
        printf("\nThe second column should have a name FrameNb\n");
        exit(1);
    }
    
    i = strncmp((const char *)names[1], FrameNb, c);
    
    if (i != 0)
    {
        printf("\nThe second column name is not FrameNb\n");
        exit(1);
    }
    i = 0;
    c = 0;

    while (names[2][c] != '\0')
    {
        c++;
    }
    if (c != 9)
    {
        printf("\nThe third column should have a name Timestamp\n");
        exit(1);
    }
    
    i = strncmp((const char *)names[2], Timestamp, c);
    
    if (i != 0)
    {
        printf("\nThe third column name is not Timestamp\n");
        exit(1);
    }
    i = 0;
    c = 0;

    while (names[3][c] != '\0')
    {
        c++;
    }
    if (c != 7)
    {
        printf("\nThe 4'th column should have a name Payload\n");
        exit(1);
    }
    
    i = strncmp((const char *)names[3], Payload, c);
    
    if (i != 0)
    {
        printf("\nThe 4'th column name is not Payload\n");
        exit(1);
    }
    i = 0;
    c = 0;

    while (names[4][c] != '\0')
    {
        c++;
    }
    if (c != 10)
    {
        printf("\nThe 5'th column should have a name Checksum\n");
        exit(1);
    }
    
    i = strncmp((const char *)names[4], Checksum, c);
    
    if (i != 0)
    {
        printf("\nThe 5'th column name is not Checksum\n");
        exit(1);
    }
    i = 0;
    c = 0;
}