/*
** fg.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon May 15 22:40:26 2017 Thibaut Cornolti
** Last update Wed May 17 14:47:10 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"
#include "my_printf.h"

void		builtin_jobs(t_command *cmd, t_status *status, t_info *info)
{
  t_job		*job;
  int		last_nbr;
  int		argc;

  UNUSED(info);
  argc = -1;
  while (cmd->argv[++argc]);
  if (argc != 1 && !(argc == 2 && !strcmp(cmd->argv[1], "-l")))
    {
      my_puterror("Usage: jobs [ -l ].\n");
    }
  job = status->job_list;
  auto_wait_job(status);
  last_nbr = 0;
  while (job)
    {
      if (job->number != last_nbr)
	my_printf("[%d]    Running\n", job->number);
      last_nbr = job->number;
      job = job->next;
    }
}
