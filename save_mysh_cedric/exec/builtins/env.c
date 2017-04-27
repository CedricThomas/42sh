/*
** env.c for env in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Jan 11 17:30:51 2017 
** Last update Sat Apr  1 15:10:26 2017 
*/
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

int	envsh(t_info *info, t_toexec *exec, t_status *status)
{
  if (exec->argc == 1 && exec->argv)
    my_show_wordtab(info->env);
  else
    {
      my_puterror("env: Too many arguments.\n");
      info->last = 1;
    }
  return (0);
}
