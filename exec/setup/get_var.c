/*
** get_var.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh/exec/setup
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Thu May 18 14:27:54 2017 Bastien
** Last update Fri May 19 23:47:41 2017 Bastien
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "syntax.h"
#include "exec.h"
#include "my_alloc.h"
#include "my.h"

static int	error_var(char *str)
{
  int	i;

  i = my_cstrlen(str, '$');
  while (str && ((str[++i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')))
    write(1, &str[i], 1);
  printf(": Undefined variable.\n");
  return (1);
}

static int	swap_var(t_info *info, t_command *cmd, int pos, int i)
{
  char		*temp;
  int		len;

  len = my_cstrlen(cmd->argv[pos], '$');
  if (!(temp = my_alloc(sizeof(char) *
			(my_strlen(cmd->argv[pos]) -
			 my_strlen(info->var[i].name) +
			 my_strlen(info->var[i].value)))))
    return (1);
  my_tag_alloc(temp, "tree", 0);
  temp = (len > 0) ? strncat(temp, cmd->argv[pos], len) : temp;
  temp = strncat(temp, info->var[i].value, my_strlen(info->var[i].value));
  temp = strncat(temp, cmd->argv[pos] + len + my_strlen(info->var[i].name) + 1,
		 my_strlen(cmd->argv[pos]) - len -
		 my_strlen(info->var[i].name));
  my_vfree((void **)(&cmd->argv[pos]), NULL);
  cmd->argv[pos] = temp;
  return (0);
}

static int	verify_var(t_info *info, t_command *cmd, int pos)
{
  int		i;
  int		len;

  if (info->var)
    {
      len = my_cstrlen(cmd->argv[pos], '$');
      if (!cmd->argv[pos][len + 1])
	return (0);
      i = my_vartablen(info->var);
      while (--i >= 0)
	if (!strcmp(cmd->argv[pos] + len + 1, info->var[i].name))
	  return (swap_var(info, cmd, pos, i));
    }
  return (error_var(cmd->argv[pos]));
}

static int	check_var(t_command *cmd, t_info *info)
{
  int		i;

  i = -1;
  while (cmd->argv[++i])
    if (is_in('$', cmd->argv[i]) && strlen(cmd->argv[i]) > 1)
      if (verify_var(info, cmd, i))
	return (1);
  return (0);
}

t_command	*get_var(t_command *cmd, t_info *info)
{
  int	len;

  if (is_in('$', cmd->path) && strlen(cmd->path) > 1)
    {
      len = my_strtablen(cmd->argv);
      cmd->argv[len] = cmd->path;
      if (verify_var(info, cmd, len))
	return (NULL);
      my_vfree((void **)(&cmd->path), NULL);
      cmd->path = cmd->argv[len];
      cmd->argv[len] = 0;
    }
  if (check_var(cmd, info))
    return (NULL);
  return (cmd);
}
