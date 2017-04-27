/*
** cmd.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar 29 13:26:21 2017 
** Last update Thu Apr  6 11:13:12 2017 Cédric Thomas
*/
#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"
#include "my_printf.h"

static void	my_undup(t_status *status, int save[2])
{
  if (status->forced.in != 0)
    {
      if (dup2(save[0], 0) < 0)
	exit(84);
      close(save[0]);
    }
  if (status->forced.out != 1)
    {
      if (dup2(save[1], 1) < 0)
	exit(84);
      close(save[1]);
    }
}

static void	my_dup(t_status *status, int save[2])
{
  if (status->forced.in != 0)
    {
      save[0] = dup(0);
      if (dup2(status->forced.in, 0) < 0)
	exit(84);
    }
  if (status->forced.out != 1)
    {
      save[1] = dup(1);
      if (dup2(status->forced.out, 1) < 0)
	exit(84);
    }
}

void		std_pipeline(t_status *status, t_toexec *exec, t_info *info)
{
  char		*path;

  if (!try_builtins(info, exec, status))
    exit(info->last);
  info->last = 0;
  replacepath(info, exec, &path);
  my_close_fd(&(status->fd), &(status->piped), &(status->pipe_max));
  if (!info->last)
    son(exec->argv, path, info);
  free(path);
  exit(info->last);
}

t_fd		my_cmd(t_node *root, t_status *status, t_info *info)
{
  int		save[2];
  t_toexec	exec;

  exec = mytoexec(args_node_to_argv(root), info->env);
  my_dup(status, save);
  if ((status->status & ON_FORK) == ON_FORK)
    std_pipeline(status, &exec, info);
  else
    exec_full(info, &exec, status);
  my_undup(status, save);
  free(exec.argv);
  return (status->forced);
}
