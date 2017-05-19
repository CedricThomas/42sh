/*
** backquote_fork.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parse/backquote
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Fri May 19 18:17:46 2017 Thibaut Cornolti
** Last update Fri May 19 21:42:40 2017 Cédric THOMAS
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
  char		buf[PIPE_BUF + 1];
  int		readed;
  int		status;

  res = NULL;
  while (waitpid(pid, &status, WNOHANG) <= 0)
    {
      if ((readed = read(fd, buf, PIPE_BUF)) == -1)
	return (NULL);
      buf[readed] = 0;
      if ((res = my_strcatdup(res, buf, 1)) == NULL)
	exit(84);
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
  t_system	*system;

  if (pipe(pipefd) < 0)
    {
      my_puterror("Can't make pipe.");
      return (NULL);
    }
  system = getter_system(NULL);
  if ((pid = fork()) == -1)
    return (NULL);
  else if (pid)
    close(pipefd[1]);
  else
    {
      dup2(pipefd[1], 1);
      close(pipefd[0]);
      my_system(cmd, system);
      exit(system->info->exit_value);
    }
  line = read_son(pipefd[0], pid, system);
  return (get_token(line, system->syntax, NULL));
}
