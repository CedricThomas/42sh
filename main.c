/*
** main.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell1
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon Jan  2 15:56:09 2017 Thibaut Cornolti
** Last update Thu Apr 13 12:18:19 2017 Thibaut Cornolti
*/

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "sh.h"
#include "my.h"

void		prompt()
{
  char		*path;

  if (!isatty(0))
    return ;
  if ((path = malloc(sizeof(char) * PATH_MAX)) == NULL)
    return ;
  getcwd(path, PATH_MAX);
  my_putstr("\033[1m");
  my_putstr(path);
  my_putstr("\033[0m> ");
  free(path);
}

void		sig(int s)
{
  static int	enable = 1;

  if (s == -1)
    signal(SIGINT, sig);
  else if (s == -2)
    enable = 1;
  else if (s == -3)
    enable = 0;
  else if (s == SIGINT && enable)
    {
      my_putstr("\r");
      prompt();
      my_putstr("  \n");
      prompt();
    }
  else
    my_putstr("\n");
}

static char	**my_strdup2D(char **ae)
{
  char		**res;
  int		i;

  i = -1;
  while (ae[++i]);
  if ((res = malloc(sizeof(char *) * (i + 1))) == NULL)
    return (ae);
  i = -1;
  while (ae[++i])
    res[i] = my_strdup(ae[i]);
  res[i] = NULL;
  if (my_getenv(res, "PATH") == NULL)
    assist_add_env("PWD", getcwd(NULL, PATH_MAX), &res);
  return (res);
}

int		main(int ac, char **av, char **ae)
{
  char		*gnl;
  int		ret_value;

  (void) av;
  (void) ac;
  sig(-1);
  prompt(ae);
  ret_value = 0;
  ae = my_strdup2D(ae);
  assist_add_env("LAST_RETURN", "0", &ae);
  gnl = my_sh(&ae);
  if (isatty(0) && (gnl == NULL))
    my_putstr("exit\n");
  ret_value = my_getnbr(my_getenv(ae, "LAST_RETURN"));
  free_argv(&ae);
  return ((isatty(0)) ? 0 : ret_value);
}
