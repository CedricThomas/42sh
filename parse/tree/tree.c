/*
** tree.c for 42sh in /home/cedric/delivery/PSU/PSU_2016_42sh/parseur42
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon May 15 18:30:26 2017 Cédric THOMAS
** Last update Wed May 17 14:20:03 2017 Thibaut Cornolti
*/

#include <math.h>
#include <stdlib.h>
#include "syntax.h"
#include "my_printf.h"

static int	get_weight(int type)
{
  int		i;
  int		size[FULL_MAX_TYPES];

  size[0] = T_ARGS;
  size[1] = T_FILE;
  size[2] = T_FLUX_REDIR_OUT;
  size[3] = T_FLUX_REDIR_IN;
  size[4] = T_COMMAND;
  size[5] = T_FLUX;
  size[6] = T_LOGIC_AND;
  size[7] = T_LOGIC_OR;
  size[8] = T_SEPAR;
  size[9] = T_JOB;
  i = 0;
  while (++i < FULL_MAX_TYPES)
    if (type == size[i])
      return (i);
  return (-1);
}

static t_token	*search_biggest(t_token *start, t_token *end)
{
  t_token	*temp;
  t_token	*save;
  int		index;
  int		tmp_index;

  temp = start;
  save = start;
  index = -1;
  while (temp != end)
    {
      tmp_index = get_weight(temp->type);
      if (index < tmp_index && tmp_index > 0)
	{
	  save = temp;
	  index = tmp_index;
	}
      temp = temp->next;
    }
  return (save);
}

static void	fill_fct(void *(*fct_create_node[FULL_MAX_TYPES])
			 (t_field *field, t_token *mid),
			 int (*fct_check_error[FULL_MAX_TYPES])
			 (t_field *field, t_token *mid))
{
  fct_create_node[0] = &create_standard_node;
  fct_create_node[1] = &create_standard_node;
  fct_create_node[2] = &create_command_node;
  fct_create_node[3] = &create_standard_node;
  fct_create_node[4] = &create_standard_node;
  fct_create_node[5] = &create_standard_node;
  fct_create_node[6] = &create_pipe_node;
  fct_create_node[7] = &create_standard_node;
  fct_create_node[8] = &create_standard_node;
  fct_check_error[0] = NULL;
  fct_check_error[1] = NULL;
  fct_check_error[2] = &error_command_node;
  fct_check_error[3] = NULL;
  fct_check_error[4] = NULL;
  fct_check_error[5] = NULL;
  fct_check_error[6] = &error_pipe_node;
  fct_check_error[7] = &error_logic_node;
  fct_check_error[8] = NULL;
}

void		*auto_create_node(void *root, t_token *start, t_token *end)
{
  void		*ret;
  t_field	field;
  t_token	*bigger;
  void		*(*fct_create_node[FULL_MAX_TYPES])(t_field *field, t_token *mid);
  int		(*fct_check_error[FULL_MAX_TYPES])(t_field *field, t_token *mid);

  if (start == end)
    return (NULL);
  fill_fct(fct_create_node, fct_check_error);
  bigger = search_biggest(start, end);
  ret = NULL;
  field.root = root;
  field.start = start;
  field.end = end;
  if (!fct_check_error[my_log2(bigger->type)] ||
      !fct_check_error[my_log2(bigger->type)](&field, bigger))
    ret = fct_create_node[my_log2(bigger->type)](&field, bigger);
  return (ret);
}
