/*
** main.c for main.c in /home/cedric/delivery/ex
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
<<<<<<< HEAD
** Last update Thu May 18 10:16:43 2017 maje
=======
** Last update Thu May 18 14:12:05 2017 Cédric THOMAS
>>>>>>> 6e63e9d3239a652d53f068dbdd309a1a7e746e52
*/
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <termio.h>
#include "my.h"
#include "get_next_command.h"
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"

void		signal_chld(int pid)
{
  kill(pid, SIGHUP);
}

static int	setup_sh(t_system *sys, char **env)
{
  if ((sys->syntax = get_syntax()) == NULL)
    return (1);
  if ((sys->info = get_info(env)) == NULL)
    return (1);
  if ((sys->keypad = init_keypad(sys)) == NULL)
    return (1);
  my_memset(sys->status, 0, sizeof(t_status));
  //signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
  signal(SIGTSTP, &signal_stp);
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);
  signal(SIGCHLD, &signal_chld);
  setpgid(getpid(), getpid());
  tcsetpgrp(0, getpgrp());
  getter_status(sys->status);
  return (0);
}

static int	free_sh(t_system *sys)
{
  int		exit;

  exit = sys->info->exit_value;
  free_syntax(&(sys->syntax));
  free_info(sys->info);
  end_keypad(sys->keypad);
  return (exit);
}

int		my_system(char *command, t_system *system)
{
  void		*root;

  if ((root = parse_cmd(system->syntax, command, system->info)))
    {
      auto_select(root, system->status, system->info);
      my_free_tree(&root);
    }
  else
    {
      auto_wait_job(system->status);
      if (!isatty(0))
	system->status->exit = 1;
    }
  print_wait_job(system->status);
  system->status->pgid = 0;
  return (system->info->exit_value);
}

int		main(int ac, char **av, char **env)
{
  t_system	system;
  t_status	status;
  char		*cmd;

  UNUSED(ac);
  UNUSED(av);
  system.status = &status;
  if (setup_sh(&(system), env))
    return (84);
  if (isatty(0))
    print_prompt(system.info);
  load_rc(system.status, system.info, system.syntax);
  my_set_term(system.keypad);
  while (!system.status->exit && (cmd = get_next_cmd(system.keypad)))
    {
      fill_history(cmd, system.info);
      my_reset_term(system.keypad);
      my_system(cmd, &system);
      if (!system.status->exit && isatty(0))
	print_prompt(system.info);
      my_set_term(system.keypad);
    }
  if (isatty(0))
    my_putstr("exit\n");
  return (free_sh(&system));
}
