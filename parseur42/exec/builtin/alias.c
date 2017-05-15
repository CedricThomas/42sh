/*
** alias.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh/parseur42/exec/builtin
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Mon May 15 15:48:20 2017 Bastien
** Last update Mon May 15 18:46:21 2017 Bastien
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fnmatch.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static int	my_strtablen(char **tab)
{
  int	i;

  i = -1;
  while (tab && tab[++i]);
  return (i < 0 ? 0 : i);
}

void		show_cmd(t_info *info, char *str)
{
  int	i;

  i = -1;
  while (info->alias[++i].link)
    if (!strcmp(info->alias[i].link, str))
      {
	printf("%s=%s\n", info->alias[i].link, info->alias[i].value);
	return ;
      }
}

void		builtin_alias(t_command *cmd, t_status *status, t_info *info)
{
  int		i;
  static int	size = 0;

  (void)status;
  if (my_strtablen(cmd->argv) != 2)
    return ;
  i = my_cstrlen(cmd->argv[1], '=');
  if (fnmatch("*=\"*\"", cmd->argv[1], 0) || cmd->argv[1][i] != '=')
    {
      if (size)
	show_cmd(info, cmd->argv[1]);
      return ;
    }
  if (!(info->alias = realloc(info->alias, sizeof(t_alias) * (size + 2))))
    return ;
  memset(&info->alias[size], 0, sizeof(t_alias) * 2);
  cmd->argv[1][i] = 0;
  info->alias[size].link = strdup(cmd->argv[1]);
  cmd->argv[1][i] = '=';
  info->alias[size].value = strdup(cmd->argv[1] + i + 1);
  size += 1;
}
