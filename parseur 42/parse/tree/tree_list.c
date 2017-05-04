/*
** tree_list.c for parseur in /home/cedric/delivery/parseur_ll/tree
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Fri Mar 24 15:04:43 2017 
** Last update Thu May  4 15:54:10 2017 
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

void	show_nodes(t_node *root, int depth, int side)
{
  if (root->right != NULL)
    show_nodes(root->right, depth + 1, 2);
  pad_me(depth);
  my_printf("%d: [%d] %s\n", side, root->type, root->data);
  if (root->left != NULL)
    show_nodes(root->left, depth + 1, 1);
}

void		*create_basic_node(t_node *root, t_token *token)
{
  t_node	*new_node;

  if ((new_node = malloc(sizeof(t_node))) == NULL)
    exit(84);
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->root = root;
  new_node->type = token->type;
  if ((new_node->data = my_strdup(token->token)) == NULL)
    exit(84);
  return (new_node);
}

void		my_free_node(t_node **root)
{
  t_command	*cmd;

  free((*root)->data);
  free(*root);
  if ((*root)->type == T_COMMAND)
    {
      cmd = (t_command *)(*root);
      free_tab(cmd->argv);
    }
  (*root) = NULL;
}

void		my_free_tree(void **root)
{
  t_node	**node;

  node = (t_node **)root;
  if ((*node)->left)
    my_free_tree(&((*node)->left));
  if ((*node)->right)
    my_free_tree(&((*node)->right));
  my_free_node(node);
}
