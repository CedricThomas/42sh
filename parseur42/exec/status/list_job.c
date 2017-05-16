/*
** list_job.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon May 15 21:10:07 2017 Thibaut Cornolti
** Last update Tue May 16 14:40:21 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"

t_job		*my_put_list_job(t_status *status, int pid, int stats)
{
  t_job		*tmp;
  t_job		*elem;

  tmp = status->job_list;
  if ((elem = malloc(sizeof(*elem))) == NULL)
    exit(84);
  elem->pid = pid;
  elem->status = stats;
  elem->number = status->job_nbr;
  elem->step = 0;
  elem->next = NULL;
  if (tmp == NULL)
    {
      elem->prev = NULL;
      status->job_list = elem;
    }
  else
    {
      while (tmp->next)
	tmp = tmp->next;
      elem->prev = tmp;
      tmp->next = elem;
    }
  return (elem);
}

int		my_del_job(t_job **ll)
{
  t_job		*tmp;

  while (*ll)
    {
      tmp = *ll;
      *ll = (*ll)->next;
      free(tmp);
    }
  return (0);
}

void		show_job_status(t_job *ll)
{
  const char		*status[5] =
    {"wtf", "suspended", "background", "nop", "current"};

  while (ll)
    {
      my_printf("pid : %d (%s)\n", ll->pid, status[ll->status]);
      ll = ll->next;
    }
}

int		get_free_job(t_job *ll)
{
  int		number;
  int		is_free;
  t_job		*tmp;

  number = 0;
  while (++number)
    {
      tmp = ll;
      is_free = 1;
      while (tmp)
	{
	  if (tmp->number == number)
	    is_free = 0;
	  tmp = tmp->next;
	}
      if (is_free)
	return (number);
    }
  return (-1);
}

void		set_job_value(t_job *ll, int pid, int status)
{
  while (ll)
    {
      if (ll->pid == pid)
	ll->status = status;
      ll = ll->next;
    }
}
