/*
** fg.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon May 15 22:40:26 2017 Thibaut Cornolti
** Last update Thu May 18 19:32:16 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"
#include "my_printf.h"

static void	print_jobs(t_job *job)
{
  static char	*status[6] = {"Running", "Suspended",
			      "Running", "Running",
			      "Terminated", "Terminated"};
  static int	code[6] = {JOB_CREATPRINT, JOB_SUSPENDED,
			   JOB_FOREGROUND, JOB_BACKGROUND,
			   JOB_TERMPRINT, JOB_TERMINATED};
  int		i;

  i = -1;
  my_printf("[%d]    ", job->number);
  while (++i < 6)
    if (code[i] == job->status)
      my_printf("%s\n", status[i]);
}

void		builtin_jobs(t_command *cmd, t_status *status, t_info *info)
{
  t_job		*job;
  t_exit	*exit;
  int		last_nbr;
  int		argc;

  UNUSED(info);
  argc = -1;
  while (cmd->argv[++argc]);
  if (argc != 1 && !(argc == 2 && !strcmp(cmd->argv[1], "-l")))
    my_puterror("Usage: jobs [ -l ].\n");
  exit = status->exit_list;
  auto_wait(status, info);
  last_nbr = 0;
  show_job_status(exit);
  while (exit)
    {
      job = exit->job;
      if (job->number != last_nbr &&
	  job->status != 0 && job->status < JOB_TERMPRINT)
	print_jobs(job);
      last_nbr = job->number;
      exit = exit->next;
    }
}
