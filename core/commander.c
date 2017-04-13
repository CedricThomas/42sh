/*
** commander.c for sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell1
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon Jan  2 18:26:13 2017 Thibaut Cornolti
** Last update Sat Apr  8 18:22:19 2017 Thibaut Cornolti
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include "my.h"
#include "sh.h"
#include "pars.h"

void		child_sig(int s)
{
  if (s == -1)
    signal(SIGSEGV, child_sig);
  else if (s == SIGSEGV)
    {
      exit(my_msg(NULL, NULL, 139));
    }
}

int		free_argv(char ***av)
{
  int		i;

  i = -1;
  if (*av != NULL)
    {
      while ((*av)[++i])
	free((*av)[i]);
      free(*av);
    }
  return (0);
}

void		commander_error(int ret, char ***ae)
{
  char		*r;
  int		sig;

  if (!WIFEXITED(ret))
    my_msg(NULL, NULL, ret);
  if (WIFSIGNALED(ret))
    if (ret == 2)
      sig = WTERMSIG(ret) + 128;
    else
      sig = (WCOREDUMP(ret)) ? WTERMSIG(ret) + 128:
	WTERMSIG(ret) + 128;
  else
    sig = WEXITSTATUS(ret);
  r = my_int_to_str(sig, NULL);
  if (sig)
    assist_add_env("LAST_RETURN", r, ae);
}

static void	commander_fork(char *tmp, char ***argv,
			       char ***ae, t_ll *ll)
{
  int		err;
  char		*cmd;

  cmd = (*argv)[0];
  if (cmd != NULL && cmd[0] != 0 && (ll->fork_pid = fork()) == 0)
    {
      child_sig(-1);
      err = execve(tmp, *argv, *ae);
      if (errno == ENOEXEC)
	exit(my_msg(cmd, NULL, -5) + 6);
      else if (err == -1)
      	exit(my_msg(cmd, NULL, 127) - 126);
      exit(0);
    }
  free_argv(argv);
}

void		commander(t_ll *ll, char ***ae)
{
  char		*cmd;
  char		**argv;
  int		argc;
  char		*tmp;

  argv = get_argv(ll->cmd, ' ');
  if (argv == NULL)
    return ;
  cmd = argv[0];
  argc = -1;
  while (argv[++argc]);
  if (check_slash(cmd))
    tmp = search_local_path(ae, cmd);
  else
    if ((tmp = search_path(ae, cmd)) == (char *) (long) 1)
      set_lr(my_msg(cmd, NULL, 127) - 126, ae);
  if (tmp != NULL && tmp != (char *) (long) 1)
    commander_fork(tmp, &argv, ae, ll);
}
