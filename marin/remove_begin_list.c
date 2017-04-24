/*
** remove_el_list.c for liblist in /home/maje/Dropbox/delivery/B2/PSU/PSU_2016_42sh/marin
** 
** Made by maje
** Login   <marin.brunel@epitech.eu>
** 
** Started on  Tue Apr 18 08:40:51 2017 maje
** Last update Tue Apr 18 08:52:33 2017 maje
*/

#include "list.h"

void	remove_begin_list(llist **list)
{
  llist	*tmp;

  if (list != NULL)
    {
      tmp = (*list)->next;
      //      free(list);
      *list = tmp;
    }
}
