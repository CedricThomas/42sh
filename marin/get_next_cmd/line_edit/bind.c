/*
** bind.c for get_next_cmd in /home/cedric/Desktop/get_next_cmd
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Fri Apr 21 22:13:11 2017 
** Last update Mon Apr 24 09:37:41 2017 
*/
#include <termio.h>
#include <stdlib.h>
#include "GNC.h"
#include "my.h"

int	enter(t_keypad *keypad)
{
  if (keypad->buffer == NULL)
    if ((keypad->buffer = my_strdup("")) == NULL)
      return (1);
  my_putchar('\n');
  keypad->index = -1;
  return (0);
}

int	end_of_file(t_keypad *keypad)
{
  if (keypad->buffer == NULL)
    keypad->index = -2;
  return (0);
}

int	left_arrow(t_keypad *keypad)
{
  //  my_printf("bite\n");
  if (keypad->buffer && keypad->index > 0)
    {
      keypad->index -= 1;
      my_putstr(keypad->key_parse[3].sequence);
    }
  return (0);
}

int	right_arrow(t_keypad *keypad)
{
  //  my_printf("bite\n");
  if (keypad->buffer && keypad->index < my_strlen(keypad->buffer))
    {
      keypad->index += 1;
      my_putstr(keypad->key_parse[2].sequence);
    }
  return (0);
}
