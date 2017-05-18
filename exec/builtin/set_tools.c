/*
** set_tools.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Thu May 18 18:22:40 2017 Bastien
** Last update Thu May 18 19:38:27 2017 Bastien
*/

#include "syntax.h"
#include "exec.h"

int      my_vartablen(t_var *var)
{
  int           i;

  i = -1;
  while (var && var[++i].name);
  return (i < 0 ? 0 : i);
}

void	sort_var(t_info *info)
{
  int	i;
  t_var	temp;

  i = 0;
  while (info->var && info->var[++i].name)
    {
      if (strcmp(info->var[i].name, info->var[i - 1].name) < 0)
	{
	  temp.name = info->var[i].name;
	  temp.value = info->var[i].value;
	  info->var[i].name = info->var[i - 1].name;
	  info->var[i].value = info->var[i - 1].value;
	  info->var[i - 1].name = temp.name;
	  info->var[i - 1].value = temp.value;
	  i = 0;
	}
    }
}
