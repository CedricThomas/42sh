/*
** fork.c for 42sh in /home/cedric/delivery/PSU/PSU_2016_42sh/parseur 42/exec
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed May 10 21:06:35 2017 
** Last update Thu May 11 20:53:53 2017 
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
      fct(cmd, status, info);
      exit(info->exit_value);
    }
  else if (pid > 0)
    my_put_list_exit(&(status->exit_list), pid, 0);
  else
    return (-1);
  return (0);
}
