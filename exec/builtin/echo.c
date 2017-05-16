/*
** echo.c for builtin in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur 42/exec/builtin
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May 11 13:22:48 2017 Thibaut Cornolti
** Last update Tue May 16 19:51:23 2017 Thibaut Cornolti
*/

#include <stdio.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

void		builtin_echo(t_command *cmd, t_status *status, t_info *info)
{
  int		i;

  i = 0;
  UNUSED(status);
  info->exit_value = 0;
  while (cmd->argv[++i])
    {
      printf("%s", cmd->argv[i]);
      if (cmd->argv[i + 1])
	printf("%s", " ");
    }
  printf("%s", "\n");
}
