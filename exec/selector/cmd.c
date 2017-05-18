/*
** cmd.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar 29 13:26:21 2017 
** Last update Thu May 18 19:23:32 2017 Bastien
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
  fct[5] = &builtin_alias;
  fct[6] = &builtin_unalias;
  fct[7] = &builtin_fg;
  fct[8] = &builtin_bg;
  fct[9] = &builtin_jobs;
  fct[10] = &builtin_set;
  fct[11] = &builtin_unset;
}

static int	exec_builtins(t_command *cmd, t_status *status,
			      t_info *info, int index)
{
  void		(*builtins[BUILTINS_NB])(t_command *cmd,
					 t_status *status,
					 t_info *info);
  int		save[3];

  fill_builtins(builtins);
  if ((status->status & LEFT_PIPE) == LEFT_PIPE ||
      (status->status & JOB) == JOB)
    my_fork(cmd, status, info, builtins[index]);
  else
    {
      if (load_redir(cmd, status))
	{
	  my_put_list_exit(&status->exit_list, -1, -1, 1);
	  return (1);
	}
      my_dup(cmd, save);
      builtins[index](cmd, status, info);
      my_undup(cmd, save);
    }
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
  t_command	*cmd;

  cmd = (t_command *)root;
  wait = auto_exec(cmd, status, info);
  auto_wait_job(status);
  if (wait)
    auto_wait(status, info);
  return (0);
}
