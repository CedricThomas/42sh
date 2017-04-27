/*
** append.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Wed Jan  4 13:33:24 2017 Cédric Thomas
** Last update Thu Jan 12 19:25:13 2017 Cédric Thomas
*/
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "mysh.h"

int	my_nullstrlen(char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    return (0);
  while (str[i])
    i += 1;
  return (i);
}

int	my_strtocharlen(char *str, char c)
{
  int	i;

  i = 0;
  if (str == NULL)
    return (0);
  while (str[i] && str[i] != c)
    i += 1;
  return (i);
}

char	*strappend(char *s1, char *s2, int freeit)
{
  char	*new;
  int	len;
  int	i;

  len = my_nullstrlen(s1) + my_nullstrlen(s2);
  i = 0;
  if (len == 0 || (new = malloc(sizeof(char) * (len + 1))) == NULL)
    return (NULL);
  new[len] = 0;
  while (i < len)
    {
      if (i < my_nullstrlen(s1))
	new[i] = s1[i];
      else
	new[i] = s2[i - my_nullstrlen(s1)];
      i += 1;
    }
  if (freeit == 3 || freeit == 1)
    free(s1);
  if (freeit == 3 || freeit == 2)
    free(s2);
  return (new);
}

char	**tabdup(char **tab)
{
  int	i;
  char	**dup;

  i = 0;
  while (tab[i])
    i += 1;
  if ((dup = malloc(sizeof(char *) * (i + 1))) == NULL)
    return (NULL);
  i = 0;
  while (tab[i])
    {
      if ((dup[i] = my_strdup(tab[i])) == NULL)
	return (NULL);
      i += 1;
    }
  dup[i] = NULL;
  return (dup);
}

char	*replaceinstr(char *tochange, char *tofind, char *toreplace)
{
  int	index;
  int	lenfull;
  char	*new;
  int	i;

  index = -1;
  i = -1;
  if (!tofind || !tochange ||
      !toreplace || my_strstr(tochange, tofind) == NULL)
    return (tochange);
  lenfull = my_strlen(tochange) - my_strlen(tofind) + my_strlen(toreplace);
  while (tochange[++index] &&
	 my_strncmp(tochange + index, tofind, my_strlen(tofind)));
  if ((new = malloc(sizeof(char) * (lenfull + 1))) == NULL)
    return (tochange);
  while (++i < lenfull)
    if (i < index)
      new[i] = tochange[i];
    else if (i < index + my_strlen(toreplace))
      new[i] = toreplace[i - index];
    else
      new[i] = tochange[i - my_strlen(toreplace) + my_strlen(tofind)];
  new[i] = 0;
  free(tochange);
  return (new);
}
