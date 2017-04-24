/*
** remove_el_list.c for liblist in /home/maje/Dropbox/delivery/B2/PSU/PSU_2016_42sh/marin
** 
** Made by maje
** Login   <marin.brunel@epitech.eu>
** 
** Started on  Mon Apr 17 17:14:39 2017 maje
** Last update Tue Apr 18 08:17:39 2017 maje
*/

#include "list.h"

void	remove_end_list(llist **list)
{
  llist	*new_el;
  llist	*tmp;

  new_el = (*list);
  tmp = (*list);
  while (tmp->next != NULL)
    {
      new_el = tmp;
      tmp = tmp->next;
    }
  new_el->next = NULL;
  free(tmp);
}
