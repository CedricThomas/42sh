/*
** builtins.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May 18 23:57:02 2017 Thibaut Cornolti
** Last update Sun May 21 00:32:20 2017 Cédric THOMAS
*/

#include <stdlib.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static int	error_repeat(t_command *cmd)
{
  int		argc;

  argc = -1;
  while (cmd->argv[++argc]);
  if (argc <= 2)
    {
      my_puterror("repeat: Too few arguments.\n");
      return (1);
    }
  argc = -1;
  while (cmd->argv[1][++argc])
    if (!is_betw('0', cmd->argv[1][argc], '9'))
      {
  	my_puterror("repeat: Badly formed number.\n");
  	return (1);
      }
  return (0);
}

void		builtin_repeat(t_command *cmd, t_status *status, t_info *info)
{
  char		*command;
  int		i;
  int		count;

  UNUSED(status);
  UNUSED(info);
  if (error_repeat(cmd))
    {
      info->exit_value = 1;
      return ;
    }
  count = atoi(cmd->argv[1]) + 1;
  command = my_strdup(cmd->argv[2]);
  i = 2;
  while (cmd->argv[++i])
    {
      command = my_strcatdup(command, " ", 1);
      command = my_strcatdup(command, cmd->argv[i], 1);
    }
  while (--count)
    my_system(my_strdup(command), getter_system(NULL));
}
