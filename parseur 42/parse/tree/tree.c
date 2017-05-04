/*
** tree.c for parseur in /home/cedric/delivery/parseur_ll/tree
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Fri Mar 24 15:26:37 2017 
** Last update Thu May  4 18:11:46 2017 
*/
#include <math.h>
#include <stdlib.h>
#include "syntax.h"

static t_token	*search_biggest(t_token *start, t_token *end)
{
  t_token	*temp;
  t_token	*save;

  temp = start;
  save = start;
  while (temp != end)
    {
      if (save->type < temp->type)
	save = temp;
      temp = temp->next;
    }
  return (save);
}

static void	fct_fill(void *(*fct[FULL_MAX_TYPES])(void *root,
						      t_token *start,
						      t_token *end))
{
  fct[0] = ;
  fct[1] = ;
  fct[2] = ;
  fct[3] = ;
  fct[4] = ;
  fct[5] = ;
  fct[6] = ;
  fct[7] = ;
}

static void	*auto_create_node(void *root, t_token *start, t_token *end)
{
  void		*ret;
  void		*(*fct[FULL_MAX_TYPES])(void *root, t_token *start, t_token *end);

  fill_fct(fct);
  ret = fct[log2()](root, start, end);
  return (ret);
}
