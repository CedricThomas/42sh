/*
** misc.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Thu Jan  5 21:14:52 2017 
** Last update Sat Apr  1 15:13:19 2017 Cédric Thomas
*/
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include "my.h"
#include "mysh.h"

t_fd	myfds(int in, int out)
{
  t_fd	my_fd;

  my_fd.in = in;
  my_fd.out = out;
  my_fd.next = NULL;
  my_fd.prev = NULL;
  return (my_fd);
}

t_toexec	mytoexec(char **argv, char **env)
{
  int		i;
  t_toexec	exec;

  i = -1;
  exec.argv = argv;
  while (argv[++i]);
  exec.argc = i;
  exec.env = env;
  return (exec);
}

void		*multi_free(int size, ...)
{
  int		i;
  va_list       ptr_list;
  void		*ptr;

  i = -1;
  va_start(ptr_list, size);
  while (++ i < size)
    {
      ptr = va_arg(ptr_list, void *);
      free(ptr);
    }
  va_end(ptr_list);
  return (NULL);
}

int		multi_close(int size, ...)
{
  int		i;
  va_list       fd_list;
  int		fd;

  i = -1;
  va_start(fd_list, size);
  while (++ i < size)
    {
      fd = va_arg(fd_list, int);
      close(fd);
    }
  va_end(fd_list);
  return (0);
}
