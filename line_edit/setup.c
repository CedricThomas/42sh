/*
** setup.c for GNC in /home/cedric/Desktop/get_next_cmd
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Fri Apr 21 22:15:37 2017
** Last update Tue May 16 18:38:45 2017 Cédric THOMAS
*/
#include <stdlib.h>
#include <termio.h>
#include <curses.h>
#include <sys/ioctl.h>
#include <term.h>
#include "my.h"
#include "my_alloc.h"
#include "get_next_command.h"

static int	my_set_term(struct termio *termios)
{
  if (ioctl(0, TCGETA, termios) == -1)
    return (1);
  termios->c_lflag &= ~(ICANON | ECHO);
  termios->c_cc[VTIME] = 0;
  termios->c_cc[VMIN] = 0;
  ioctl(0, TCSETA, termios);
  if (ioctl(0, TCSETA, termios) == -1)
    return (1);
  return (0);
}

static int	my_reset_term(struct termio *termios)
{
  if (ioctl(0, TCGETA, termios) == -1)
    return (1);
  termios->c_lflag |= (ICANON | ECHO);
  if (ioctl(0, TCSETA, termios) == -1)
    return (1);
  return (0);
}

static void	fct_filler(t_keypad_fct *keys)
{
  keys[0].sequence = "\n";
  keys[0].fct = &enter;
  keys[3].sequence = "\004";
  keys[3].fct = &end_of_file;
  keys[1].sequence = tigetstr("kcub1");
  keys[1].fct = &left_arrow;
  keys[2].sequence = tigetstr("kcuf1");
  keys[2].fct = &right_arrow;
  keys[4].sequence = tigetstr("kbs");
  keys[4].fct = &delete_char;
  keys[5].sequence = tigetstr("kdch1");
  keys[5].fct = &suppr_char;
  keys[6].sequence = tigetstr("khome");
  keys[6].fct = &go_start;
  keys[7].sequence = tigetstr("kend");
  keys[7].fct = &go_end;
  keys[8].sequence = "\f";
  keys[8].fct = &bind_clear;
  keys[9].sequence = "\t";
  keys[9].fct = &auto_complete;
}

t_keypad	*init_keypad(struct s_system *sys)
{
  int		i;
  char		*smkx;
  t_keypad	*keypad;

  if ((keypad = malloc(sizeof(t_keypad))) == NULL)
    return (NULL);  
  my_memset(keypad, 0, sizeof(t_keypad));
  keypad->sys = sys;
  setupterm(NULL, 0, NULL);
  if (my_set_term(&(keypad->term)))
    return (keypad);
  if ((smkx = tigetstr("smkx")) == (char *)-1)
    return (keypad);
  my_putstr(smkx);
  fct_filler(keypad->keys);
  i = -1;
  while (++i < KEY_LINKED)
    if (keypad->keys[i].sequence == (char *) -1)
      return (keypad);
  keypad->valid = 1;
  return (keypad);
}

void		*end_keypad(t_keypad *keypad)
{
  my_reset_term(&(keypad->term));
  free(keypad->line);
  free(keypad);
  endwin();
  return (NULL);
}
