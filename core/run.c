/*
** run.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell1
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Wed Jan 11 23:26:57 2017 Thibaut Cornolti
** Last update Thu Apr 13 12:23:27 2017 Thibaut Cornolti
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "sh.h"
#include "pars.h"

static void	check_exit(t_ll *ll, char ***ae)
{
  char		*exited;

  exited = my_getenv(*ae, "IS_EXIT_NEXT");
  if (ll->token == TOK_PIPE && exited &&
      !my_strcmp(exited, "1"))
    assist_add_env("IS_EXIT_NEXT", "0", ae);
  if (ll->token == TOK_SEPA && ll->next)
    set_lr(0, ae);
}

static int	check_cond_token(t_ll *ll, char **ae)
{
  int		ret_value;

  ret_value = my_getnbr(my_getenv(ae, "LAST_RETURN"));
  return ((ll->prev->token != TOK_DPIP && ll->prev->token != TOK_DESP) ||
	  (ll->prev->token == TOK_DPIP && ret_value) ||
	  (ll->prev->token == TOK_DESP && !ret_value));
}

static void	my_sh_run(t_ll *ll, char ***ae)
{
  char		**argv;

  argv = get_argv(ll->cmd, ' ');
  if (argv && argv[0])
    {
      if (redirect_open(ll) < 0)
	set_lr(my_msg(ll->next->cmd, NULL, -3) + 4, ae);
      else if (check_cond_token(ll, *ae))
	{
	  if (is_builtin(argv[0]))
	    builtin(ll->cmd, ae);
	  else
	    commander(ll, ae);
	}
      redirect_close(ll);
    }
  free_argv(&argv);
}

static void	my_sh_pre_run(t_ll *ll, char ***ae)
{
  if (check_syntax(ll))
    set_lr(1, ae);
  else
    while (ll)
      {
	ll->cmd = my_epure_str(ll->cmd);
	if (ll->prev->token == TOK_PIPE ||
	    ll->prev->token == TOK_SEPA ||
	    ll->prev->token == TOK_DPIP ||
	    ll->prev->token == TOK_DESP ||
	    !ll->prev->token)
	  my_sh_run(ll, ae);
	wait_fork(ll, ae);
	check_exit(ll, ae);
	ll = ll->next;
      }
}

char		*my_sh(char ***ae)
{
  char		*gnl;
  t_ll		*ll;
  char		*exited;

  while ((gnl = get_next_line(0)) != NULL)
    {
      ll = my_pars(my_epure_str(gnl))->next;
      sig(-3);
      my_sh_pre_run(ll, ae);
      exited = my_getenv(*ae, "IS_EXIT_NEXT");
      if (exited && !my_strcmp(exited, "1"))
	break ;
      prompt();
      sig(-2);
    }
  return (gnl);
}
