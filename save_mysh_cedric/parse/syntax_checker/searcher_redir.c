/*
** searcher.c for parseur in /home/cedric/delivery/parseur_ll/syntax_checker
** 
** Made by Cédric Thomas
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon Mar 27 08:50:11 2017 Cédric Thomas
** Last update Mon Apr  3 00:59:35 2017 
*/
#include "my.h"
#include "syntax.h"

/*
**>, >>
*/

int	search_rightflux_error(t_node *root, int branch)
{
  if (!root)
    return (0);
  if (branch == 2)
    return (0);
  if (is_in('>', root->data) && root->type == T_FLUX_REDIR)
    return (1);
  return (0);
}

/*
**<, <<
*/

int	search_leftflux_error(t_node *root, int branch)
{
  if (!root)
    return (0);
  if (branch == 1)
    return (0);
  if (is_in('<', root->data) && root->type == T_FLUX_REDIR)
    return (1);
  return (0);
}

/*
**char searcher for parent
*/

int	search_in(t_node *root, char c)
{
  if (!root)
    return (0);
  if (is_in(c, root->data) && root->type == T_FLUX_REDIR)
    return (1);
  return (0);
}

int	search_flux_parent(t_node *root, char c)
{
  if (!root)
    return (0);
  if (root->type == T_FLUX)
    return (1);
  return (0);
}
