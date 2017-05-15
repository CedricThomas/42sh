/*
** alias.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh/parseur42/exec/builtin
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Mon May 15 15:48:20 2017 Bastien
** Last update Mon May 15 17:07:48 2017 Bastien
*/

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

static int	alias_size(t_alias *tab)
{
  int	       i;

  i = -1;
  while (tab && tab[++i].link);
  return (i < 0 ? 0 : i);
}

void		builtin_alias(t_command *cmd, t_status *status, t_info *info)
{
  int		i;
  int		size;

  (void)status;
  if (my_strtablen(cmd->argv) != 2)
    return ;
  if (fnmatch("*=\"*\"", cmd->argv[1], 0))
    return ;
  i = my_cstrlen(cmd->argv[1], '=');
  if (cmd->argv[1][i] != '=')
    return ;
  size = (!info->alias) ? 2 : 1;
  if (!(info->alias = realloc(info->alias, alias_size(info->alias) + size)))
    return ;
  cmd->argv[1][i] = 0;
  size = alias_size(info->alias);
  info->alias[size].link = strdup(cmd->argv[1]);
  cmd->argv[1][i] = '=';
  info->alias[size].value = strdup(cmd->argv[1] + i + 1);  
}
