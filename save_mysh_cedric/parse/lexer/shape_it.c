/*
** shape_it.c for parseur in /home/cedric/delivery/parseur_ll/lexer
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Thu Mar 23 17:12:35 2017 
** Last update Mon Apr  3 01:00:02 2017 
*/
#include <stdlib.h>
#include "my.h"
#include "syntax.h"

static int	swap_flux(t_token *temp)
{
  int		bool;
  t_token	*reverse;

  reverse = temp->prev;
  bool = 1;
  while (reverse->prev && (reverse->prev->type == T_ARGS
			   || reverse->prev->type == T_COMMAND))
    {
      bool = 0;
      swap_token(reverse->prev, reverse);
      swap_token(temp->prev, temp);
      reverse = temp->prev;
      temp = temp->prev;
    }
  return (bool);
}

static void	deplace_flux(t_token **token)
{
  int		bool;
  t_token	*temp;

  bool = 0;
  while (!bool)
    {
      bool = 1;
      temp = *token;
      while (temp)
	{
	  if (temp->type == T_FLUX_REDIR)
	    bool = swap_flux(temp);
	  temp = temp->next;
	}
    }
  temp = *token;
  while (temp)
    {
      if (temp->prev && temp->type == T_COMMAND &&
	  (temp->prev->type == T_COMMAND || temp->prev->type == T_ARGS))
	temp->type = T_ARGS;
      temp = temp->next;
    }
}

static int	check_redir_output(t_token **token)
{
  t_token	*temp;

  temp = *token;
  while (temp)
    {
      if (temp->type == T_FLUX_REDIR)
	if (!temp->next || temp->next->type != T_COMMON)
	  {
	    my_puterror("Missing name for redirect.\n");
	    my_free_token(token);
	    return (84);
	  }
      temp = temp->next;
    }
  return (0);
}

int		redefine_tokens(t_token **token)
{
  t_token	*temp;

  if (check_redir_output(token))
    return (84);
  temp = *token;
  while (temp)
    {
      if (temp->type == T_COMMON)
	if (temp->prev && temp->prev->type == T_FLUX_REDIR &&
	    (temp->prev->prev == NULL || temp->prev->prev->type != T_FILE))
	  {
	    temp->type = T_FILE;
	    swap_token(temp->prev, temp);
	  }
  	else if (temp->prev && (temp->prev->type == T_ARGS ||
				temp->prev->type == T_COMMAND))
  	  temp->type = T_ARGS;
  	else
	  temp->type = T_COMMAND;
      temp = temp->next;
    }
  deplace_flux(token);
  return (0);
}

char	*shape_for_token(char *str, t_syntax *my_syntax)
{
  str = shape_separator(str, my_syntax[0].values);
  str = shape_separator(str, my_syntax[1].values);
  str = shape_separator(str, my_syntax[2].values);
  return (str);
}
