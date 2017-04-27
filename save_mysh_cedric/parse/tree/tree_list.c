/*
** tree_list.c for parseur in /home/cedric/delivery/parseur_ll/tree
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Fri Mar 24 15:04:43 2017 
** Last update Sun Apr  2 22:43:45 2017 
*/

#include <stdlib.h>
#include "syntax.h"
#include "my.h"
#include "my_printf.h"

static void	pad_me(int depth)
{
  int		i;

  i = -1;
  while (++i < depth)
    my_putchar('\t');
}

t_node		*show_nodes(t_node *root, int depth, int side)
{
  if (root->right != NULL)
    show_nodes(root->right, depth + 1, 2);
  else
    {
      pad_me(depth + 1);
      my_putstr("empty\n");
    }
  pad_me(depth);
  my_printf("%d: [%d] %s\n", side, root->type, root->data);
  if (root->left != NULL)
    show_nodes(root->left, depth + 1, 1);
  else
    {
      pad_me(depth + 1);
      my_putstr("empty\n");
    }
}

t_node		*create_node(t_node *root, char *value, int type)
{
  t_node	*new_node;

  if ((new_node = malloc(sizeof(t_node))) == NULL)
    exit(84);
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->root = root;
  new_node->type = type;
  if ((new_node->data = dequotificator(value)) == NULL)
    exit(84);
  return (new_node);
}

void	my_free_tree(t_node **root)
{
  if ((*root)->left)
    my_free_tree(&((*root)->left));
  if ((*root)->right)
    my_free_tree(&((*root)->right));
  free((*root)->data);
  free(*root);
  (*root) = NULL;
}
