#include "../inc/common.h"

void read_f(char **line, FILE *fp, t_buff *buff, FILE *fp2)
{

    size_t len = 0;
    ssize_t read;

    read = 0;
    buff->i = 0;
    buff->n = 0;
    buff->t = 0;
    buff->f = 0;
    buff->h = 0;
    buff->FrameDropCnt15 = 0;
    buff->FrameDropCnt78 = 0;

    bzero(line, strlen((const char *)line));
    read = getline(line, &len, fp);
    name_col_check(line);
    write_name(fp2);

    while (read != -1) 
    {
        read = getline(line, &len, fp);
        if (read != -1)
        {
            id_frame(line, buff, fp2);
            TimeoutOK_cnt(line, buff);
            ChecksumOK_calc(line, buff);
            vel_pos(line, buff);
            write_pos_vel(buff, fp2, line);
            write_check_time(buff,fp2);
            write_framedrop(buff, fp2, line);

        }
    }
}

void write_name(FILE *fp2)
{
    char str[] = "ID, FrameNb, Timestamp, PositionX, PositionY, VelocityX, VelocityY, ChecksumOK, TimeoutOK, FrameDrop\r\n";
    fputs(str, fp2);
}

void write_pos_vel(t_buff *buff, FILE *fp2, char **line)
{
    int ret;
    char **values;

    ret = 0;

    values = ft_strsplit(*line, '\n');
    values = ft_strsplit(*line, '\r');
    values = ft_strsplit(*line, ',');

    if (atoi(values[0]) == POSITION)
    {
        ret = fprintf(fp2, "%f", buff->PositionX);
        fputs(",", fp2);
        if (ret < 0) 
            exit(1);
        ret = fprintf(fp2, "%f", buff->PositionY);
        if (ret < 0) 
            exit(1);
        fputs(",", fp2);
        fputs("0,0,", fp2);
    }

    else if (atoi(values[0]) == VELOCITY)
    {
        fputs("0,0,", fp2);
        ret = fprintf(fp2, "%f", buff->VelocityX);
        fputs(",", fp2);
        if (ret < 0) 
            exit(1);
        ret = fprintf(fp2, "%f", buff->VelocityY);
        fputs(",", fp2);
        if (ret < 0) 
            exit(1); 
    }
}

void write_check_time(t_buff *buff, FILE *fp2)
{
    int ret;

    ret = 0;

    ret = fprintf(fp2, "%d", buff->ChecksumOK);
    fputs(",", fp2);
    if (ret < 0) 
    exit(1);
    ret = fprintf(fp2, "%d", buff->TimeoutOK);
    fputs(",", fp2);
    if (ret < 0) 
    exit(1); 
}

void write_framedrop(t_buff *buff, FILE *fp2, char **line)
{
    int ret;
    char **values;

    ret = 0;

    values = ft_strsplit(*line, '\n');
    values = ft_strsplit(*line, '\r');
    values = ft_strsplit(*line, ',');

    if (atoi(values[0]) == POSITION)
    {
        ret = fprintf(fp2, "%d", buff->FrameDropCnt15);
        if (ret < 0) 
            exit(1);
        fputs("\r\n", fp2);
    }

    else if (atoi(values[0]) == VELOCITY)
    {
        ret = fprintf(fp2, "%d", buff->FrameDropCnt78);
        if (ret < 0) 
            exit(1);
        fputs("\r\n", fp2);
    }
}