/*
** main.c for main.c in /home/cedric/delivery/ex
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
** Last update Sat Apr 22 21:25:15 2017 Cédric Thomas
*/
#include <stdlib.h>
#include <termio.h>
#include "GNC.h"
#include "my.h"
#include "my_printf.h"

int		main()
{
  char		*str;
  t_keypad	*keypad;

  if ((keypad = init_keypad()) == NULL)
    return (84);
  while ((str = get_next_cmd(keypad)))
    {
      my_printf("receive : %s\n", str);
      free(str);
    }
  end_keypad(keypad);
  return (0);
}
