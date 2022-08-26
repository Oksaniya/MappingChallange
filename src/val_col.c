#include "../inc/common.h"

void id_frame(char **line, t_buff *buff, FILE *fp2)
{
    char **values;
    int i;
    int n;

    n = buff->iterator_FrameDropCnt15;
    i = buff->iterator_FrameDropCnt78;

    values = ft_strsplit(*line, '\n');
    values = ft_strsplit(*line, '\r');
    values = ft_strsplit(*line, ',');
    
    fputs(values[0], fp2);
    fputs(",", fp2);
    fputs(values[1], fp2);
    fputs(",", fp2);
    fputs(values[2], fp2);
    fputs(",", fp2);

    if ((atoi((const char *)values[0]) == POSITION))
    {
        if (atoi((const char *)values[1]) == n)
        {
            n++;
            buff->iterator_FrameDropCnt15 = n;
        }
        else if (atoi((const char *)values[1]) != n)
        {
            n = atoi((const char *)values[1]);
            n++;
            buff->iterator_FrameDropCnt15 = n;
            buff->FrameDropCnt15++;

        }
    }
    else if (atoi((const char *)values[0]) == VELOCITY)
    {
        if (atoi((const char *)values[1]) == i)
        {
            i++;
            buff->iterator_FrameDropCnt78 = i;
        }
        else if (atoi((const char *)values[1]) != i)
        {
            i = atoi((const char *)values[1]);
            i++;
            buff->iterator_FrameDropCnt78 = i;
            buff->FrameDropCnt78++;
        }
    }
}

void TimeoutOK_cnt(char **line, t_buff *buff)
{
    char **values;
    int t;
    int f;

    t = buff->iterator_TimeoutOK_position;
    f = buff->iterator_TimeoutOK_velocity;

    values = ft_strsplit(*line, '\n');
    values = ft_strsplit(*line, '\r');
    values = ft_strsplit(*line, ',');

    if ((atoi((const char *)values[0]) == POSITION))
    {
        if ((atoi((const char *)values[2]) >= (t - TIMESTAMP_INTERVAL_POS_DEVIATION)) && 
        (atoi((const char *)values[2]) <= (t + TIMESTAMP_INTERVAL_POS_DEVIATION)))
        {
            t = (t + TIMESTAMP_INTERVAL_POSITION);
            buff->iterator_TimeoutOK_position = t;
            buff->TimeoutOK = 1;
        }
        else 
        {
            t = atoi((const char *)values[2]);
            t = (t + TIMESTAMP_INTERVAL_POSITION);
            buff->iterator_TimeoutOK_position = t;
            buff->TimeoutOK = 0;
        }
    }
    else if (atoi((const char *)values[0]) == VELOCITY)
    {
        if ((atoi((const char *)values[2]) >= (f - TIMESTAMP_INTERVAL_VEL_DEVIATION)) && 
        (atoi((const char *)values[2]) <= (f + TIMESTAMP_INTERVAL_VEL_DEVIATION)))
        {
            f = (f + TIMESTAMP_INTERVAL_VELOCITY);
            buff->iterator_TimeoutOK_velocity = f;
            buff->TimeoutOK = 1;
        }
        else 
        {
            f = atoi((const char *)values[2]);
            f = (f + TIMESTAMP_INTERVAL_VELOCITY);
            buff->iterator_TimeoutOK_velocity = f;
            buff->TimeoutOK = 0;
        }
    }
}

void ChecksumOK_calc(char **line, t_buff *buff)
{
    char **values;
    char **fragments;
    int i;
    unsigned char a;

    a = 'a';
    i = 0;
    values = ft_strsplit(*line, '\n');
    values = ft_strsplit(*line, '\r');
    values = ft_strsplit(*line, ',');

    fragments = (char **)malloc(strlen(values[3]));

    if (fragments == NULL)
    {
        exit(1) ;
    }
    while (i < PAYLOAD_FRAGMENTS_COMPLEMENT)
    {
        fragments[i] = ft_strndup((const char *)values[3], 2);
        values[3] += 2;
        i++;
    }
    
    a = complement_cnt(fragments);

    if (a == (int)strtol(values[4], NULL, 16))
    {
        buff->ChecksumOK = 1;
    }

    else if (a != (int)strtol(values[4], NULL, 16))
    {
        buff->ChecksumOK = 0;

    }
}

unsigned char complement_cnt(char **fragments)
{
    int i;
    unsigned char a;    

    i = 0;
    a = 0;

    while (i < PAYLOAD_FRAGMENTS_COMPLEMENT)
    {
        a += strtoul((const char *)fragments[i], NULL, 16);
        i++;
    }
    a = ~a;
    a++;
    return a;
}

void vel_pos(char **line, t_buff *buff)
{
    char **values;
    char **fr;
    unsigned short xpayload;
    unsigned short ypayload;
    float fxp;
    float fyp;
    int i;

    xpayload = 0;
    ypayload = 0;
    i = 0;
    fxp = 0,0;
    fyp = 0,0;

    values = ft_strsplit(*line, '\n');
    values = ft_strsplit(*line, '\r');
    values = ft_strsplit(*line, ',');

    fr = (char **)malloc(strlen(values[3]));

    if (fr == NULL)
    {
        exit(1) ;
    }

    while (i < PAYLOAD_FRAGMENTS_POS_VEL)
    {
        fr[i] = ft_strndup((const char *)values[3], 4);
        values[3] += 4;
        i++;
    }

    xpayload = (unsigned short)strtol(fr[0], NULL, 16);
    fxp = (float)xpayload;
    
    ypayload = (unsigned short)strtol(fr[1], NULL, 16);
    fyp = (float)ypayload;

    if ((atoi((const char *)values[0]) == POSITION))
    {
        buff->PositionX = (fxp / 100);
        buff->PositionY = ((fyp + (-32767)) / 1000);
    }
    else if (atoi((const char *)values[0]) == VELOCITY)
    {
        
        buff->VelocityX = ((fxp + (-32767)) / 1000);
        buff->VelocityY = ((fyp + (-32767)) / 1000);
    }
}

