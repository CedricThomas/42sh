/*
** unsetenv.c for unsetenv.c in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue Jan 10 11:10:28 2017 
** Last update Sat Apr  1 15:08:49 2017 
*/
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

int    unsetenvsh(t_info *info, t_toexec *exec, t_status *status)
{
  int	i;

  i = 0;
  info->last = 0;
  if (exec->argc <= 1)
    {
      info->last = 1;
      my_puterror("unsetenv: Too few arguments.\n");
    }
  else
    while (exec->argv[++i])
      info->env = deletekey(info->env, exec->argv[i], 0);
  return (0);
}
