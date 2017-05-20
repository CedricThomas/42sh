/*
** backquote_fork.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parse/backquote
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Fri May 19 18:17:46 2017 Thibaut Cornolti
** Last update Sat May 20 13:53:26 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <limits.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static char	*read_son(int fd, int pid, t_system *system)
{
  char		*res;
  int		size;
  char		buf[PIPE_BUF + 1];
  int		readed;
  int		status;

  res = NULL;
  size = 0;
  while (waitpid(pid, &status, WNOHANG) <= 0)
    {
      if ((readed = read(fd, buf, PIPE_BUF)) == -1)
	return (NULL);
      size += readed;
      buf[readed] = 0;
      if ((res = realloc(res, size + 1)) == NULL)
	exit(84);
      my_strcpy(res + size - readed, buf);
    }
  system->info->exit_value_backquote = status;
  if ((res = replace_unquoted_str(res, "\n", " ", "")) == NULL)
    exit(84);
  return (res);
}

void		redef_token(t_token *token)
{
  t_token	*tmp;

  tmp = token;
  while (tmp)
    {
      if (tmp->type & T_COMMON)
	tmp->type = T_COMMON;
      tmp = tmp->next;
    }
  shape_token(token);
}

t_token		*get_system(char *cmd)
{
  char		*line;
  int		pipefd[2];
  int		pid;
  t_system	*sys;

  if (pipe(pipefd) < 0)
    {
      my_puterror("Can't make pipe.");
      return (NULL);
    }
  sys = getter_system(NULL);
  signal(SIGINT, SIG_IGN);
  if ((pid = fork()) == -1)
    return (NULL);
  else if (pid)
    close(pipefd[1]);
  else
    {
      signal(SIGINT, SIG_DFL);
      dup2(pipefd[1], 1);
      close(pipefd[0]);
      my_system(cmd, sys);
      exit(sys->info->exit_value);
    }
  line = read_son(pipefd[0], pid, sys);
  signal(SIGINT, &signal_sigint);
  return (get_token(line, sys->syntax, NULL));
}
