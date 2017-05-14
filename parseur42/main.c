/*
** main.c for main.c in /home/cedric/delivery/ex
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
** Last update Fri May 12 18:44:53 2017 
*/
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "my.h"
#include "get_next_line.h"
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"

static int	setup_sh(t_syntax **syntax, t_info **info,
			 t_status *status, char **env)
{
  if ((*syntax = get_syntax()) == NULL)
    return (1);
  if ((*info = get_info(env)) == NULL)
    return (1);
  my_memset(status, 0, sizeof(t_status));
  return (0);
}

static int	free_sh(t_syntax *syntax, t_info *info)
{
  int		exit;

  exit = info->exit_value;
  free_syntax(&syntax);
  free_info(info);
  return (exit);
}

int		main(int ac, char **av, char **env)
{
  void		*root;
  t_syntax	*syntax;
  t_status	status;
  t_info	*info;
  char		*cmd;

  if (setup_sh(&syntax, &info, &status, env))
    return (84);
  if (isatty(0))
    print_prompt(info);
  while (!status.exit && (cmd = get_next_line(0)))
    {
      if ((root = parse_cmd(syntax, cmd)))
	{
	  //	  show_nodes(root, 0, 0);
	  auto_select(root, &status, info);
	  my_free_tree(&root);
	}
      if (!status.exit && isatty(0))
	print_prompt(info);
    }
  if (isatty(0))
    my_putstr("exit\n");
  return (free_sh(syntax, info));
}