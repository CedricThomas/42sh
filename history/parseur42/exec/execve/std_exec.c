/*
** std_exec.c for 42sh in /home/cedric/delivery/PSU/PSU_2016_42sh/parseur 42
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed May 10 22:32:29 2017 
** Last update Fri May 12 12:12:26 2017 
*/
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static void	check_errno(char *str)
{
  my_puterror(str);
  my_puterror(": ");
  if (ENOEXEC == errno)
    my_perror(str, "cannot execute binary file\n");
  else
    perror(str);
  exit(1);
}

void	simple_exec(t_command *cmd, t_status *status, t_info *info)
{
  char	*path;

  (void)(status);
  path = my_pathfinder(cmd, info);
  if (path && execve(path, cmd->argv, info->env))
    check_errno(cmd->path);
}
