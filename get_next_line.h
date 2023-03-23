#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

char  *ft_strjoin(char *s1, char *s2);
int   find(char *str, int c);
int   ft_strlen(char *str);

#endif
