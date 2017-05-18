/*
** get_var.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh/exec/setup
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Thu May 18 14:27:54 2017 Bastien
** Last update Thu May 18 18:20:16 2017 Bastien
*/

#include <stdio.h>
#include <string.h>
#include "syntax.h"
#include "exec.h"
#include "my_alloc.h"
#include "my.h"

static int	error_var(char *str)
{
  int	len;

  len = my_cstrlen(str, '$');
  printf("%s: Undefined variable.\n", str + len +1);
  return (1);
}

static int	verify_var(t_info *info, t_command *cmd, int pos)
{
  int	i;
  int	len;
  char	*temp;

  len = my_cstrlen(cmd->argv[pos], '$');
  i = my_vartablen(info->var);
  while (--i >= 0)
    if (!strncmp(cmd->argv[pos] + len + 1,
		 info->var[i].name, strlen(info->var[i].name)))
      {
	if (!(temp = my_alloc(sizeof(char) *
			      (strlen(cmd->argv[pos]) -
			       strlen(info->var[i].name) +
			       strlen(info->var[i].value) + 1))))
	  return (1);
	my_tag_alloc(temp, "tree", 0);
	strncat(temp, cmd->argv[pos], len - 1);
	strncat(temp, info->var[i].value, strlen(info->var[i].value));
	strncat(temp, cmd->argv[pos] + len + strlen(info->var[i].value),
		strlen(info->var[i].value) - len - strlen(info->var[i].name));
	my_vfree((void **)(&cmd->argv[pos]), NULL);
	cmd->argv[pos] = temp;
	return (0);
      }
  return (error_var(cmd->argv[pos]));
}

static int	check_var(t_command *cmd, t_info *info)
{
  int		i;

  i = -1;
  while (cmd->argv[++i])
    if (is_in('$', cmd->argv[i]))
      if (verify_var(info, cmd, i))
	return (1);
  return (0);
}

t_command	*get_var(t_command *cmd, t_info *info)
{
  if (!info->var)
    return (cmd);
  if (check_var(cmd, info))
    return (NULL);
  return (cmd);
}
