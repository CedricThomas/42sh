/*
** my_fork.c for my_fork in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Jan 11 10:34:47 2017 
** Last update Thu Apr  6 10:59:08 2017 Cédric Thomas
*/
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "mysh.h"
#include "my.h"

static void	check_errno(char *str)
{
  my_puterror(str);
  my_puterror(": ");
  if (errno == ENOEXEC)
    my_puterror("Exec format error. Binary file not executable.");
  else
    my_puterror("Error not handled.");
  my_puterror("\n");
  exit(1);
}

void	check_sig(int status)
{
  int	dump;

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

void	son(char **argv, char *name, t_info *info)
{
  signal(SIGINT, SIG_DFL);
  if (execve(name, argv, info->env) == -1)
    check_errno(name);
}

void	father(t_info *info)
{
  int		wstatus;

  wait(&wstatus);
  if (WIFEXITED(wstatus))
    info->last = WEXITSTATUS(wstatus);
  else if (WIFSIGNALED(wstatus))
    {
      info->last = wstatus % 128 + 128;
      check_sig(wstatus);
    }
}

int	my_fork(t_toexec *exec, char *name, t_info *info, t_status *status)
{
  int	forkvalue;

  forkvalue = fork();
  if (forkvalue == 0)
    {
      my_close_fd(&(status->fd), &(status->piped), &(status->pipe_max));
      son(exec->argv, name, info);
    }
  else if (forkvalue > 0)
    {
      if ((status->status & ON_PIPELINE) == ON_PIPELINE)
	{
	  my_put_list_exit(&(status->pipeline), forkvalue, 0);
	  status->cmd += 1;
	}
      else
	father(info);
    }
  else
    my_puterror("fork: the creation of the child failed.\n");
  return (0);
}
