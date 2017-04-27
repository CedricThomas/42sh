/*
** main.c for mysh in /home/cedric/delivery/ex
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
** Last update Thu Apr  6 11:13:56 2017 Cédric Thomas
*/
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "mysh.h"
#include "get_next_line.h"

void	free_info(t_info *info)
{
  int	i;

  i = -1;
  while (++i < BUILTINS_NB)
    if (info->builtins)
      free(info->builtins[i].builtins);
  free(info->builtins);
  free(info->old_pwd);
  free(info->pwd);
  free_tab(info->env);
  free_syntax(&(info->syntax));
}

static int	try_env(t_info *info, char **ae)
{
  char		*temp;

  info->last = 0;
  info->old_pwd = my_strdup("");
  if ((info->syntax = get_syntax()) == NULL)
    return (0);
  if ((info->env = tabdup(ae)) == NULL)
    return (0);
  temp = getcleanpwd();
  if (getkey(info->env, "PWD", 0) == NULL)
    info->env = addkey(info->env, "PWD", temp, 0);
  else
    changekey(info->env, "PWD", temp, 0);
  info->pwd = temp;
  temp = getcleanhostname();
  if (getkey(info->env, "HOST", 0) == NULL)
    info->env = addkey(info->env, "HOST", temp, 0);
  if ((info->builtins = get_builtins()) == NULL)
    return (0);
  free(temp);
  return (1);
}

void	reset_status(t_status *status)
{
  status->fd = NULL;
  free(status->piped);
  status->piped = NULL;
  status->pipe_max = 0;
  status->pipeline = NULL;
  status->status = 0;
  status->cmd = 0;
  status->forced = myfds(0, 1);
  status->exit = 0;
}

static int		run(t_info *info, int debug)
{
  t_status		status;
  t_node		*root;
  char			*cmd;

  print_prompt(info);
  status.exit = 0;
  status.piped = NULL;
  while (!status.exit && (cmd = get_next_line(0)))
    {
      if ((root = parse_cmd(info->syntax, cmd, info)) != NULL)
	{
	  if (debug)
	    show_nodes(root, 0, 0);
	  reset_status(&status);
	  search_actions(root, &status, info);
	  my_close_fd(&(status.fd), &(status.piped), &(status.pipe_max));
	  my_free_tree(&root);
	}
      if (!status.exit)
	print_prompt(info);
    }
  if (isatty(0) && status.exit >= 0)
    my_puterror("exit\n");
  return (info->last);
}

int		main(int ac, char **av, char **ae)
{
  int		debug;
  int		exit;
  t_info	info;

  debug = 0;
  if (ac == 2 && !my_strcmp(av[1], "-d"))
    debug = 1;
  signal(SIGINT, SIG_IGN);
  if (!try_env(&info, ae))
    return (84);
  exit = run(&info, debug);
  free_info(&info);
  return (exit);
}
