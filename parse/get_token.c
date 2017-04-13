/*
** get_token.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parse
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu Apr 13 12:05:10 2017 Thibaut Cornolti
** Last update Thu Apr 13 12:11:27 2017 Thibaut Cornolti
*/


/*
**
** Le pars est a changé complètement, 
** je fais ce truc dégueu pour commencer 
** à bosser sur des fonctionnalités
**
*/

#include "sh.h"
#include "pars.h"

static int	get_token_1(char *s)
{
  if (*s == ';' || *s == 0)
    return (TOK_SEPA);
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

static int	get_token_2(char *s)
{
  if (*s == '|')
    {
      if (*(s + 1) == '|')
	return (TOK_DPIP);
      else
	return (TOK_PIPE);
    }
  else if (*s == '&')
    {
      if (*(s + 1) == '&')
	return (TOK_DESP);
      else
	return (0); /* SIMPLE '&' NON GERE */
    }
  return (0);
}

int		get_token(char *s)
{
  int		tok;

  if ((tok = get_token_1(s)) == 0)
    tok = get_token_2(s);
  return (tok);
}
