/*
** redir.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Thu Mar 30 13:27:56 2017 
** Last update Tue May  9 13:22:11 2017 
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

/* static int		my_redir(t_node *root, t_status *status, t_info *info) */
/* { */
/*   int		i; */
/*   t_parse_fct	fct[REDIR_TYPES]; */

/*   i = -1; */
/*   set_fct(fct); */
/*   while (++i < REDIR_TYPES) */
/*     { */
/*       if (!my_strcmp(root->data, fct[i].tag)) */
/*   	if (fct[i].fct != NULL) */
/*   	  return (fct[i].fct(root, status, info)); */
/*     } */
/* } */

void	close_redir(t_command *cmd)
{
  if (cmd->fd[0] != 0)
    close(cmd->fd[0]);
  if (cmd->fd[1] != 1) 
    close(cmd->fd[1]);
  if (cmd->fd[2] != 2)
    close(cmd->fd[2]);
}
