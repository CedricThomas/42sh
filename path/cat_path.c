/*
** cat_path.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell1
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Tue Jan 17 23:44:53 2017 Thibaut Cornolti
** Last update Thu Mar 23 14:03:56 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "my.h"
#include "sh.h"

char		*cat_path(char *path, char *name)
{
  char		*result;
  int		i;
  int		j;

  if (path == NULL)
    return (name);
  result = malloc(sizeof(char) *
		  (my_strlen(path) + my_strlen(name) + 3));
  if (result == NULL)
    return (NULL);
  i = -1;
  j = -1;
  while (path[++i])
    result[++j] = path[i];
  i = -1;
  if (result[j] != '/')
    result[++j] = '/';
  while (name[++i])
    result[++j] = name[i];
  result[++j] = '/';
  result[++j] = 0;
  return (result);
}

char		*cat_path_wm(char *path, char *name, int *k)
{
  int		i;
  int		j;

  if (path == NULL)
    return (name);
  if (name == NULL)
    return (path);
  i = -1;
  j = -1;
  while (path[++j]);
  i = -1;
  if (path[j] != '/')
    path[j] = '/';
  while (name[++i])
    path[++j] = name[i];
  path[++j] = '/';
  path[++j] = 0;
  *k = j - 1;
  return (path);
}
