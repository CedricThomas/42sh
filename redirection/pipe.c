/*
** pipe.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell2
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Wed Apr  5 23:13:43 2017 Thibaut Cornolti
** Last update Sun Apr  9 16:23:08 2017 Thibaut Cornolti
*/

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"
#include "my.h"

static int	fct_pipe_close_1(t_ll *ll)
{
  if (close(1) < 0 ||
      dup2(ll->std_tmp[1], 1) < 0 ||
      close(ll->std_tmp[1]) < 0 ||
      close(ll->pipefd[1]) < 0)
    exit(84 + my_puterror("Fatal error: pipe"));
  return (0);
}

static int	fct_pipe_open_1(t_ll *ll)
{
  if (pipe(ll->pipefd) < 0 ||
      (ll->std_tmp[1] = dup(1)) < 0 ||
      close(1) < 0 ||
      dup2(ll->pipefd[1], 1) < 0)
    exit(84 + my_puterror("Fatal error: pipe"));
  return (0);
}

static int	fct_pipe_open_0(t_ll *ll)
{
  if ((ll->std_tmp[0] = dup(0)) < 0 ||
      close(0) < 0 ||
      dup2(ll->prev->pipefd[0], 0) < 0)
    exit(84 + my_puterror("Fatal error: pipe"));
  return (0);
}

static int	fct_pipe_close_0(t_ll *ll)
{
  if (close(0) < 0 ||
      dup2(ll->std_tmp[0], 0) < 0 ||
      close(ll->std_tmp[0]) < 0 ||
      close(ll->prev->pipefd[0]) < 0)
    exit(84 + my_puterror("Fatal error: pipe"));
  return (0);
}

int		fct_pipe(t_ll *ll, int tmp)
{
  if (tmp == 0)
    return (fct_pipe_open_1(ll));
  else if (tmp == 1)
    return (fct_pipe_close_1(ll));
  else if (tmp == 2)
    return (fct_pipe_open_0(ll));
  else if (tmp == 3)
    return (fct_pipe_close_0(ll));
  return (0);
}
