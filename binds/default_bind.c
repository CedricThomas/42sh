/*
** default_bind.c for gnc in /home/cedric/Desktop/get_next_cmd
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon May 15 22:03:45 2017 Cédric THOMAS
** Last update Wed May 17 13:52:17 2017 Cédric THOMAS
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
  int		i;
  char		*seq;

  keypad->line = insert_str(keypad->line, buff, keypad->index);
  if (keypad->line)
    {
      my_printf("%s", keypad->line + keypad->index);
      keypad->index += size_buff;
      i = my_strlen(keypad->line) - keypad->index;
      if ((seq = tigetstr("cub1")) == (char *) -1)
	return ;
      while (--i >= 0)
	my_printf(seq);
    }
}
