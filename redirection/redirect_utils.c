/*
** redirect_utils.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell2
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Wed Apr  5 18:12:51 2017 Thibaut Cornolti
** Last update Sun Apr  9 01:44:36 2017 Thibaut Cornolti
*/

#include "sh.h"
#include "pars.h"

int		redirect_open(t_ll *ll)
{
  static char	toks[5] = {TOK_SRDD, TOK_SRDG,
			   TOK_DRDD, TOK_DRDG, TOK_PIPE};
  static int	(*fct[5])(t_ll *, int) = {&fct_srdd,
					  &fct_srdg,
					  &fct_drdd,
					  &fct_drdg,
					  &fct_pipe};
  int		i;

  if (ll->token == TOK_SRDG || ll->token == TOK_DRDG)
    {
      if (ll->prev->token == TOK_PIPE)
	fct_pipe(ll->prev, 2);
      i = -1;
      while (++i < 5)
  	if (toks[i] == ll->next->token && fct[i](ll->next, 0) == -1)
	  return (-1);
    }
  else if (ll->prev->token == TOK_PIPE)
    fct_pipe(ll, 2);
  i = -1;
  while (++i < 5)
    if (toks[i] == ll->token)
      return (fct[i](ll, 0));
  return (0);
}

void		redirect_close(t_ll *ll)
{
  static char	toks[5] = {TOK_SRDD, TOK_SRDG,
			   TOK_DRDD, TOK_DRDG,
			   TOK_PIPE};
  static int	(*fct[5])(t_ll *, int) =
    {&fct_srdd, &fct_srdg, &fct_drdd,
     &fct_drdg, &fct_pipe};
  int		i;

  if (ll->token == TOK_SRDG || ll->token == TOK_DRDG)
    {
      if (ll->prev->token == TOK_PIPE)
	fct_pipe(ll->prev, 3);
      i = -1;
      while (++i < 5)
  	if (toks[i] == ll->next->token)
	  fct[i](ll->next, 1);
    }
  else if (ll->prev->token == TOK_PIPE)
    fct_pipe(ll, 3);
  i = -1;
  while (++i < 5)
    if (toks[i] == ll->token)
      fct[i](ll, 1);
  return ;
}
