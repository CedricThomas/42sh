/*
** main.c for main.c in /home/cedric/delivery/ex
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
** Last update Mon May  1 19:23:38 2017 
*/
#include "my.h"
#include "get_next_line.h"
#include "syntax.h"

int		main(int ac, char **av)
{
  t_syntax	*syntax;
  char		*str;

  syntax = get_syntax();
  while ((str = get_next_line(0)))
    {
      parse_cmd(syntax, str);
    }
  free_syntax(&syntax);
  UNUSED(av);
  UNUSED(ac);
  return (0);
}
