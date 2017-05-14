/*
** info.c for 42Sh in /home/cedric/Desktop/parseur 42/exec
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue May  9 09:30:17 2017 
** Last update Thu May 11 17:01:40 2017 Thibaut Cornolti
*/
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static void	get_builtins(t_info *my_info)
{
  my_info->builtins[0] = "exit";
  my_info->builtins[1] = "cd";
  my_info->builtins[2] = "setenv";
  my_info->builtins[3] = "unsetenv";
  my_info->builtins[4] = "echo";
  my_info->builtins[5] = NULL;
}

t_info		*get_info(char **env)
{
  char		*temp;
  t_info	*my_info;

  if ((my_info = malloc(sizeof(t_info))) == NULL)
    return (NULL);
  if ((my_info->env = tab_dup(env)) == NULL)
    return (NULL);
  my_info->exit_value = 0;
  if ((temp = getkey_pwd()) == NULL)
    return (NULL);
  if (changekey(my_info->env, "PWD", temp, 0))
    my_info->env = addkey(my_info->env, "PWD", temp, 0);
  my_info->pwd = temp;
  if ((my_info->old_pwd = my_strdup("")) == NULL)
    return (NULL);
  if ((temp = getkey_hostname()) == NULL)
    return (NULL);
  if (changekey(my_info->env, "HOST", temp, 0))
    my_info->env = addkey(my_info->env, "HOST", temp, 0);
  free(temp);
  get_builtins(my_info);
  return (my_info);
}

void		*free_info(t_info *info)
{
  free(info->pwd);
  free(info->old_pwd);
  free_tab(info->env);
  free(info);
  return (NULL);
}
