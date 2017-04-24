/*
** chained.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell2
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu Mar 23 13:47:56 2017 Thibaut Cornolti
** Last update Thu Mar 23 20:06:04 2017 Thibaut Cornolti
*/

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"
#include "pars.h"

void		my_malloc_list(t_ll *ll)
{
  t_ll		*elem;

  elem = malloc(sizeof(t_ll));
  while (ll && ll->next)
    ll = ll->next;
  ll->next = elem;
  elem->prev = ll;
  elem->next = NULL;
}
