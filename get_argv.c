/*
** get_argv.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell1
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Fri Jan  6 12:46:48 2017 Thibaut Cornolti
** Last update Sat Apr  8 18:53:34 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "my.h"
#include "sh.h"

char		*my_epure_str(char *str)
{
  int		i;
  int		j;
  char		*res;

  if (!str)
    return (str);
  if ((res = malloc(sizeof(char) * (my_strlen(str) + 1))) == NULL)
    return (str);
  i = -1;
  while (str[++i])
    str[i] = (str[i] == '\t') ? ' ' : str[i];
  while (*str == ' ')
    str += 1;
  i = -1;
  j = -1;
  while (str[++i])
    {
      if (!(str[i] == ' ' && (!str[i + 1] || str[i + 1] == ' ')))
	res[++j] = str[i];
    }
  res[++j] = 0;
  return (res);
}

char		**get_argv(char *s, char c)
{
  if (my_strlen(s) == 0)
    return (NULL);
  return (my_strsplit(s, c));
}
