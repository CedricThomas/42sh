/*
** tools.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell2
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu Apr  6 10:52:34 2017 Thibaut Cornolti
** Last update Sun Apr  9 13:13:34 2017 Thibaut Cornolti
*/

#include <sys/wait.h>
#include <signal.h>
#include "sh.h"
#include "pars.h"
#include "my.h"

void		kill_fork(t_ll *ll)
{
  while (ll && ll->token != TOK_SEPA && ll->token)
    {
      if (ll->fork_pid != -1)
	{
	  kill(ll->fork_pid, SIGINT);
	  ll->fork_pid = -1;
	}
      ll = ll->prev;
    }
}

void		wait_fork(t_ll *ll, char ***ae)
{
  int		ret;
  int		i;

  i = 0;
  if (ll->token == TOK_SEPA)
    {
      while ((ll && ll->token && ll->token != TOK_SEPA) || i == 0)
	{
	  i = 1;
	  if (ll->fork_pid != -1)
	    {
	      waitpid(ll->fork_pid, &ret, 0);
	      commander_error(ret, ae);
	      kill_fork(ll->prev);
	      ll->fork_pid = -1;
	    }
	  ll = ll->prev;
	}
    }
}

int		is_builtin(char *builtin)
{
  static char	*builts[5] = {"cd", "env", "setenv",
			     "unsetenv", "exit"};
  int		i;

  i = -1;
  while (++i < 5)
    if (!my_strcmp(builts[i], builtin))
      return (1);
  if (!my_strncmp(builtin, "exit(", 5))
    return (1);
  return (0);
}
