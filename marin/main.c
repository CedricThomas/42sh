/*
** main.c for lemin in /home/maje/Dropbox/delivery/B2/PSU/PSU_2016_42sh/marin
** 
** Made by maje
** Login   <marin.brunel@epitech.eu>
** 
** Started on  Mon Apr 17 17:08:08 2017 maje
** Last update Tue Apr 18 09:39:53 2017 maje
*/

#include "list.h"

int     main()
{
  int   i;
  llist *list;
  list = NULL;
  i = -1;
  while (++i <= 10)
    {
      add_begin(&list, i);
      add_end(&list, i);
    }
  remove_end_list(&list);
  remove_begin_list(&list);
  aff_list(&list);
}
