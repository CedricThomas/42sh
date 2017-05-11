/*
** get_next_cmd.c for get_next_cmd.c in /home/cedric/Desktop/get_next_cmd
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Fri Apr 21 22:22:55 2017 
** Last update Mon Apr 24 09:38:28 2017 
*/

#include <sys/ioctl.h>
#include <ncurses.h>
#include <termio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>
#include "GNC.h"
#include "my.h"

static int	my_set_term(struct termio *termios)
{
  ioctl(0, TCGETA, termios);
  termios->c_lflag &= ~(ICANON | ECHO);
  termios->c_cc[VTIME] = 0;
  termios->c_cc[VMIN] = 0;
  ioctl(0, TCSETA, termios);
  return (0);
}

static int	my_reset_term(struct termio *termios)
{
  ioctl(0, TCGETA, termios);
  termios->c_lflag |= (ICANON | ECHO);
  ioctl(0, TCSETA, termios);
  return (0);
}

static int	get_input(char *buff, t_keypad *keypad)
{
  int		size;

  if ((size = read(0, buff, READ_SIZE)) > 0)
    {
      buff[size] = 0;
      my_putprintable(buff, keypad);
    }
  return (size);
}

static int	find_exec(t_keypad *keypad, char *buff)
{
  int		match;
  int		i;

  i = -1;
  match = -1;
  //  my_printf("\nSearch exec :\n", keypad->key_parse[i].sequence, buff);
  while (++i < KEY_LINKED && match == -1)
    {
      //my_printf("%S vs %S\n", keypad->key_parse[i].sequence, buff);
      if (keypad->key_parse[i].sequence)
  	if (!my_strcmp(keypad->key_parse[i].sequence, buff))
  	  {
  	    if (keypad->key_parse[i].fct(keypad))
  	      return (1);
  	    match = 0;
  	  }
    }
  if (match == -1)
    {
      if ((keypad->buffer = insert_str(keypad->buffer, buff,
      				       keypad->index, keypad)) == NULL)
      	return (1);
      keypad->index += my_strlen(buff);
    }
  return (0);
}

char	*get_next_cmd(t_keypad *keypad)
{
  char  buff[READ_SIZE + 1];
  int   size;

  my_set_term(&(keypad->term));
  keypad->buffer = NULL;
  while (keypad->index >= 0)
    {
      if ((size = get_input(buff, keypad)) != 0)
	{
	  if (size < 0)
	    keypad->index = -1;
	  else
	    if (find_exec(keypad, buff))
	      return (NULL);
	}
      usleep(1);
    }
  if (size >= 0)
    keypad->index += 1;
  my_reset_term(&(keypad->term));
  return (keypad->buffer);
}
