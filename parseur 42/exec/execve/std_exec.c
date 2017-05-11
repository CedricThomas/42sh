/*
** std_exec.c for 42sh in /home/cedric/delivery/PSU/PSU_2016_42sh/parseur 42
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed May 10 22:32:29 2017 
** Last update Thu May 11 17:23:37 2017 
*/
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "syntax.h"
#include "exec.h"

void	simple_exec(t_command *cmd, t_status *status, t_info *info)
{
  char	*path;

  (void)(status);
  //my_printf("%s\n", my_pathfinder(cmd, info));
  path = my_pathfinder(cmd, info);
  if (path && execve(path, cmd->argv, info->env))
    {
      my_printf("%d\n", errno);
      perror(cmd->path);
    }
}
