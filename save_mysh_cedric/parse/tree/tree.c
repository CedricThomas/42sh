/*
** tree.c for parseur in /home/cedric/delivery/parseur_ll/tree
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Fri Mar 24 15:26:37 2017 
** Last update Sun Mar 26 11:32:38 2017 Cédric Thomas
*/
#include <stdlib.h>
#include "syntax.h"

static t_token	*search_biggest(t_token *start, t_token *end,
				     t_syntax *my_syntax)
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

t_node		*create_tree(t_node *root, t_syntax *my_syntax,
			     t_token *start, t_token *end)
{
  t_token	*middle;
  t_node	*new_node;

  middle = search_biggest(start, end, my_syntax);
  new_node = create_node(root, middle->token, middle->type);
  if (middle != start)
    new_node->left = create_tree(new_node, my_syntax, start, middle);
  if (middle->next != end)
    new_node->right = create_tree(new_node, my_syntax, middle->next, end);
  return (new_node);
}
