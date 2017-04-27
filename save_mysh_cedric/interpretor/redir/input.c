/*
** input.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by Cédric Thomas
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sat Apr  1 14:12:18 2017 Cédric Thomas
** Last update Wed Apr  5 19:05:49 2017 Cédric Thomas
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"
#include "my.h"

static int	check_acces(char *path, t_info *info)
{
  if (access(path, F_OK))
    {
      my_puterror(path);
      my_puterror(": No such file or directory.\n");
      info->last = 1;
      return (1);
    }
  else if (access(path, R_OK))
    {
      my_puterror(path);
      my_puterror(": Permission denied.\n");
      info->last = 1;
      return (1);
    }
  return (0);
}

t_fd	input(t_node *root, t_status *status, t_info *info)
{
  int	fd_in;

  if (check_acces(root->left->data, info))
    {
      close_errors(&(status->forced));
      return (status->forced);
    }
  if ((fd_in = open(root->left->data,
		    O_RDONLY)) == -1)
    {
      close_errors(&(status->forced));
      my_puterror(root->left->data);
      my_puterror(": Permission denied.\n");
      info->last = 1;
      return (status->forced);
    }
  status->forced.in = fd_in;
  search_actions(root->right, status, info);
  return (status->forced);
}
