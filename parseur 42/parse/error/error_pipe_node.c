/*
** pipe_error.c for error in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur 42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May  4 21:26:36 2017 Thibaut Cornolti
** Last update Fri May  5 11:19:44 2017 Thibaut Cornolti
*/

#include "syntax.h"

static int	check_command(t_token *start, t_token *end,
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
  return (!(mask_need_one & already_check));
}

int		error_command_node(t_field *field, t_token *mid)
{
  int		next_available;
  int		prev_available;
  int		next_need_one;
  int		prev_need_one;

  next_available =  T_ARGS | T_FILE | T_FLUX_REDIR_OUT | T_FLUX_REDIR_IN;
  next_need_one = 0;
  prev_available = T_FILE | T_FLUX_REDIR_IN | T_FLUX_REDIR_OUT;
  prev_need_one = 0;
  if (check_command(field->start, mid, prev_available, prev_need_one) ||
      check_command(mid->next, field->end, next_available, next_need_one))
    return (1);
  return (0);
}
