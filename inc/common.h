#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define POSITION 15
#define VELOCITY 78
#define TIMESTAMP_INTERVAL_POSITION 25
#define TIMESTAMP_INTERVAL_POS_DEVIATION 2
#define TIMESTAMP_INTERVAL_VELOCITY 50
#define TIMESTAMP_INTERVAL_VEL_DEVIATION 3
#define PAYLOAD_FRAGMENTS_COMPLEMENT 4
#define PAYLOAD_FRAGMENTS_POS_VEL 2


typedef struct          s_buff
{
    int                 iterator_FrameDropCnt78;
    int                 iterator_FrameDropCnt15;
    int                 iterator_TimeoutOK_position;
    int                 iterator_TimeoutOK_velocity;
    int                 a;
    int                 ID;
    int                 FrameNB;
    int                 Timestamp;
    float               PositionX;
    float               PositionY;
    float               VelocityX;
    float               VelocityY;
    bool                ChecksumOK;
    bool                TimeoutOK;
    int                 FrameDropCnt15;
    int                 FrameDropCnt78;
}                       t_buff;

void argc_check(const int argc);
void input_name_exe_check(const char *argv);
void output_name_exe_check(const char *argv);
void ft_bzero(void *ptr, size_t size);
char **ft_strsplit(char const *s, char c);
char *ft_strndup(const char *str, size_t n);
char *ft_strnew(size_t size);
void read_f(FILE *fp, t_buff *buff, FILE *fp2);
void name_col_check(char **line);
void id_frame(char **line, t_buff *buff, FILE *fp2);
void TimeoutOK_cnt(char **line, t_buff *buff);
void ChecksumOK_calc(char **line, t_buff *buff);
unsigned char complement_cnt(char **fragments);
void vel_pos(char **line, t_buff *buff);
void write_name(FILE *fp2);
void write_pos_vel(t_buff *buff, FILE *fp2, char **line);
void write_check_time(t_buff *buff, FILE *fp2);
void write_framedrop(t_buff *buff, FILE *fp2, char **line);

#endif