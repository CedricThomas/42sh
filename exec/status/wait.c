/*
** fork.c for fork in /home/cedric/delivery/PSU/PSU_2016_42sh/parseur 42/exec
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue May  9 20:20:52 2017 
** Last update Thu May 18 23:49:51 2017 Thibaut Cornolti
*/

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
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
      if (WIFSIGNALED(tmp->exit) && !(tmp->job->status & JOB_TERMPRINT))
	check_sig(tmp->exit);
      if (tmp->exit && !(tmp->job->status & JOB_TERMPRINT))
	{
	  last = tmp->exit;
	  if (tmp->pid < 0)
	    info->exit_value = last;
	  else if (WIFEXITED(last))
	    info->exit_value = WEXITSTATUS(last);
	  else if (WIFSIGNALED(last))
	    info->exit_value = last % 128 + 128;
	}
      tmp->exit = (tmp->job->status & JOB_TERMPRINT) ? tmp->exit : 0;
      tmp = tmp->next;
    }
}

void		print_wait_job(t_status *status)
{
  t_exit	*exit;
  t_job		*job;
  int		last;

  exit = status->exit_list;
  while (exit && exit->next)
    exit = exit->next;
  last = 0;
  while (exit)
    {
      job = exit->job;
      if (job->status & JOB_TERMPRINT && job->number)
	{
	  if (last != job->number)
	    {
	      if (exit->exit)
		my_printf("[%d]    Exit %d\n", job->number, exit->exit % 255);
	      else
		my_printf("[%d]    Done\n", job->number);
	      last = job->number;
	    }
	  job->status = JOB_TERMINATED;
	  job->number = 0;
	  exit->exit = 0;
	}
      exit = exit->prev;
    }
}

void		auto_wait(t_status *status, t_info *info)
{
  t_exit	*tmp;
  int		last;

  tmp = status->exit_list;
  while (tmp)
    {
      if (tmp->pid > 0 && tmp->job->status & JOB_BACKGROUND &&
	  waitpid(tmp->pid, &last, WNOHANG) > 0)
	{
	  tmp->job->status = JOB_TERMPRINT;
	  set_exit_value(status->exit_list, tmp->pid, last);
	}
      else if (tmp->pid > 0 && tmp->job->status & JOB_FOREGROUND)
	{
	  tcsetpgrp(0, tmp->pgid);
	  while (waitpid(tmp->pid, &last, WNOHANG | WUNTRACED) <= 0);
	  if (WIFSTOPPED(last))
	    {
	      tmp->job->status = JOB_SUSPENDED;
	      my_printf("Suspended\n");
	    }
	  else
	    {
	      tmp->job->status = JOB_TERMINATED;
	      tmp->job->number = 0;
	      set_exit_value(status->exit_list, tmp->pid, last);
	      info->exit_value = 0;
	    }
	}
      tmp = tmp->next;
    }
  get_exit_value(status, info);
  tcsetpgrp(0, getpgrp());
}
