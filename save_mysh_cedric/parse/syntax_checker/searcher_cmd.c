/*
** searcher_cmd.c for parseur in /home/cedric/delivery/parseur_ll/syntax_checker
** 
** Made by Cédric Thomas
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon Mar 27 09:46:18 2017 Cédric Thomas
** Last update Tue Apr  4 15:48:59 2017 
*/
#include "syntax.h"

int	search_command(t_node *root, int branch)
{
  if (root->type == T_COMMAND)
    return (1);
  return (0);
}
