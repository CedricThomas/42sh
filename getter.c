/*
** getter.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Wed May 17 13:47:54 2017 Thibaut Cornolti
** Last update Thu May 18 16:23:20 2017 maje
*/

#include <stdlib.h>
#include <memory.h>
#include "syntax.h"
#include "exec.h"

t_status		*getter_status(t_status *setter)
{
  static t_status	*status = NULL;
  if (setter)
    status = setter;
  return (status);
}
