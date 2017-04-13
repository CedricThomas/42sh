/*
** parse.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell2
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Tue Mar 14 17:44:12 2017 Thibaut Cornolti
** Last update Sun Apr  9 13:14:09 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "sh.h"
#include "pars.h"

static char	get_token(char *s)
{
  if (*s == ';' || *s == 0)
    return (TOK_SEPA);
  else if (*s == '|')
    return (TOK_PIPE);
  else if (*s == '>')
    {
      if (*(s + 1) == '>')
	return (TOK_DRDD);
      else
	return (TOK_SRDD);
    }
  else if (*s == '<')
    {
      if (*(s + 1) == '<')
	return (TOK_DRDG);
      else
	return (TOK_SRDG);
    }
  return (0);
}

static void	detect_sepa(t_ll **ll, char **s, int *i)
{
  char		tok;

  if (get_token(*s + *i))
    {
      tok = get_token(*s + *i);
      if (tok != TOK_SEPA || my_epure_str(my_strndup(*s, *i))[0])
	{
	  my_malloc_list(*ll);
	  *ll = (*ll)->next;
	  (*ll)->cmd = my_epure_str(my_strndup(*s, *i));
	  (*ll)->token = tok;
	  (*ll)->std_tmp[0] = -1;
	  (*ll)->std_tmp[1] = -1;
	  (*ll)->fork_pid = -1;
	}
      *s += *i + 1;
      if (tok == TOK_DRDD || tok == TOK_DRDG)
	*s += 1;
      *i = -1;
    }
}

static void	fill_ll(t_ll *ll, char *s)
{
  int		i;

  i = -1;
  while (s[++i])
    detect_sepa(&ll, &s, &i);
  detect_sepa(&ll, &s, &i);
}

t_ll		*my_pars(char *s)
{
  t_ll		*ll;

  ll = malloc(sizeof(t_ll));
  ll->prev = NULL;
  ll->next = NULL;
  ll->cmd = s;
  ll->token = 0;
  ll->std_tmp[0] = -1;
  ll->std_tmp[1] = -1;
  ll->fork_pid = -1;
  fill_ll(ll, s);
  if (ll->cmd != s)
    free(s);
  return (ll);
}
