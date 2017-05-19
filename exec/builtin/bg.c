/*
1;2802;0c** fg.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon May 15 22:40:26 2017 Thibaut Cornolti
** Last update Thu May 18 18:43:27 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

void		builtin_bg(t_command *cmd, t_status *status, t_info *info)
{
  t_exit	*exit;

  UNUSED(cmd);
  UNUSED(info);
  exit = status->exit_list;
  auto_wait(status, info);
  while (!(exit == NULL ||
	   exit->job->status & JOB_FOREGROUND ||
	   exit->job->status & JOB_SUSPENDED))
    exit = exit->next;
  if (!exit)
    {
      my_puterror("bg: No current job.\n");
      return ;
    }
  tcsetpgrp(0, getpgrp());
  kill(-exit->job->pgid, SIGCONT);
  exit->job->status = JOB_BACKGROUND;
}
