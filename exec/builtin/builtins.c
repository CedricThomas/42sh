/*
** builtins.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May 18 23:57:02 2017 Thibaut Cornolti
** Last update Fri May 19 00:07:24 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

void		builtin_builtins(t_command *cmd, t_status *status, t_info *info)
{
  UNUSED(cmd);
  UNUSED(status);
  UNUSED(info);
  //my_system("echo bite bite bite | sort | column", getter_system(NULL));
}
