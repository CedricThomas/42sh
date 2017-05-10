/*
** cmd.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar 29 13:26:21 2017 
** Last update Wed May 10 13:22:15 2017 
*/
#include <unistd.h>
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"

static void	fill_builtins(int (*fct[BUILTINS_NB])(t_command *cmd,
						      t_status *status,
						      t_info *info))
{
  fct[0] = NULL;
  fct[1] = NULL;  
  fct[2] = NULL;
  fct[3] = NULL;
  fct[4] = NULL;
}

static int	auto_exec(t_command *cmd, t_status *status, t_info *info)
{
  int		(*fct[BUILTINS_NB])(t_command *cmd,
				    t_status *status,
				    t_info *info);
  int		idx;

  fill_builtins(fct);
  if ((idx = exist_in_tab(cmd->path, info->builtins)) > 0)
    {
      
      printf("exec builtins\n");
      
    }
  else
    {
      
      printf("exec path\n");      
      
    }
}

int		exec_cmd(t_node *root, t_status *status, t_info *info)
{
  int		save[3];
  t_command	*cmd;

  cmd = (t_command *)root;
  load_redir(cmd);
  my_dup(cmd, save);
  auto_exec(cmd, status, info);
  my_undup(save);
  return (0);
}
