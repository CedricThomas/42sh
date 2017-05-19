/*
** fg.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon May 15 22:40:26 2017 Thibaut Cornolti
** Last update Thu May 18 18:41:20 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"
#include "my_printf.h"

void		builtin_fg(t_command *cmd, t_status *status, t_info *info)
{
  t_exit	*exit;

  UNUSED(cmd);
  UNUSED(info);
  auto_wait(status, info);
  exit = status->exit_list;
  while (!(exit == NULL || exit->job->status & JOB_BACKGROUND))
    exit = exit->next;
  if (!exit)
    {
      my_puterror("fg: No current job.\n");
      return ;
    }
  tcsetpgrp(0, exit->job->pgid);
  kill(-exit->job->pgid, SIGCONT);
  exit->job->status = JOB_FOREGROUND;
  my_printf("Continued\n");
  auto_wait(status, info);
}
