/*
** std_exec.c for 42sh in /home/cedric/delivery/PSU/PSU_2016_42sh/parseur 42
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed May 10 22:32:29 2017 
** Last update Thu May 18 09:31:05 2017 maje
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
    my_perror(str, "Exec format error. Binary file not executable.\n");
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
