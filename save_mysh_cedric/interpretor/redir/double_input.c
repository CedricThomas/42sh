/*
** input.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by Cédric Thomas
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sat Apr  1 14:12:18 2017 Cédric Thomas
** Last update Fri Apr  7 09:24:19 2017 
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "get_next_line.h"
#include "mysh.h"

int	change_input(t_node *root, t_status *status, t_info *info)
{
  char	*str;
  int	mypipe[2];
  int	fd_in;

  if (pipe(mypipe) < 0)
    {
      my_puterror("Can't make pipe.\n");
      return (1);
    }
  if (isatty(0))
    my_putstr("? ");
  while ((str = get_next_line(0)) && my_strcmp(str, root->left->data))
    {
      if (isatty(0))
	my_putstr("? ");
      write(mypipe[1], str, my_strlen(str));
      write(mypipe[1], "\n", 1);
      free(str);
    }
  close(mypipe[1]);
  status->forced.in = mypipe[0];
  free(str);
  return (0);
}

int	search_double_input(t_node *root, t_status *status, t_info *info)
{
  while (root->type == T_FLUX_REDIR && my_strcmp(root->data, "<<"))
    root = root->right;
  if (root->type != T_FLUX_REDIR)
    return (0);
  if (change_input(root, status, info))
    return (1);
  return (0);
}

t_fd	double_input(t_node *root, t_status *status, t_info *info)
{
  if ((status->status & ON_PIPELINE) == ON_PIPELINE &&
      (status->status & ON_FORK) == ON_FORK)
    search_actions(root->right, status, info);
  else
    {
      if (change_input(root, status, info))
	return (status->forced);
      search_actions(root->right, status, info);
    }
  return (status->forced);
}
