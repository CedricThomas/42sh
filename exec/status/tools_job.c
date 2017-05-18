/*
** list_job.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon May 15 21:10:07 2017 Thibaut Cornolti
** Last update Thu May 18 14:44:00 2017 Cédric THOMAS
*/

#include <stdlib.h>
#include "syntax.h"
#include "exec.h"

t_job		*get_job(t_job *ll, int pid)
{
  while (ll)
    {
      if (ll->pid == pid && ll->status)
	return (ll);
      ll = ll->next;
    }
  return (NULL);
}
