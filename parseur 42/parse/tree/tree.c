/*
** tree.c for parseur in /home/cedric/delivery/parseur_ll/tree
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Last update Thu May  4 22:34:28 2017 
** Last update Thu May  4 21:36:11 2017 Thibaut Cornolti
*/

#include <math.h>
#include <stdlib.h>
#include "syntax.h"
#include "my_printf.h"

static t_token	*search_biggest(t_token *start, t_token *end)
{
  t_token	*temp;
  t_token	*save;

  temp = start;
  save = start;
  while (temp != end)
    {
      if (save->type < temp->type)
	save = temp;
      temp = temp->next;
    }
  return (save);
}

static void	fill_fct(void *(*fct_create_node[FULL_MAX_TYPES])(t_field *field,
								  t_token *mid),
			 int (*fct_check_error[FULL_MAX_TYPES])(t_field *field,
								  t_token *mid))
{
  fct_create_node[0] = &create_standard_node;
  fct_create_node[1] = &create_standard_node;
  fct_create_node[2] = &create_standard_node;
  fct_create_node[3] = &create_standard_node;
  fct_create_node[4] = &create_command_node;
  fct_create_node[5] = &create_standard_node;
  fct_create_node[6] = &create_standard_node;
  fct_create_node[7] = &create_standard_node;
  fct_check_error[0] = NULL;
  fct_check_error[1] = NULL;
  fct_check_error[2] = NULL;
  fct_check_error[3] = NULL;
  fct_check_error[4] = NULL;
  fct_check_error[5] = &error_pipe_node;
  fct_check_error[6] = NULL;
  fct_check_error[7] = NULL;
}

static void	show_debug_node(t_token *start, t_token *end)
{
  my_printf("NODE::\n");
  while (start != end)
    {
      my_printf("\t%s %d\n", start->token, start->type);
      start = start->next;
    }
  my_printf("------\n");
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
  show_debug_node(start, end);
  fill_fct(fct_create_node, fct_check_error);
  bigger = search_biggest(start, end);
  ret = NULL;
  field.root = root;
  field.start = start;
  field.end = end;
  if (fct_check_error[my_log2(bigger->type)] == NULL ||
      !fct_check_error[my_log2(bigger->type)](&field, bigger))
    ret = fct_create_node[my_log2(bigger->type)](&field, bigger);
  return (ret);
}
