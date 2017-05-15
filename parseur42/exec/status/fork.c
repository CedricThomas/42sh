/*
** fork.c for 42sh in /home/cedric/delivery/PSU/PSU_2016_42sh/parseur 42/exec
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed May 10 21:06:35 2017 
** Last update Mon May 15 16:10:57 2017 Thibaut Cornolti
*/
#include <unistd.h>
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"

int	my_fork(t_command *cmd, t_status *status, t_info *info,
		void (*fct)(t_command *cmd, t_status *status, t_info *info))
{
  pid_t	pid;

  pid = fork();
  if (pid == 0)
    {
      status->status |= FORK;
      my_dup(cmd, NULL);
      if (status->fd_to_close)
	close(status->fd_to_close);
      if (load_redir(cmd, status))
	exit(1);
      fct(cmd, status, info);
      exit(info->exit_value);
    }
  else if (pid > 0)
    my_put_list_exit(&(status->exit_list), pid, 0);
  else
    return (-1);
  return (0);
}
