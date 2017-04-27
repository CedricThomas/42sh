/*
** inter.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue Mar 28 22:36:31 2017 
** Last update Sun Apr  2 17:46:51 2017 
*/
#include <stdlib.h>
#include "mysh.h"
#include "my_printf.h"

static void	get_fct(t_parse_fct parse[NODE_TYPES])
{
  parse[0].type = T_COMMAND;
  parse[0].fct = &my_cmd;
  parse[1].type = T_FLUX;
  parse[1].fct = &my_pipe;
  parse[2].type = T_FLUX_REDIR;
  parse[2].fct = &my_redir;
  parse[3].type = T_SEPAR;
  parse[3].fct = &my_separ;
}

t_fd		search_actions(t_node *root, t_status *status, t_info *info)
{
  t_parse_fct	fct_parse[NODE_TYPES];
  int		i;

  i = -1;
  if (root == NULL)
    return (myfds(-1, -1));
  get_fct(fct_parse);
  while (++i < NODE_TYPES)
    {
      if (root->type == fct_parse[i].type)
	if (fct_parse[i].fct != NULL)
	  return (fct_parse[i].fct(root, status, info));
    }
}
