/*
** my_strdup.c for my_strdup in /home/thibrex/delivery/CPool_Day08/task01
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu@epitech.net>
** 
** Started on  Wed Oct 12 09:39:31 2016 Thibaut Cornolti
** Last update Thu Mar 23 19:28:57 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "my.h"

char	*my_strndup(char *src, int n)
{
  char	*dup;
  int	i;

  if ((dup = malloc(sizeof(char) * n + 1)) == NULL)
    exit(my_puterror("error") + 84);
  i = 0;
  while (src[i] != 0 && i < n)
    {
      dup[i] = src[i];
      i += 1;
    }
  dup[i] = 0;
  return (dup);
}
