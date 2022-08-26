#include "../inc/common.h"

void read_f(FILE *fp, t_buff *buff, FILE *fp2)
{

    //char    buf[64];
	char	*line;
    ssize_t	read;

    read = 0;
    buff->iterator_FrameDropCnt78 = 0;
    buff->iterator_FrameDropCnt15 = 0;
    buff->iterator_TimeoutOK_position = 0;
    buff->iterator_TimeoutOK_velocity = 0;
    buff->FrameDropCnt15 = 0;
    buff->FrameDropCnt78 = 0;

  //  ft_bzero(line, strlen((const char *)line));
    //read = getline(line, &len, fp);
    line = ft_strnew(64);
	line = fgets(line, 64, fp);
    
	name_col_check(&line);
    write_name(fp2);

    while (line) 
    {
        //read = getline(line, &len, fp);
		line = fgets(line, 64, fp);
        if (line)
        {
            id_frame(&line, buff, fp2);
            TimeoutOK_cnt(&line, buff);
            ChecksumOK_calc(&line, buff);
            vel_pos(&line, buff);
            write_pos_vel(buff, fp2, &line);
            write_check_time(buff,fp2);
            write_framedrop(buff, fp2, &line);

        }
    }
}

void write_name(FILE *fp2)
{
    char str[] = "ID,FrameNb,Timestamp,PositionX,PositionY,VelocityX,VelocityY,ChecksumOK,TimeoutOK,FrameDrop\n";
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
        {
            printf("Moja programa wsralas tut");
            exit(1);
        }
        fputs("\n", fp2);
    }

    else if (atoi(values[0]) == VELOCITY)
    {
        ret = fprintf(fp2, "%d", buff->FrameDropCnt78);
        if (ret < 0) 
            exit(1);
        fputs("\n", fp2);
    }
}