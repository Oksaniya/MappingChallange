#include "../inc/common.h"

char *ft_strnew(size_t size)
{
    char *str;
    str = (char *)malloc(size);

    if (str == NULL)
    {
        return NULL;
    }

    bzero((void *)str, size);
    return str;
}

char **ft_strsplit(char const *s, char c)
{
    int i;
    int wrdlen;
    int wordcounter;
    int counter;
    int rescounter;
    char **res;

    i = 0;
    rescounter = 0;
    wordcounter = 0;

    while (s[i] != '\0')
    {
        while (s[i] == c)
        {
            i++;
        }
        if (s[i] != c && (i == 0 || s[i - 1] == c))
        {
            wordcounter++;
        }
        i++;
    }
    i = 0;
    res = (char **)malloc(sizeof(char *) * (wordcounter + 1));

    if (res == NULL)
    {
        return NULL;
    }

    res[wordcounter] = 0;

    while (rescounter < wordcounter)
    {
        while (s[i] == c)
        {
            i++;
        }
        wrdlen = 0;
        while (s[i + wrdlen] != c && s[i + wrdlen] != '\0')
        {
            wrdlen++;
        }
        res[rescounter] = ft_strnew(wrdlen + 1);
        counter = 0;
        while (s[i] != c && s[i] != '\0')
        {
            res[rescounter][counter] = s[i];
            i++;
            counter++;
        }
        rescounter++;
    }
    return res;
}

//int big_to_small_endian()