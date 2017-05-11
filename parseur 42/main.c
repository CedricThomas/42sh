/*
** main.c for main.c in /home/cedric/delivery/ex
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
** Last update Thu May 11 12:58:14 2017 Thibaut Cornolti
*/
#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "get_next_line.h"
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"

int		main(int ac, char **av, char **env)
{
  void		*root;
  t_syntax	*syntax;
  t_status	status;
  t_info	*info;
  char		*str;

  syntax = get_syntax();
  info = get_info(env);
  my_memset(&status, 0, sizeof(status));
  if (isatty(0))
    my_printf("$> ");
  while ((str = get_next_line(0)))
    {
      if ((root = parse_cmd(syntax, str)))
	{
	  //	  show_nodes(root, 0, 0);
	  auto_select(root, &status, info);
	  my_free_tree(&root);
	}
      if (isatty(0))
	my_printf("$> ");
    }
  free_syntax(&syntax);
  free_info(info);
  UNUSED(av);
  UNUSED(ac);
  return (0);
}
