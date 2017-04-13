/*
** check.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell2
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Fri Apr  7 16:40:37 2017 Thibaut Cornolti
** Last update Thu Apr 13 12:12:21 2017 Thibaut Cornolti
*/

#include "sh.h"
#include "pars.h"
#include "my.h"

static int	check_lost_token(t_ll *ll)
{
  while (ll)
    {
      if (!ll->next || !ll->next->cmd[0])
	{
	  if (ll->token == TOK_PIPE)
	    return (1 + my_puterror("Invalid null command.\n"));
	  else if (ll->token != TOK_SEPA)
	    return (1 + my_puterror("Missing name for redirect.\n"));
	}
      ll = ll->next;
    }
  return (0);
}

static int	check_ambiguous_output(t_ll *ll)
{
  while (ll)
    {
      if ((ll->token == TOK_SRDD || ll->token == TOK_DRDD) &&
	  ll->next && ll->next->token != TOK_SEPA)
	return (1 + my_puterror("Ambiguous output redirect.\n"));
      ll = ll->next;
    }
  return (0);
}

static int	check_ambiguous_input(t_ll *ll)
{
  while (ll)
    {
      if ((ll->token == TOK_SRDG || ll->token == TOK_DRDG) &&
	  ll->next &&
	  (ll->next->token == TOK_SRDG || ll->token == TOK_DRDG))
	return (1 + my_puterror("Ambiguous input redirect.\n"));
      if (ll->prev->token == TOK_PIPE &&
	  (ll->token == TOK_SRDG || ll->token == TOK_DRDG))
	return (1 + my_puterror("Ambiguous input redirect.\n"));
      ll = ll->next;
    }
  return (0);
}

int		check_syntax(t_ll *ll)
{
  if (check_lost_token(ll))
    return (1);
  if (check_ambiguous_output(ll))
    return (1);
  if (check_ambiguous_input(ll))
    return (1);
  return (0);
}
