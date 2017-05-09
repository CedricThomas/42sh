/*
** misc.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue Mar 28 21:47:15 2017 
** Last update Sun Apr  2 15:44:48 2017 
*/
#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"

char		**args_node_to_argv(t_node *root)
{
  char		**new;
  int		size;
  t_node	*temp;

  if (!root && root->type != T_COMMAND)
    return (NULL);
  temp = root;
  size = 0;
  while (temp)
    {
      temp = temp->right;
      size += 1;
    }
  if ((new = malloc(sizeof(char *) * (size + 1))) == NULL)
    return (NULL);
  new[size] = NULL;
  temp = root;
  size = 0;
  while (temp)
    {
      new[size] = temp->data;
      temp = temp->right;
      size += 1;
    }
  return (new);
}

void	close_errors(t_fd *forced)
{
  if (forced->in != 0)
    {
      close(forced->in);
      forced->in = 0;
    }
  if (forced->out != 1)
    {
      close(forced->out);
      forced->in = 1;
    }
}
