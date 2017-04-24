/*
** add_begin.c for lib_llist in /home/maje/Dropbox/delivery/B2/PSU/PSU_2016_42sh/marin
** 
** Made by maje
** Login   <marin.brunel@epitech.eu>
** 
** Started on  Thu Apr 13 18:09:10 2017 maje
** Last update Tue Apr 18 09:40:07 2017 maje
*/

#include "list.h"

void   add_begin(llist **list, int x)
{
  llist *new_el;

  new_el = malloc(sizeof(llist));
  new_el->x = x;
  new_el->next = (*list);
  (*list) = new_el;
}

