/*
** exit.c for exit.c in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sun Jan  8 16:44:37 2017 
** Last update Sat Apr  1 14:00:37 2017 Cédric Thomas
*/
#include "my.h"
#include "mysh.h"

static void	check_syntax(char *arg, t_info *info, t_status *status)
{
  int		i;

  i = -1;
  while (arg[++i] && (is_nb(arg[i]) || (i == 0 && arg[0] == '-')));
  if (!arg[i])
    {
      info->last = my_getnbr(arg);
      status->exit = 1;
      return ;
    }
  else if (!is_nb(arg[i]) && i > 0)
    my_puterror("exit: Badly formed number.\n");
  else if (!is_nb(arg[i]))
    my_puterror("exit: Expression Syntax.\n");
  info->last = 1;
}

int	exitsh(t_info *info, t_toexec *exec, t_status *status)
{
  info->last = 0;
  if (exec->argc == 1)
    status->exit = 1;
  else if (exec->argc == 2)
    check_syntax(exec->argv[1], info, status);
  else
    {
      info->last = 1;
      my_puterror("exit: Expression Syntax.\n");
    }
  return (0);
}
