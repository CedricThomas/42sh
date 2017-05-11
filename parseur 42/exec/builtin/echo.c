/*
** echo.c for builtin in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur 42/exec/builtin
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May 11 13:22:48 2017 Thibaut Cornolti
** Last update Thu May 11 16:37:44 2017 Thibaut Cornolti
*/

#include "syntax.h"
#include "exec.h"
#include "my.h"

void		builtin_echo(t_command *cmd, t_status *status, t_info *info)
{
  int		i;

  i = 0;
  UNUSED(status);
  UNUSED(info);
  while (cmd->argv[++i])
    {
      my_putstr(cmd->argv[i]);
      if (cmd->argv[i + 1])
	my_putchar(' ');
    }
  my_putchar('\n');
}
