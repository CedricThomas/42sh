/*
** setup.c for GNC in /home/cedric/Desktop/get_next_cmd
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Fri Apr 21 22:15:37 2017 
** Last update Tue May  9 15:14:34 2017 maje
*/
#include <stdlib.h>
#include <termio.h>
#include <curses.h>
#include <term.h>
#include "my.h"
#include "my_alloc.h"
#include "GNC.h"

t_keypad	*init_keypad()
{
  t_keypad	*keypad;

  if ((keypad = malloc(sizeof(t_keypad))) == NULL)
    return (NULL);
  my_memset((char *)keypad, 0, sizeof(t_keypad));
  setupterm(NULL, 0, NULL);
  keypad->key_parse[0].sequence = "\n";
  keypad->key_parse[0].fct = &enter;
  keypad->key_parse[1].sequence = my_seq(1, 4);
  keypad->key_parse[1].fct = &end_of_file;
  if ((keypad->key_parse[2].sequence = tigetstr("cuf1")) == (char *) -1)
    return (NULL);
  keypad->key_parse[2].fct = &right_arrow;
  keypad->key_parse[3].sequence = my_seq(3, '\e', '[', 'D');
  /* if ((keypad->key_parse[3].sequence = tigetstr("kcub1")) == (char *) -1) */
  /*   return (NULL); */
  keypad->key_parse[3].fct = &left_arrow;
  return (keypad);
}

void		*end_keypad(t_keypad *keypad)
{
  free(keypad);
  my_free_tag("seq", 's');
  endwin();
  return (NULL);
}