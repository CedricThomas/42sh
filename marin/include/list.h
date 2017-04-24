/*
** my.h for liclist in /home/maje/Dropbox/delivery/B2/PSU/PSU_2016_42sh/marin
** 
** Made by maje
** Login   <marin.brunel@epitech.eu>
** 
** Started on  Thu Apr 13 12:02:46 2017 maje
** Last update Tue Apr 18 09:41:08 2017 maje
*/

#ifndef LIST_H_
# define LIST_H_

#include <stdio.h>
#include <stdlib.h>

typedef	struct	list
{
  int	x;
  int	y;
  struct list	*next;
  struct list	*prev;
}		llist;

void	remove_end_list(llist**);
void	remove_begin_list(llist**);
void   add_begin(llist **list, int x);
void	add_start(llist**, int);
void	add_end(llist**, int);
void	aff_list(llist**);
int	main();


#endif /* LIST_H_ */
