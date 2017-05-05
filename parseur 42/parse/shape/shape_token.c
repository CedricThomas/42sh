/*
** shape_token.c for parser in /home/cedric/Desktop/parseur 42
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue May  2 18:22:24 2017 
** Last update Fri May  5 10:09:01 2017 
*/
#include "syntax.h"

static void	define_args(t_token *token)
{
  int		is_arg;

  is_arg = 0;
  while (token)
    {
      if (token->type >= T_FLUX)
	is_arg = 0;
      if (!is_arg && token->type == T_COMMON)
	{
	  token->type = T_COMMAND;
	  is_arg = 1;
	}
      else if (is_arg && token->type == T_COMMON)
	token->type = T_ARGS;
      token = token->next;
    }
}

static void	define_file(t_token *token)
{
  int		mask;

  mask = (T_FLUX_REDIR_IN | T_FLUX_REDIR_OUT);
  while (token && token->next)
    {
      if ((mask & token->type) == token->type &&
	  (token->next->type & T_COMMON) == token->next->type)
	token->next->type = T_FILE;
      token = token->next;
    }  
}

void	shape_token(t_token *token)
{
  define_file(token);
  define_args(token);
}
