/*
** set_tools.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Thu May 18 18:22:40 2017 Bastien
** Last update Thu May 18 18:24:01 2017 Bastien
*/

#include "syntax.h"
#include "exec.h"

int      my_vartablen(t_var *var)
{
  int           i;

  i = -1;
  while (var && var[++i].name);
  return (i < 0 ? 0 : 1);
}
