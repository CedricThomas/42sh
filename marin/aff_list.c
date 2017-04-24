/*
** aff_list.c for liblist in /home/maje/Dropbox/delivery/B2/PSU/PSU_2016_42sh/marin
** 
** Made by maje
** Login   <marin.brunel@epitech.eu>
** 
** Started on  Mon Apr 17 17:01:06 2017 maje
** Last update Mon Apr 17 17:01:35 2017 maje
*/

#include "list.h"

void    aff_list(llist **list)
{
  llist *tmp = (*list);

  while (tmp != NULL)
    {
      printf("%d\n", tmp->x);
      tmp = tmp->next;
    }
}
