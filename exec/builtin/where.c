/*
** builtins.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May 18 23:57:02 2017 Thibaut Cornolti
** Last update Sat May 20 13:39:07 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

void		builtin_where(t_command *cmd, t_status *status, t_info *info)
{
  UNUSED(cmd);
  UNUSED(status);
  info->exit_value = 1;
}
