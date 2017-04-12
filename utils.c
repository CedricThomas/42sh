/*
** utils.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell1
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Wed Jan  4 11:16:16 2017 Thibaut Cornolti
** Last update Thu Mar 23 14:03:49 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "my.h"
#include "sh.h"

int		check_slash(char *s)
{
  int		i;

  i = -1;
  while (s[++i])
    if (s[i] == '/')
      return (1);
  return (0);
}

int		check_alphanum(char *s)
{
  int		i;

  i = -1;
  while (s[++i])
    if (!((s[i] >= '0' && s[i] <= '9') ||
	  (s[i] >= 'a' && s[i] <= 'z') ||
	  (s[i] >= 'A' && s[i] <= 'Z') ||
	  s[i] == '_'))
      return (0);
  return (1);
}

int		my_arglen(char **av)
{
  int		i;

  i = -1;
  while (av[++i]);
  return (i);
}

void		assist_add_env(char *p, char *s, char ***ae)
{
  char		**fav;

  if ((fav = malloc(sizeof(char *) * 4)) == NULL)
    return ;
  fav[0] = "setenv";
  fav[1] = my_strdup(p);
  if ((fav[2] = malloc(sizeof(char) * PATH_MAX)) == NULL)
    return ;
  my_strcpy(fav[2], s);
  fav[3] = 0;
  fct_setenv(fav, ae);
}

void		set_lr(int ret, char ***ae)
{
  assist_add_env("LAST_RETURN", my_int_to_str(ret, NULL), ae);
}
