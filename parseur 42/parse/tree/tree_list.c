/*
** tree_list.c for parseur in /home/cedric/delivery/parseur_ll/tree
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Fri Mar 24 15:04:43 2017 
** Last update Thu May  4 20:59:21 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "syntax.h"
#include "my.h"
#include "my_printf.h"
#include "my_alloc.h"

static void	pad_me(int depth)
{
  int		i;

  i = -1;
  while (++i < depth)
    my_putchar('\t');
}

void	show_nodes(t_node *root, int depth, int side)
{
  if (root->right != NULL)
    show_nodes((t_node *)root->right, depth + 1, 2);
  pad_me(depth);
  my_printf("%d: [%d] %s\n", side, root->type, root->data);
  /* if (root->type == T_COMMAND) */
  /*   { */
  /*     my_printf(); */
      

  /*   } */
  if (root->left != NULL)
    show_nodes((t_node *)root->left, depth + 1, 1);
}

void		my_free_tree(void **root)
{
  my_free_tag("tree", 0);
  *root = NULL;
}
