/*
** copy_paste.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Fri May 19 22:19:27 2017 Thibaut Cornolti
** Last update Sat May 20 09:43:28 2017 Cédric THOMAS
*/

#include <curses.h>
#include <termio.h>
#include <stdlib.h>
#include <unistd.h>
#include "syntax.h"
#include "exec.h"
#include "get_next_command.h"
#include "my.h"
#include "my_printf.h"

static int	get_shift(t_keypad *keypad, int sense)
{
  int		i;
  int		shift;

  i = keypad->index;
  shift = 0;
  if (!keypad->line || (!keypad->line[i] && sense))
    return (0);
  if (sense)
    while (keypad->line[++i] && keypad->line[i] != ' ')
      shift += 1;
  else
    while (i && --i && keypad->line[i] && keypad->line[i] != ' ')
      shift += 1;
  return (shift + 1);
}

int		ctrl_left_arrow(t_keypad *keypad)
{
  char		*seq;
  int		shift;

  if ((seq = tigetstr("cub1")) == (char *)-1)
    return (0);
  shift = get_shift(keypad, 0);
  if (keypad->index > 0)
    {
      keypad->index -= shift;
      while (shift-- > 0)
	my_printf(seq);
    }
  return (0);
}

int		ctrl_right_arrow(t_keypad *keypad)
{
  char		*seq;
  int		shift;

  if ((seq = tigetstr("cuf1")) == (char *)-1)
    return (0);
  shift = get_shift(keypad, 1);
  if (keypad->index < my_strlen(keypad->line))
    {
      keypad->index += shift;
      while (shift-- > 0)
	my_printf(seq);
    }
  return (0);
}
