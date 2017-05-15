/*
** tab.c for 42sh in /home/cedric/Desktop/parseur 42/exec
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue May  9 09:37:36 2017 
** Last update Tue May  9 18:28:31 2017 
*/
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

int		exist_in_tab(char *str, char **tab)
{
  int		i;

  i = -1;
  while (tab[++i])
    if (!my_strcmp(str, tab[i]))
      return (i);
  return (-1);
}

char		**tab_dup(char **tab)
{
  int		i;
  char		**dup;

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
