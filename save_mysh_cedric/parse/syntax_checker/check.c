/*
** check.c for parseur in /home/cedric/delivery/parseur_ll
** 
** Made by Cédric Thomas
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon Mar 27 09:41:20 2017 Cédric Thomas
** Last update Wed Apr  5 18:17:26 2017 Cédric Thomas
*/
#include "syntax.h"
#include "my.h"

int	check_syntax_pipe(t_node *root)
{
  int	ret;

  ret = 0;
  if (root->left)
    ret += check_syntax_pipe(root->left);
  if (root->right)
    ret += check_syntax_pipe(root->right);
  if (root->type == T_FLUX)
      if (!root->left || !root->right)
	ret += 1;
      else
	{
	  if (!search_child(root->left, &search_command, 1) &&
	      root->left->type != T_COMMAND)
	    ret += 1;
	  if (!search_child(root->right, &search_command, 2) &&
	      root->right->type != T_COMMAND)
	    ret += 1;
	}
  return (ret);
}

int	check_syntax_redir_out(t_node *root)
{
  int	ret;

  ret = 0;
  if (root->left)
    ret += check_syntax_redir_out(root->left);
  if (root->right)
    ret += check_syntax_redir_out(root->right);
  if (root->type == T_FLUX)
    ret += search_child_auto(root, &search_rightflux_error);
  return (ret);
}

int	check_syntax_redir_in(t_node *root)
{
  int	sum;
  int	ret;

  ret = 0;
  if (root->left)
    ret += check_syntax_redir_in(root->left);
  if (root->right)
    ret += check_syntax_redir_in(root->right);
  if (root->type == T_FLUX)
    ret += search_child_auto(root, &search_leftflux_error);
  if (root->type == T_FLUX_REDIR && is_in('<', root->data))
    {
      sum = search_parent(root, &search_flux_parent, '|');
      if (sum > 1)
	ret += 1;
    }
  return (ret);
}

int	check_double_redir(t_node *root, char c)
{
  int	ret;

  ret = 0;
  if (root->left)
    ret += check_double_redir(root->left, c);
  if (root->right)
    ret += check_double_redir(root->right, c);
  if (root->type == T_FLUX_REDIR && is_in(c, root->data))
    ret += search_parent(root, &search_in, c);
  return (ret);
}
