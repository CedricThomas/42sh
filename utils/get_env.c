/*
** get_env.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell1
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon Jan  2 17:01:44 2017 Thibaut Cornolti
** Last update Thu Mar 23 14:04:46 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "my.h"
#include "sh.h"

char		*getenv_var(char *s)
{
  int		i;

  i = -1;
  while (s[++i])
    if (s[i] == '=')
      return (s + i + 1);
  return (s);
}

char		*getenv_pa(char *s)
{
  int		i;

  i = -1;
  while (s[++i])
    if (s[i] == '=')
      s[i] = 0;
  return (s);
}

char		*my_getenv(char **ae, char *s)
{
  int		i;
  char		*tmp;

  i = -1;
  while (ae[++i])
    {
      tmp = my_strdup(ae[i]);
      if (!my_strcmp(getenv_pa(tmp), s))
	{
	  free(tmp);
	  return (getenv_var(ae[i]));
	}
      free(tmp);
    }
  return (NULL);
}

int		my_igetenv(char **ae, char *s)
{
  int		i;

  i = -1;
  while (ae[++i])
    if (!my_strcmp(getenv_pa(my_strdup(ae[i])), s))
      return (i);
  return (-1);
}
