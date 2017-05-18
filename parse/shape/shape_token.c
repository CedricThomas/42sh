/*
** shape_token.c for parser in /home/cedric/Desktop/parseur 42
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue May  2 18:22:24 2017 
** Last update Thu May 18 17:15:59 2017 Cédric THOMAS
*/
#include <stdlib.h>
#include "syntax.h"
#include "my.h"

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

static char	*change_token(char *str)
{
  char		inib[3];
  char		skip[2];
  int		i;

  i = -1;
  inib[0] = INIB_C;
  inib[2] = 0;
  skip[1] = 0;
  while (SKIP[++i])
    {
      inib[1] = SKIP[i];
      skip[0] = SKIP[i];
      str = replace_unquoted_str(str, inib, skip, INIB);
    }
  return (str);
}

void		inib_token(t_token *token)
{
  char		*tmp;

  while (token)
    {
      if ((tmp = my_strdup(token->token)) == NULL)
	exit(84);
      if ((tmp = change_token(tmp)) == NULL)
	exit(84);
      free(token->token);
      token->token = dequotificator(tmp);
      token = token->next;
    }
}

void	shape_token(t_token *token)
{
  define_file(token);
  define_args(token);
}
