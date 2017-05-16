/*
** del_binds.c for del_binds in /home/cedric/Desktop/get_next_cmd
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon May 15 22:18:05 2017 Cédric THOMAS
** Last update Tue May 16 15:31:57 2017 Cédric THOMAS
*/
#include <curses.h>
#include <termio.h>
#include <stdlib.h>
#include "get_next_command.h"
#include "my.h"
#include "my_printf.h"

int	suppr_char(t_keypad *keypad)
{
  int	i;
  int	len;
  char	*seq;

  if (keypad->line && keypad->line[keypad->index])
    {
      if ((seq = tigetstr("cub1")) == (char *)-1)
	return (0);
      keypad->line = delete_a_char(keypad->line, keypad->index);
      len = my_strlen(keypad->line);
      i = len - keypad->index + 1;
      while (--i >= 0)
      	my_printf(" ");
      i = len - keypad->index + 1;
      while (--i >= 0)
      	my_printf(seq);
      my_printf("%s", keypad->line + keypad->index);
      i = len - keypad->index + 1;
      while (--i > 0)
      	my_printf(seq);
    }
  return (0);
}

int	delete_char(t_keypad *keypad)
{
  int	i;
  int	len;
  char	*seq;

  if (keypad->line && keypad->index > 0)
    {
      if ((seq = tigetstr("cub1")) == (char *)-1)
	return (0);
      keypad->line = delete_a_char(keypad->line, keypad->index - 1);
      keypad->index -= 1;
      my_printf(seq);
      len = my_strlen(keypad->line);
      i = len - keypad->index + 1;
      while (--i >= 0)
	my_printf(" ");
      i = len - keypad->index + 1;
      while (--i >= 0)
      	my_printf(seq);
      my_printf("%s", keypad->line + keypad->index);
      i = len - keypad->index;
      while (--i >= 0)
      	my_printf(seq);
    }
  return (0);
}
