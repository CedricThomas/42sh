/*
** std_exec.c for 42sh in /home/cedric/delivery/PSU/PSU_2016_42sh/parseur 42
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed May 10 22:32:29 2017 
** Last update Wed May 10 22:38:58 2017 
*/
#include <stdio.h>
#include <unistd.h>
#include "syntax.h"
#include "exec.h"

void	simple_exec(t_command *cmd, t_status *status, t_info *info)
{
  (void)(status);
  if (execvpe(cmd->path, cmd->argv, info->env))
    perror(cmd->path);
}
