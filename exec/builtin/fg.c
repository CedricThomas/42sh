/*
** fg.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon May 15 22:40:26 2017 Thibaut Cornolti
** Last update Thu May 18 13:25:32 2017 Thibaut Cornolti
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
  t_job		*job;

  UNUSED(cmd);
  UNUSED(info);
  job = status->job_list;
  auto_wait_job(status);
  while (!(job == NULL ||
	   ((job->status & JOB_BACKGROUND) && waitpid(job->pid, NULL, WNOHANG | WUNTRACED) != -1)))
    job = job->next;
  if (!job)
    {
      my_puterror("fg: No current job.\n");
      return ;
    }
  tcsetpgrp(0, job->pgid);
  kill(-job->pgid, SIGCONT);
  job->status = JOB_FOREGROUND;
  my_printf("Continued\n");
  auto_wait_job(status);
}
