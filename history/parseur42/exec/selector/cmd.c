/*
** cmd.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar 29 13:26:21 2017 
** Last update Fri May 12 18:52:17 2017 
*/
#include <unistd.h>
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"

static void	fill_builtins(void (*fct[BUILTINS_NB])(t_command *cmd,
						       t_status *status,
						       t_info *info))
{
  fct[0] = &builtin_exit;
  fct[1] = &builtin_cd;
  fct[2] = &builtin_setenv;
  fct[3] = &builtin_unsetenv;
  fct[4] = &builtin_echo;
}

static int	exec_builtins(t_command *cmd, t_status *status,
			      t_info *info, int index)
{
  void	(*builtins[BUILTINS_NB])(t_command *cmd,
				 t_status *status,
				 t_info *info);

  fill_builtins(builtins);
  if ((status->status & LEFT_PIPE) == LEFT_PIPE)
    my_fork(cmd, status, info, builtins[index]);
  else
    builtins[index](cmd, status, info);
  return (0);
}

static int	exec_std(t_command *cmd, t_status *status, t_info *info)
{
  my_fork(cmd, status, info, &simple_exec);
  if ((status->status & PIPELINE) != PIPELINE)
    return (1);
  return (0);
}

static int	auto_exec(t_command *cmd, t_status *status, t_info *info)
{
  int		idx;

  idx = 0;
  if ((idx = exist_in_tab(cmd->path, info->builtins)) >= 0)
    exec_builtins(cmd, status, info, idx);
  else
    if (exec_std(cmd, status, info))
      return (1);
  return (0);
}

int		exec_cmd(t_node *root, t_status *status, t_info *info)
{
  int		wait;
  int		save[3];
  t_command	*cmd;

  cmd = (t_command *)root;
  if (load_redir(cmd))
    {
      my_put_list_exit(&status->exit_list, -1, 1);
      if ((status->status & PIPELINE) != PIPELINE)
	auto_wait(status, info);
      return (1);
    }
  my_dup(cmd, save);
  wait = auto_exec(cmd, status, info);
  my_undup(cmd, save);
  if (wait)
    auto_wait(status, info);
  return (0);
}
