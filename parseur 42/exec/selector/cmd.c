/*
** cmd.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar 29 13:26:21 2017 
** Last update Tue May  9 13:17:26 2017 
*/
#include <unistd.h>
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"

int		exec_cmd(t_node *root, t_status *status, t_info *info)
{
  int		save[3];
  t_command	*cmd;

  cmd = (t_command *)root;
  load_redir(cmd);
  
  
  
  
  
  close_redir(root);
}
