/*
** list_job.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon May 15 21:10:07 2017 Thibaut Cornolti
** Last update Thu May 18 10:02:10 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "syntax.h"
#include "exec.h"

void		plane_job(t_job *ll)
{
  while (ll)
    {
      if (ll->status == 0)
	ll->number = -1;
      ll = ll->next;
    }
}

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
