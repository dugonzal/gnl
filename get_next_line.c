#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 200
#endif

int find(char *str)
{
  int i = 0;
  while (str[i]){
    if (str[i] == '\n')
      return (1);
    i++;
  }
  return (0);
}

int ft_strlen(char *str)
{
  int i = 0;
  if (!str)
    return (0);
  while (str[i])
    i++;
  return (i);
}

char *ft_strjoin (char *s1, char *s2)
{
  char *tmp;
  int i;
  int j;

  if (!s1 && !s2)
    return (NULL);
  tmp = (char *)malloc(sizeof (char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
  if (!tmp)
    return (NULL);
  i = 0;
  if (s1)
    while (s1[i])
    {
      tmp[i] = s1[i];
      i++;
    }
  j = 0;
  while (s2[j])
    tmp[i++] = s2[j++];
  tmp[i] = '\0';
  free (s1);
  return (tmp);
}

char *read_line(char *str, int fd)
{
  ssize_t rd;
  char *tmp;

  tmp = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
  if (!tmp)
    return (NULL);
  rd = 1;
  while (rd != 0 && !find (tmp)) {
    rd = read (fd, tmp, BUFFER_SIZE);
    if (rd == -1) // error en lectura
    {
      free (tmp);
      return (NULL);
    }
    tmp[rd] = '\0';
    str = ft_strjoin(str, tmp);
  }
  free (tmp);
  return (str);
}

char *get_line (char *str)
{
  char *tmp;
  int i;

  i = 0;
  while (str[i] != 0 && str[i] != '\n')
    i++;
  if (!str[i])
    return (NULL);
  tmp = (char *)malloc(sizeof(char) * i + 2);
  if (!tmp)
    return (NULL);
  i = 0;
  while (str[i] != 0 && str[i] != '\n'){
    tmp[i] = str[i];
    i++;
  }
  if (str[i] == '\n'){
     tmp[i] = '\n';
    tmp[i + 1] = '\0';
    return (tmp);
  }
  tmp[i] = '\0';
  return (tmp);
}

char *next_line(char *str)
{
  char *tmp;
  int i;
  int j;

  i = 0;
  while (str[i] != 0 && str[i] != '\n')
    i++;
  if (!str[i])
    return (NULL);
  tmp = (char *)malloc(sizeof(char) * ft_strlen(str) - i + 2);
  if (!tmp)
    return (NULL);
  i++;
  j = 0;
  while (str[i] != 0){
    tmp[j] = str[i];
    j++;
    i++;
  }
  tmp[j] = '\0';
  return (tmp);
}

char *get_next_line(int fd)
{
  char *line;
  static char *str;

  if (fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0) // la condicion del read 
    return (NULL);
  str = read_line (str, fd);
  if (!str)
    return (NULL);
  line = get_line(str);
  str = next_line (str);
  return (line);
}


int main(void)
{
  char *line;

 while (((line = get_next_line (0))))
 {
    printf ("[%s]", line);
    free (line);
    line = NULL; 
 }
    printf ("[%s]", line);
}

