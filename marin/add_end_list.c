/*
** add_end_list.c for libllist in /home/maje/Dropbox/delivery/B2/PSU/PSU_2016_42sh/marin
** 
** Made by maje
** Login   <marin.brunel@epitech.eu>
** 
** Started on  Mon Apr 17 16:58:49 2017 maje
** Last update Tue Apr 18 09:40:26 2017 maje
*/

#include "list.h"

void    add_end(llist **list, int x)
{
  llist *new_el;
  llist *tmp;

  new_el = malloc(sizeof(llist));
  new_el->x = x;
  new_el->next = NULL;
  if (list == NULL)
    new_el = (*list);
  else
    {
      tmp = (*list);
      while (tmp->next != NULL)
	{
	  tmp = tmp->next;
	}
      tmp->next = new_el;
    }
}
