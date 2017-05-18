/*
** alias_len.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Wed May 17 22:33:50 2017 Bastien
** Last update Thu May 18 10:24:56 2017 Bastien
*/

#include "syntax.h"
#include "exec.h"

int      my_strtablen(char **tab)
{
  int   i;

  i = -1;
  while (tab && tab[++i]);
  return (i < 0 ? 0 : i);
}

int	my_aliastablen(t_alias *alias)
{
  int	i;

  i = -1;
  while (alias && alias[++i].link);
  return (i < 0 ? 0 : i);
}
