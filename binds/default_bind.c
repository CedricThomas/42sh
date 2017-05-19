/*
** default_bind.c for gnc in /home/cedric/Desktop/get_next_cmd
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon May 15 22:03:45 2017 Cédric THOMAS
** Last update Fri May 19 10:51:41 2017 Cédric THOMAS
*/
#include <sys/ioctl.h>
#include <ncurses.h>
#include <curses.h>
#include <term.h>
#include "get_next_command.h"
#include "my_printf.h"
#include "my.h"

void		default_append(char *buff, t_keypad *keypad, int size_buff)
{
  int		idx;
  int		i;
  char		*seq;

  i = -1;
  idx = 0;
  while (buff[++i])
    {
      if (buff[i] >= ' ' && buff[i] <= '~')
	{
	  keypad->line = insert_str(keypad->line, buff + i, keypad->index + idx, 1);
	  idx += 1;
	}
    }
  if (keypad->line)
    {
      my_printf("%s", keypad->line + keypad->index);
      keypad->index += idx;
      i = my_strlen(keypad->line) - keypad->index;
      if ((seq = tigetstr("cub1")) == (char *) -1)
	return ;
      while (--i >= 0)
	my_printf(seq);
    }
  UNUSED(size_buff);
}
