/*
** alias.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh/parseur42/exec/builtin
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Mon May 15 15:48:20 2017 Bastien
** Last update Tue May 16 13:26:00 2017 Bastien
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

void		show_cmd(t_info *info, char *str, int size)
{
  int	i;

  i = -1;
  while (size && info->alias[++i].link)
    {
      if (str && !strcmp(info->alias[i].link, str))
	{
	  printf("%s\n", info->alias[i].value);
	  return ;
	}
      else if (!str)
	printf("%s\t%s\n", info->alias[i].link, info->alias[i].value);
    }
}

int		verify_exist(t_info *info, char *str, char *value)
{
  int	i;

  i = -1;
  while (info->alias && info->alias[++i].link)
    if (!my_strcmp(info->alias[i].link, str))
      {
	info->alias[i].value = value;
	return (0);
      }
  return (1);
}

char	*get_whole_alias(t_command *cmd)
{
  int	i;
  char	*temp;

  i = 1;
  temp = NULL;
  while (cmd->argv[++i])
    {
      temp = my_strcatdup(temp, cmd->argv[i], 1);
      if (cmd->argv[i + 1])
	temp = my_strcatdup(temp, " ", 1);
    }
  return (temp);
}

void		builtin_alias(t_command *cmd, t_status *status, t_info *info)
{
  int		nb_arg;
  char		*temp;
  static int	size = 0;

  UNUSED(status);
  info->exit_value = 0;
  nb_arg = my_strtablen(cmd->argv);
  if (nb_arg <= 2)
    {
      show_cmd(info, cmd->argv[1], size);
      return ;
    }
  temp = get_whole_alias(cmd);
  if (verify_exist(info, cmd->argv[1], temp))
    {
      if (!(info->alias = realloc(info->alias, sizeof(t_alias) * (size + 2))))
	return ;
      memset(&info->alias[size], 0, sizeof(t_alias) * 2);
      info->alias[size].link = strdup(cmd->argv[1]);
      info->alias[size].value = temp;
      size += 1;
    }
}
