/*
** separ.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar 29 13:22:51 2017 
** Last update Thu May 11 16:52:37 2017 Cédric Thomas
*/
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"

int		exec_separ(t_node *root, t_status *status, t_info *info)
{
  auto_select(root->left, status, info);
  auto_select(root->right, status, info);
  return (0);
}
