/*
** dup.c for 42sh in /home/cedric/delivery/PSU/PSU_2016_42sh/parseur 42
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue May  9 16:12:11 2017 
** Last update Tue May  9 16:35:53 2017 
*/
#include <stdlib.h>
#include <unistd.h>
#include "syntax.h"
#include "exec.h"

void	my_undup(int save[3])
{
  int		i;

  i = 0;
  while (i <= 2)
    {
      if (save[i] != -1)
	{
	  if (dup2(save[i], i) < 0)
	    exit(84);
	  close(save[i]);
	}
    }
}

void	my_dup(t_command *cmd, int save[3])
{
  int		i;

  i = 0;
  while (i <= 2)
    {
      if (cmd->fd[i] != i)
	{
	  save[i] = dup(i);
	  if (dup2(cmd->fd[i], i) < 0)
	    exit(84);
	}
      else
	save[i] = -1;
      i += 1;
    }
}
