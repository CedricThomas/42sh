/*
** logic.c for 42sh in /home/cedric/delivery/PSU/PSU_2016_42sh/parseur 42
** 
** Made by Cédric THOMASCédric Thomas
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Thu May 11 16:55:14 2017 Cédric Thomas
** Last update Thu May 11 16:59:38 2017 Cédric Thomas
*/
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

int		exec_logic(t_node *root, t_status *status, t_info *info)
{
  auto_select(root->left, status, info);
  if (info->exit_value && !my_strcmp(root->data, "||"))
    auto_select(root->right, status, info);
  else if (!info->exit_value && !my_strcmp(root->data, "&&"))
    auto_select(root->right, status, info);
  return (0);
}
