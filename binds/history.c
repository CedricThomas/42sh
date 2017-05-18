/*
** history.c for 42sh in /home/cedric/delivery/PSU/PSU_2016_42sh
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Thu May 18 19:13:06 2017 Cédric THOMAS
** Last update Thu May 18 19:43:13 2017 maje
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

int		down_arrow(t_keypad *keypad)
{
  t_history	hist;

  if (keypad->system->info->histo->current->next == NULL)
    return (-1);
}

int		up_arrow(t_keypad *keypad)
{
  


}
