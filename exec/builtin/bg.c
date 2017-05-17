/*
** fg.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon May 15 22:40:26 2017 Thibaut Cornolti
** Last update Wed May 17 13:03:44 2017 Thibaut Cornolti
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
  t_job		*job;

  UNUSED(cmd);
  UNUSED(info);
  job = status->job_list;
  auto_wait_job(status);
  while (!(job == NULL ||
	   (job->status && job->status != JOB_BACKGROUND
	    && waitpid(job->pid, NULL, WNOHANG) != -1)))
    job = job->next;
  if (!job)
    {
      my_puterror("bg: No current job.\n");
      return ;
    }
  tcsetpgrp(0, getpid());
  kill(job->pid, SIGCONT);
  job->status = JOB_BACKGROUND;
}
