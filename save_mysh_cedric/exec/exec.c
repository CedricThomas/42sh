/*
** exec.c for exec_selector in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sun Jan  8 14:13:47 2017 
** Last update Thu Apr  6 17:34:50 2017 
*/
#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"
#include "my.h"
#include "get_next_line.h"

t_builtin	*get_builtins()
{
  t_builtin	*builtins;

  if ((builtins = malloc(sizeof(t_parse_fct) * BUILTINS_NB)) == NULL)
    return (NULL);
  builtins[0].fct = &exitsh;
  builtins[1].fct = &cd;
  builtins[2].fct = &setenvsh;
  builtins[3].fct = &unsetenvsh;
  builtins[4].fct = &envsh;
  builtins[0].builtins = my_strdup("exit");
  builtins[1].builtins = my_strdup("cd");
  builtins[2].builtins = my_strdup("setenv");
  builtins[3].builtins = my_strdup("unsetenv");
  builtins[4].builtins = my_strdup("env");
  return (builtins);
}

int		try_builtins(t_info *info, t_toexec *exec, t_status *status)
{
  char		*str;
  int		i;
  int		rt;

  i = -1;
  rt = 1;
  while (info->builtins && ++i < BUILTINS_NB && rt == 1)
    if (info->builtins[i].builtins &&
	!my_strcmp(info->builtins[i].builtins, exec->argv[0]))
      rt = info->builtins[i].fct(info, exec, status);
  if (rt == 0 && (status->status & ON_PIPELINE) == ON_PIPELINE)
    {
      my_put_list_exit(&(status->pipeline), -1, info->last);
    }
  return (rt);
}

int	exec_full(t_info *info, t_toexec *exec, t_status *status)
{
  if (try_builtins(info, exec, status) > 0)
    my_exec(info, exec, status);
  return (0);
}
