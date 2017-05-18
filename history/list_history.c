/*
** list_lexer.c for lexer in /home/cedric/delivery/parseur_ll
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar 22 21:39:39 2017 
** Last update Thu May 18 18:16:47 2017 Cédric THOMAS
*/
#include <string.h>
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"

int		my_put_list_history(t_history **ll, char *history, long time)
{
  t_history	*elem;
  t_history	*tmp;

  if ((elem = malloc(sizeof(*elem))) == NULL)
    exit(84);
  memset(elem, 0, sizeof(*elem));
  elem->cmd = history;
  elem->time = time;
  if (*ll == NULL)
    {
      elem->next = NULL;
      elem->prev = NULL;
      *ll = elem;
    }
  else
    {
      tmp = *ll;
      while (tmp->next != NULL)
	tmp = tmp->next;
      elem->prev = tmp;
      elem->next = NULL;
      tmp->next = elem;
    }
  return (0);
}

int		my_del_list_history(t_history **ll, t_history *elem)
{
  if (*ll == elem)
    {
      if ((*ll)->next != NULL)
	*ll = (*ll)->next;
      else if ((*ll)->prev != NULL)
	*ll = (*ll)->prev;
      else
	*ll = NULL;
    }
  if (elem->next != NULL)
    elem->next->prev = elem->prev;
  if (elem->prev != NULL)
    elem->prev->next = elem->next;
  free(elem->cmd);
  free(elem);
  return (0);
}

int		my_free_history(t_history **ll)
{
  while (*ll != NULL)
    my_del_list_history(ll, *ll);
  *ll = NULL;
  return (0);
}
