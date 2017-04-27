/*
** redir.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Thu Mar 30 13:27:56 2017 
** Last update Sat Apr  1 18:26:32 2017 Cédric Thomas
*/
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

static void	set_fct(t_parse_fct fct[REDIR_TYPES])
{
  fct[0].tag = ">";
  fct[0].fct = &output;
  fct[1].tag = ">>";
  fct[1].fct = &double_output;
  fct[2].tag = "<";
  fct[2].fct = &input;
  fct[3].tag = "<<";
  fct[3].fct = &double_input;
}

t_fd		my_redir(t_node *root, t_status *status, t_info *info)
{
  int		i;
  t_parse_fct	fct[REDIR_TYPES];

  i = -1;
  set_fct(fct);
  while (++i < REDIR_TYPES)
    {
      if (!my_strcmp(root->data, fct[i].tag))
  	if (fct[i].fct != NULL)
  	  return (fct[i].fct(root, status, info));
    }
}
