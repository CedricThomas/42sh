/*
** inter.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue Mar 28 22:36:31 2017 
** Last update Fri May 12 11:59:23 2017 
*/
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"

static void	get_fct(t_exec_fct parse[TREE_TYPES])
{
  parse[0].type = T_COMMAND;
  parse[0].fct = &exec_cmd;
  parse[1].type = T_FLUX;
  parse[1].fct = &exec_pipe;
  parse[2].type = T_SEPAR;
  parse[2].fct = &exec_separ;
  parse[3].type = T_LOGIC;
  parse[3].fct = &exec_logic;
}

int		auto_select(t_node *root, t_status *status, t_info *info)
{
  t_exec_fct	fct_parse[TREE_TYPES];
  int		i;

  i = -1;
  if (root == NULL)
    return (0);
  get_fct(fct_parse);
  while (++i < TREE_TYPES)
    {
      if (root->type == fct_parse[i].type)
	if (fct_parse[i].fct != NULL)
	  return (fct_parse[i].fct(root, status, info));
    }
  return (0);
}
