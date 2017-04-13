/*
** fct.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell1
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Wed Jan  4 09:36:21 2017 Thibaut Cornolti
** Last update Thu Mar 23 14:04:03 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "my.h"
#include "sh.h"

static void	add_env(char **av, char ***ae)
{
  char		**res;
  char		*r;
  int		i;

  i = -1;
  while ((*ae)[++i]);
  if ((res = malloc(sizeof(char *) * (i + 2))) == NULL ||
      (r = malloc(sizeof(char) * my_strlen(av[1])
		  + my_strlen(av[2]) + 3)) == NULL)
    return ;
  i = -1;
  while ((*ae)[++i])
    res[i] = (*ae)[i];
  res[i] = r;
  my_strcpy(res[i], av[1]);
  my_strcat(res[i], "=");
  if (my_arglen(av) == 3)
    my_strcat(res[i], av[2]);
  res[i + 1] = NULL;
  free(*ae);
  *ae = res;
}

void		fct_setenv(char **av, char ***ae)
{
  char		*s;
  int		i;

  if (my_arglen(av) < 2)
    fct_env(av, ae);
  else if (my_arglen(av) > 3)
    set_lr(1 + my_puterror("setenv: Too many arguments.\n"), ae);
  else if (!check_alphanum(av[1]))
    set_lr(1 + my_puterror("setenv: Variable name must contain \
alphanumeric characters.\n"), ae);
  else if ((i = my_igetenv(*ae, av[1])) != -1)
    {
      if ((s = malloc(sizeof(char) *
		      (my_strlen(av[1])
		       + my_strlen(av[2]) + 5))) == NULL)
	return ;
      my_strcpy(s, av[1]);
      my_strcat(s, "=");
      my_strcat(s, av[2]);
      (*ae)[i] = s;
    }
  else
    add_env(av, ae);
}

static void	del_env(char *s, char ***ae)
{
  char		**res;
  char		*r;
  int		i;
  int		j;

  i = -1;
  while ((*ae)[++i]);
  if ((res = malloc(sizeof(char *) * (i + 2))) == NULL)
    return ;
  i = -1;
  j = -1;
  while ((*ae)[++i])
    {
      r = my_strdup((*ae)[i]);
      if (my_strcmp(getenv_pa(r), s))
	res[++j] = (*ae)[i];
      free(r);
    }
  res[++j] = NULL;
  free(*ae);
  *ae = res;
}

void		fct_unsetenv(char **av, char ***ae)
{
  int		i;

  if (my_arglen(av) < 2)
    {
      my_puterror("unsetenv: Too few arguments.\n");
      assist_add_env("LAST_RETURN", "1", ae);
    }
  else
    {
      i = 0;
      while (av[++i])
	del_env(av[i], ae);
    }
}

void		fct_env(char **av, char ***ae)
{
  int		i;

  i = -1;
  (void) av;
  while ((*ae)[++i])
    {
      my_putstr((*ae)[i]);
      my_putchar('\n');
    }
}
