/*
** redirection.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell2
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Wed Apr  5 17:33:17 2017 Thibaut Cornolti
** Last update Sun Apr  9 16:21:49 2017 Thibaut Cornolti
*/

#include <fcntl.h>
#include <unistd.h>
#include "sh.h"
#include "my.h"

int		fct_srdd(t_ll *ll, int tmp)
{
  if (!tmp)
    {
      if (!ll->next)
	return (-1);
      ll->std_tmp[1] = dup(1);
      close(1);
      if (open(ll->next->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644) < 0)
	return (-1);
      return (0);
    }
  close(1);
  dup2(ll->std_tmp[1], 1);
  close(ll->std_tmp[1]);
  return (0);
}

int		fct_drdd(t_ll *ll, int tmp)
{
  if (!tmp)
    {
      if (!ll->next)
	return (-1);
      ll->std_tmp[1] = dup(1);
      close(1);
      if (open(ll->next->cmd,
	       O_WRONLY | O_CREAT | O_APPEND, 0644) < 0)
	return (-1);
      return (0);
    }
  close(1);
  dup2(ll->std_tmp[1], 1);
  close(ll->std_tmp[1]);
  return (0);
}

int		fct_srdg(t_ll *ll, int tmp)
{
  if (!tmp)
    {
      if (!ll->next)
	return (-1);
      ll->std_tmp[0] = dup(0);
      close(0);
      if (open(ll->next->cmd, O_RDONLY) < 0)
	return (-1);
      return (0);
    }
  close(0);
  dup2(ll->std_tmp[0], 0);
  close(ll->std_tmp[0]);
  return (0);
}

static int	fct_drdg_open(t_ll *ll)
{
  char		*gnl;
  int		pipefd[2];

  if (!ll->next)
    return (-1);
  if (pipe(pipefd) < 0)
    return (-1);
  ll->std_tmp[0] = dup(0);
  close(0);
  if (dup2(pipefd[0], 0) < 0)
    return (-1);
  my_putstr("? ");
  while ((gnl = get_next_line(ll->std_tmp[0])))
    {
      if (!my_strcmp(gnl, ll->next->cmd))
	break ;
      write(pipefd[1], gnl, my_strlen(gnl));
      write(pipefd[1], "\n", 1);
      my_putstr("? ");
    }
  close(pipefd[0]);
  close(pipefd[1]);
  return (0);
}

int		fct_drdg(t_ll *ll, int tmp)
{
  if (!tmp)
    return (fct_drdg_open(ll));
  close(0);
  dup2(ll->std_tmp[0], 0);
  close(ll->std_tmp[0]);
  return (0);
}
