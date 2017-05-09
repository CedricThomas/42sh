/*
** separ.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar 29 13:22:51 2017 
** Last update Thu Apr  6 10:58:34 2017 Cédric Thomas
*/
#include <stdlib.h>
#include "mysh.h"

t_fd		my_separ(t_node *root, t_status *status, t_info *info)
{
  search_actions(root->left, status, info);
  my_close_fd(&(status->fd), &(status->piped), &(status->pipe_max));
  reset_status(status);
  search_actions(root->right, status, info);
  return (myfds(0, 0));
}
