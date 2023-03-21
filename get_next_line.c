#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 2

#endif /* ifndef BUFFER_SIZE */
// creo que no paso los test porque no contorlo bien los errores

int ft_strchr(char *str)
{
  int i;

  if (!str)
      return (0);
  i = 0;
  while (str[i])
  {
    if (str[i] == '\n')
      return (1);
    i++;
  }
  return (0);
}

int ft_strlen(char *str)
{
  int i;

  if (!str)
    return (0);
  i = 0;
  while (str[i])
    i++;
  return (i);
}

char *clean(char *str)
{
  printf ("[%p]<- address  entro en la funcion de error", str);// <- pointer
  if (str)
    free (str);
  return (NULL);
}

char *ft_strjoin(char *s1, char *s2)
{
  char *tmp;
  int i;
  int j;

  if (!s2)
    clean (s2);
  if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1)))
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
  free ((void *)s1);
  return (tmp);
}

char *read_line (char *str, int fd)
{
  char *tmp;
  int rd;

  rd = 1;
  while (rd > 0 && !ft_strchr(tmp))
  {
      if (!(tmp = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
        clean (tmp);
      if ((rd = read(fd, tmp, BUFFER_SIZE)) == -1)
        clean (tmp);
      tmp[rd] = '\0';
      str = ft_strjoin(str, tmp);
  }
  free ((void *)tmp);
  return (str);
}

char *get_next_line(int fd)
{
  static char *str;
  char *line;
  (void)line;
  if (fd < 0|| BUFFER_SIZE < 1)
      return (NULL);
  str = read_line(str, fd);
  return (str);
}

int main(void)
{
  char *line;

  line = get_next_line (0);
  printf ("%s", line);
  printf ("%s", line);
  if (line)
    free (line);
}

