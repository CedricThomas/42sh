/*
** fork.c for fork in /home/cedric/delivery/PSU/PSU_2016_42sh/parseur 42/exec
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue May  9 20:20:52 2017 
** Last update Tue May 16 18:14:39 2017 Thibaut Cornolti
*/

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"
#include "my_printf.h"

static void	check_sig(int status)
{
  int   dump;

  dump = 0;
  if (WTERMSIG(status) == SIGSEGV && (dump = 1))
    my_puterror("Segmentation fault");
  if (WTERMSIG(status) == SIGFPE && (dump = 1))
    my_puterror("Floating exception");
  if (WTERMSIG(status) == SIGABRT && (dump = 1))
    my_puterror("Aborted");
  if (WTERMSIG(status) == SIGBUS && (dump = 1))
    my_puterror("Bus error");
  if (dump && WCOREDUMP(status))
    my_puterror(" (core dumped)");
  if (dump)
    my_puterror("\n");
}

static void	get_exit_value(t_status *status, t_info *info)
{
  int		last;
  t_exit	*tmp;

  tmp = status->exit_list;
  while (tmp)
    {
      if (WIFSIGNALED(tmp->exit))
	check_sig(tmp->exit);
      if (tmp->exit)
	{
	  last = tmp->exit;
	  if (tmp->pid < 0)
	    info->exit_value = last;
	  else if (WIFEXITED(last))
	    info->exit_value = WEXITSTATUS(last);
	  else if (WIFSIGNALED(last))
	    info->exit_value = last % 128 + 128;
	}
      tmp = tmp->next;
    }
}

static void	print_wait_job(t_status *status)
{
  t_job		*job;
  int		last;

  job = status->job_list;
  while (job && job->next)
    job = job->next;
  last = 0;
  while (job)
    {
      if (job->status && job->number && job->step == 2)
	{
	  if (last != job->number)
	    {
	      my_printf("[%d]    Done\n", job->number);
	      last = job->number;
	    }
	  job->status = 0;
	  job->number = 0;
	}
      job = job->prev;
    }
}

void		auto_wait_job(t_status *status)
{
  t_job		*job;

  job = status->job_list;
  if (!(status->status & JOB))
    {
      while (job && job->next)
	job = job->next;
      while (job)
	{
	  if (job->status && waitpid(job->pid, NULL, WNOHANG))
	    job->step = 2;
	  job = job->prev;
	}
    }
}

void		auto_wait(t_status *status, t_info *info)
{
  t_exit	*tmp;
  int		last;

  tmp = status->exit_list;
  info->exit_value = 0;
  auto_wait_job(status);
  while (tmp)
    {
      if (tmp->pid > 0)
	{
	  waitpid(tmp->pid, &last, 0);
	  set_exit_value(status->exit_list, tmp->pid, last);
	}
      tmp = tmp->next;
    }
  print_wait_job(status);
  get_exit_value(status, info);
  my_del_exit(&(status->exit_list));
}
