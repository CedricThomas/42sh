/*
** fg.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon May 15 22:40:26 2017 Thibaut Cornolti
** Last update Tue May 16 18:37:29 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include <signal.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

void		builtin_fg(t_command *cmd, t_status *status, t_info *info)
{
  t_job		*job;

  job = status->job_list;
  auto_wait_job(status);
  while (job && !job->status && waitpid(job->pid, NULL, WNOHANG) != -1)
    job = job->next;
  if (!job)
    {
      my_puterror("fg: No current job.\n");
      return ;
    }
  printf("resume\n");
  my_put_list_exit(&(status->exit_list), job->pid, 0);
  auto_wait(status, info);
  job->status = 0;
}
