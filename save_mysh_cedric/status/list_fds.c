/*
** list_lexer.c for lexer in /home/cedric/delivery/parseur_ll
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar 22 21:39:39 2017 
** Last update Thu Apr  6 11:10:10 2017 Cédric Thomas
*/
#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"
#include "my_printf.h"

int		my_put_list_fd(t_fd **ll, int in, int out)
{
  t_fd	*elem;
  t_fd	*tmp;

  if ((elem = malloc(sizeof(*elem))) == NULL)
    exit(84);
  elem->in = in;
  elem->out = out;
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

int		my_del_list_fd(t_fd **ll, t_fd *elem)
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
  if (elem->in != 0)
    close(elem->in);
  if (elem->out != 1)
    close(elem->out);
  free(elem);
  return (0);
}

int		my_close_fd(t_fd **ll, int **pipes, int *size)
{
  int		i;
  t_fd		*tmp;

  while (ll && *ll)
    {
      tmp = *ll;
      *ll = (*ll)->next;
      if (tmp->in != 0)
	close(tmp->in);
      if (tmp->out != 1)
	close(tmp->out);
      free(tmp);
    }
  if (pipes && *pipes)
    {
      i = -1;
      while (++i < 2 * *size)
	close((*pipes)[i]);
      free(*pipes);
      *pipes = NULL;
      *size = 0;
    }
  return (0);
}
