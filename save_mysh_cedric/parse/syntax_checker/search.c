/*
** search.c for parseur in /home/cedric/delivery/parseur_ll/syntax_checker
** 
** Made by Cédric Thomas
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon Mar 27 06:25:37 2017 Cédric Thomas
** Last update Mon Apr  3 01:03:25 2017 
*/
#include "syntax.h"

int	search_parent(t_node *root,
		      int (*searcher)(t_node *root, char c),
		      char c)
{
  if (root->root)
    {
      root = root->root;
      if (searcher(root, c))
	return (1 + search_parent(root, searcher, c));
      else
	return (search_parent(root, searcher, c));
    }
  return (0);
}

int	search_child(t_node *root,
		     int (*searcher)(t_node *root, int branch),
		     int branch)
{
  int	ret;

  ret = 0;
  if (root->left)
    {
      ret += searcher(root->left, branch);
      ret += search_child(root->left, searcher, branch);
    }
  if (root->right)
    {
      ret += searcher(root->right, branch);
      ret += search_child(root->right, searcher, branch);
    }
  return (ret);
}

int	search_child_auto(t_node *root,
		     int (*searcher)(t_node *root, int branch))
{
  int	ret;

  ret = 0;
  if (root->left)
    {
      ret += searcher(root->left, 1);
      ret += search_child_auto(root->left, searcher);
    }
  if (root->right)
    {
      ret += searcher(root->right, 2);
      ret += search_child_auto(root->right, searcher);
    }
  return (ret);
}
