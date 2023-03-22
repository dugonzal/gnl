#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 200 + 150 - 349
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
    tmp[ft_strlen(tmp) + 1] = '\0';
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
  if (str[i] == '\n')
  {
     tmp[i] = '\n';
    i++;
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
  j = 0;
  while (str[i] != 0)
    tmp[j++] = str[++i];
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

 while (((line = get_next_line (0)))){
    printf ("\n[%s]", line);
    free (line);
 }
    printf ("[%s]", line);
}


/*

  ❯ ls
   get_next_line.c   gnl   studleak   test   tester_val.sh


❯ valgrind ./a.out

[(null)]
==48728== 
==48728== HEAP SUMMARY:
==48728==     in use at exit: 7,636 bytes in 121 blocks
==48728==   total heap usage: 7,878 allocs, 7,757 frees, 875,972 bytes allocated
==48728== 
==48728== 7,636 bytes in 121 blocks are definitely lost in loss record 1 of 1
==48728==    at 0x4841888: malloc (vg_replace_malloc.c:393)
==48728==    by 0x109240: ft_strjoin (in /home/ciclo/Documentos/42/42_School_Exam_Rank_02/0/core/exam/my_42_exam/0000/42-EXAM/rendu/get_next_line/gnl)
==48728==    by 0x109398: read_line (in /home/ciclo/Documentos/42/42_School_Exam_Rank_02/0/core/exam/my_42_exam/0000/42-EXAM/rendu/get_next_line/gnl)
==48728==    by 0x109612: get_next_line (in /home/ciclo/Documentos/42/42_School_Exam_Rank_02/0/core/exam/my_42_exam/0000/42-EXAM/rendu/get_next_line/gnl)
==48728==    by 0x10969E: main (in /home/ciclo/Documentos/42/42_School_Exam_Rank_02/0/core/exam/my_42_exam/0000/42-EXAM/rendu/get_next_line/gnl)
==48728== 
==48728== LEAK SUMMARY:
==48728==    definitely lost: 7,636 bytes in 121 blocks
==48728==    indirectly lost: 0 bytes in 0 blocks
==48728==      possibly lost: 0 bytes in 0 blocks
==48728==    still reachable: 0 bytes in 0 blocks
==48728==         suppressed: 0 bytes in 0 blocks
==48728== 
==48728== ERROR SUMMARY: 122 errors from 2 contexts (suppressed: 0 from 0)
==48728== 
==48728== 121 errors in context 1 of 2:
==48728== Conditional jump or move depends on uninitialised value(s)
==48728==    at 0x1091AB: find (in /home/ciclo/Documentos/42/42_School_Exam_Rank_02/0/core/exam/my_42_exam/0000/42-EXAM/rendu/get_next_line/gnl)
==48728==    by 0x1093AF: read_line (in /home/ciclo/Documentos/42/42_School_Exam_Rank_02/0/core/exam/my_42_exam/0000/42-EXAM/rendu/get_next_line/gnl)
==48728==    by 0x109612: get_next_line (in /home/ciclo/Documentos/42/42_School_Exam_Rank_02/0/core/exam/my_42_exam/0000/42-EXAM/rendu/get_next_line/gnl)
==48728==    by 0x10969E: main (in /home/ciclo/Documentos/42/42_School_Exam_Rank_02/0/core/exam/my_42_exam/0000/42-EXAM/rendu/get_next_line/gnl)
==48728==  Uninitialised value was created by a heap allocation
==48728==    at 0x4841888: malloc (vg_replace_malloc.c:393)
==48728==    by 0x109324: read_line (in /home/ciclo/Documentos/42/42_School_Exam_Rank_02/0/core/exam/my_42_exam/0000/42-EXAM/rendu/get_next_line/gnl)
==48728==    by 0x109612: get_next_line (in /home/ciclo/Documentos/42/42_School_Exam_Rank_02/0/core/exam/my_42_exam/0000/42-EXAM/rendu/get_next_line/gnl)
==48728==    by 0x10969E: main (in /home/ciclo/Documentos/42/42_School_Exam_Rank_02/0/core/exam/my_42_exam/0000/42-EXAM/rendu/get_next_line/gnl)
==48728== 
==48728== ERROR SUMMARY: 122 errors from 2 contexts (suppressed: 0 from 0)

*/
