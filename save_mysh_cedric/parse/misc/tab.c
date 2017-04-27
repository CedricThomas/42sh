/*
** tab.c for parseur in /home/cedric/delivery/parseur_ll
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Thu Mar 23 10:00:54 2017 
** Last update Thu Mar 23 10:10:31 2017 
*/
#include <stdlib.h>
#include <stdarg.h>
#include "syntax.h"
#include "my.h"

char		**tab_create(int size, ...)
{
  char	       *str;
  int		i;
  va_list	str_list;
  char		**tab;

  if ((tab = malloc(sizeof(char *) * (size + 1))) == NULL)
    return (NULL);
  i = -1;
  va_start(str_list, size);
  while (++ i < size)
    {
      str = va_arg(str_list, char *);
      if ((tab[i] = my_strdup(str)) == NULL)
	return (NULL);
    }
  tab[i] = NULL;
  va_end(str_list);
  return (tab);
}
