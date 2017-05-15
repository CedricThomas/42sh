/*
** alloc.c for alloc in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur 42/parse/tree
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May  4 18:48:35 2017 Thibaut Cornolti
** Last update Thu May  4 20:30:38 2017 Thibaut Cornolti
*/

#include <sys/types.h>
#include <stdlib.h>
#include "my_alloc.h"
#include "my.h"

char		*alloc_strdup(char *str)
{
  int		i;
  char		*res;

  if ((res = my_alloc(sizeof(char) * (my_strlen(str) + 1))) == NULL)
    return (NULL);
  i = -1;
  while (str[++i])
    res[i] = str[i];
  res[i] = 0;
  return (res);
}
