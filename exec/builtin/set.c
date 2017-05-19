/*
** set.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Wed May 17 16:07:30 2017 Bastien
** Last update Thu May 18 20:03:23 2017 Bastien
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static int	verify_set(t_command *cmd)
{
  int		i;

  i = 0;
  while (cmd->argv[++i])
    if ((cmd->argv[i][0] < 'A' || cmd->argv[i][0] > 'Z') &&
	(cmd->argv[i][0] < 'a' || cmd->argv[i][0] > 'z'))
      {
	printf("set: Variable name must begin with a letter.\n");
	return (0);
      }
  return (1);
}

static void	replace_var(char *str, t_var *var)
{
  unsigned int	len;

  len = my_cstrlen(str, '=') + 1;
  free(var->value);
  if (len == strlen(str))
    return ;
  var->value = strdup(str + len);
}

static void	add_var(char *str, t_info *info)
{
  int		size;
  unsigned int	len;

  size = my_vartablen(info->var);
  if (!(info->var = realloc(info->var, sizeof(t_var) * (size + 2))))
    return ;
  memset(&info->var[size], 0, sizeof(t_var) * 2);
  if ((len = my_cstrlen(str, '=')) == strlen(str))
    {
      info->var[size].name = strdup(str);
      return ;
    }
  len = my_cstrlen(str, '=');
  str[len] = 0;
  info->var[size].name = strdup(str);
  str[len] = '=';
  info->var[size].value = strdup(str + len + 1);  
}

static int	display_cmd(t_command *cmd, t_info *info)
{
  int	i;

  i = -1;
  if (cmd->argv[1])
    return (0);
  printf("\tFaut la dernière commande ici, mais c'est le zoo\n_\n");
  while (info->var && info->var[++i].name)
    {
      printf("%s\t", info->var[i].name);
      if (info->var[i].value)
	printf("%s", info->var[i].value);
      printf("\n");
    }
  return (1);
}

void		builtin_set(t_command *cmd, t_status *status, t_info *info)
{
  int		i;
  unsigned int	len;
  int		j;

  (void)status;
  i = 0;
  if (!verify_set(cmd))
    return ;
  if (display_cmd(cmd, info))
    return ;
  while (cmd->argv[++i])
    {
      j = -1;
      while (info->var && info->var[++j].name)
	if ((len = my_cstrlen(cmd->argv[i], '=')) == strlen(info->var[j].name)
	    && !strncmp(cmd->argv[i], info->var[j].name, len))
	  {
	    replace_var(cmd->argv[i], &info->var[j]);
	    break ;
	  }
      if (!info->var || !info->var[j].name)
	add_var(cmd->argv[i], info);
    }
  sort_var(info);
}
