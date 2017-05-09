/*
** new_output.c for output in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur 42/exec/selector
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Tue May  9 14:40:23 2017 Thibaut Cornolti
** Last update Tue May  9 15:23:19 2017 Thibaut Cornolti
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "my.h"
#include "get_next_line.h"
#include "syntax.h"

int		redir_output(char *file)
{
  int		fd;

  if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
    perror(file);
  return (fd);
}

int		double_redir_output(char *file)
{
  int		fd;

  if ((fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
    perror(file);
  return (fd);
}

int		redir_input(char *file)
{
  int		fd;

  if ((fd = open(file, O_RDONLY)) < 0)
    perror(file);
  return (fd);
}

int		double_redir_input(char *end)
{
  int		pipefd[2];
  char		*gnl;

  if (pipe(pipefd));
  my_putstr("? ");
  while ((gnl = get_next_line(0)))
    {
      if (my_strcmp(gnl, end))
	{
	  my_putfd(pipefd[1], gnl);
	  my_putfd(pipefd[1], "\n");
	  my_putstr("? ");
	}
    }
  close(pipefd[1]);
  return (pipefd[0]);
}
