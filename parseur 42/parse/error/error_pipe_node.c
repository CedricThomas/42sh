/*
** pipe_error.c for error in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur 42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May  4 21:26:36 2017 Thibaut Cornolti
** Last update Thu May 11 23:33:53 2017 Thibaut Cornolti
*/

#include "syntax.h"

static int	check_pipe(t_token *start, t_token *end,
			   int mask_available, int mask_need_one)
{
  int		already_check;

  already_check = 0;
  while (start != end)
    {
      already_check |= start->type;
      if (!(mask_available & start->type))
	return (1);
      start = start->next;
    }
  if (!(mask_need_one & already_check))
    {
      my_puterror("Invalid null command.\n");
      return (1);
    }
  return (0);
}

int		error_pipe_node(t_field *field, t_token *mid)
{
  int		next_available;
  int		prev_available;
  int		next_need_one;
  int		prev_need_one;

  next_available = T_COMMAND | T_ARGS | T_FILE | T_FLUX_REDIR_OUT | T_FLUX;
  next_need_one = T_COMMAND;
  prev_available = T_COMMAND | T_ARGS | T_FILE | T_FLUX_REDIR_IN;
  prev_need_one = T_COMMAND;
  if (check_pipe(field->start, mid, prev_available, prev_need_one) ||
      check_pipe(mid->next, field->end, next_available, next_need_one))
    return (1);
  return (0);
}
