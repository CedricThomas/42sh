/*
** main.c for main.c in /home/cedric/delivery/ex
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
** Last update Tue May  9 12:54:50 2017 
*/
#include "my.h"
#include "get_next_line.h"
#include "syntax.h"
#include "exec.h"

int		main(int ac, char **av, char **env)
{
  void		*root;
  t_syntax	*syntax;
  t_info	*info;
  char		*str;

  syntax = get_syntax();
  info = get_info(env);
  while ((str = get_next_line(0)))
    {
      if ((root = parse_cmd(syntax, str)))
	{
	  show_nodes(root, 0, 0);
	  auto_select(root, NULL, info);
	  my_free_tree(&root);
	}
    }
  free_syntax(&syntax);
  free_info(info);
  UNUSED(av);
  UNUSED(ac);
  return (0);
}
