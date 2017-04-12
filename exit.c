/*
** exit.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell1
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Sat Jan  7 19:28:31 2017 Thibaut Cornolti
** Last update Fri Apr  7 16:08:11 2017 Thibaut Cornolti
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "sh.h"

static int	pure_exit(char **s)
{
  int		i;
  int		j;
  int		par;
  char		*result;

  if ((result = malloc(sizeof(char) * my_strlen(*s) + 2)) == NULL)
    return (1);
  i = -1 + 0 * (j = -1);
  par = 0;
  while ((*s)[++i])
    {
      if ((*s)[i] == '(')
	par++;
      else if ((*s)[i] == ')')
	par--;
      else
	result[++j] = (*s)[i];
    }
  result[j + 1] = 0;
  if (par > 0)
    return (my_puterror("Too many ('s.\n"));
  else if (par < 0)
    return (my_puterror("Too many )'s.\n"));
  *s = result;
  return (1);
}

void		fct_exit(char **av, char ***ae)
{
  if (av[1] == 0)
    {
      if (isatty(0))
	my_putstr("exit\n");
      assist_add_env("LAST_RETURN", "0", ae);
      assist_add_env("IS_EXIT_NEXT", "1", ae);
    }
  else
    if (pure_exit(&(av[1])))
      {
	if (isatty(0))
	  my_putstr("exit\n");
	assist_add_env("LAST_RETURN", av[1], ae);
	assist_add_env("IS_EXIT_NEXT", "1", ae);
      }
    else
      assist_add_env("LAST_RETURN", "1", ae);
}
