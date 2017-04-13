/*
** builtin.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell1
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Wed Jan  4 09:27:50 2017 Thibaut Cornolti
** Last update Thu Mar 23 14:04:17 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "my.h"
#include "sh.h"

static char	*format_exit(char *cmd)
{
  char		*res;
  int		i;
  int		j;
  int		p;

  if ((res = malloc(sizeof(char) * my_strlen(cmd) + 4)) == NULL)
    return (cmd);
  i = -1;
  j = -1;
  p = 0;
  while (cmd[++i])
    if (cmd[i] == '(' && !p)
      {
	res[++j] = ' ';
	res[++j] = cmd[i];
	p = 1;
      }
    else
      res[++j] = cmd[i];
  res[++j] = 0;
  return (res);
}

static void	init_fct(void (*fct[6])(), char *bt[6])
{
  int		i;

  i = -1;
  fct[++i] = fct_cd;
  bt[i] = "cd";
  fct[++i] = fct_env;
  bt[i] = "env";
  fct[++i] = fct_setenv;
  bt[i] = "setenv";
  fct[++i] = fct_unsetenv;
  bt[i] = "unsetenv";
  fct[++i] = fct_exit;
  bt[i] = "exit";
  bt[++i] = 0;
}

void		builtin(char *cmd, char ***ae)
{
  void		(*fct[6])();
  char		*bt[6];
  int		i;
  char		**argv;

  init_fct(fct, bt);
  i = -1;
  if (!my_strncmp(cmd, "exit(", 5))
    cmd = format_exit(cmd);
  argv = get_argv(my_strdup(cmd), ' ');
  while (bt[++i])
    if (!my_strcmp(argv[0], bt[i]))
      {
	fct[i](argv, ae);
	return ;
      }
  if (!bt[i])
    {
      assist_add_env("LAST_RETURN", "1", ae);
      my_msg(cmd, NULL, 127);
    }
  free_argv(&argv);
}
