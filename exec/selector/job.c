/*
** job.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon May 15 20:54:17 2017 Thibaut Cornolti
** Last update Thu May 18 21:46:48 2017 Thibaut Cornolti
*/

#include <unistd.h>
#include <signal.h>
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"

static void	show_process(t_status *status)
{
  t_exit	*exit;
  t_job		*job;
  int		last;

  exit = status->exit_list;
  last = 0;
  while (exit)
    {
      job = exit->job;
      if (job->status & JOB_CREATPRINT)
	{
	  if (last != job->number)
	    {
	      my_printf((last) ? "\n[%d]" : "[%d]", job->number);
	      last = job->number;
	    }
	  my_printf(" %d", job->pid);
	  job->status = JOB_BACKGROUND;
	}
      exit = exit->next;
    }
  my_printf("\n");
}

int		exec_job(t_node *root, t_status *status, t_info *info)
{
  int		first;

  first = 0;
  if ((status->status & JOBLINE) != JOBLINE)
    {
      first = 1;
      status->status |= JOBLINE;
      auto_wait(status, info);
    }
  status->status |= JOB;
  status->job_nbr = get_free_job(status->exit_list);
  auto_select(root->left, status, info);
  show_process(status);
  status->status -= JOB;
  auto_select(root->right, status, info);
  if (first)
    status->status -= JOBLINE;
  return (0);
}
