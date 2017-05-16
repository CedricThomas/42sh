/*
** main.c for main.c in /home/cedric/delivery/ex
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
** Last update Tue May 16 15:17:15 2017 Thibaut Cornolti
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

int		my_system(const char *command, t_system *system)
{
  void		*root;
  t_syntax	*syntax;
  t_status	status;
  t_info	*info;

  if (!system)
    {
      if (setup_sh(&syntax, &info, &status, env))
	return (84);
      load_rc(&status, info, syntax);
    }
  else
    {
      syntax = system->syntax;
      status = *(system->status);
      info = system->info;
    }
  if ((root = parse_cmd(syntax, command, info)))
    {
      auto_select(root, &status, info);
      my_free_tree(&root);
    }
  else
    auto_wait(&status, info);
  return (info->exit_value);  
}

int		main(int ac, char **av, char **env)
{
  void		*root;
  t_syntax	*syntax;
  t_status	status;
  t_info	*info;
  char		*cmd;

  UNUSED(ac);
  UNUSED(av);
  if (setup_sh(&syntax, &info, &status, env))
    return (84);
  if (isatty(0))
    print_prompt(info);
  load_rc(&status, info, syntax);
  while (!status.exit && (cmd = get_next_line(0)))
    {
      if ((root = parse_cmd(syntax, cmd, info)))
	{
	  auto_select(root, &status, info);
	  my_free_tree(&root);
	}
      else
	auto_wait(&status, info);
      if (!status.exit && isatty(0))
	print_prompt(info);
    }
  if (isatty(0))
    my_putstr("exit\n");
  return (free_sh(syntax, info));
}
