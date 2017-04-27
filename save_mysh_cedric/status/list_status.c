/*
** list_status.c for status in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by Cédric Thomas
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Apr  5 15:59:59 2017 Cédric Thomas
** Last update Tue Apr 11 11:46:21 2017 
*/
#include <stdlib.h>
#include "mysh.h"
#include "my_printf.h"

int		my_put_list_exit(t_exit **ll, int pid, int last)
{
  t_exit	*tmp;
  t_exit	*elem;

  tmp = *ll;
  if ((elem = malloc(sizeof(*elem))) == NULL)
    exit(84);
  elem->pid = pid;
  elem->exit = last;
  elem->next = NULL;
  if (tmp == NULL)
    *ll = elem;
  else
    {
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = elem;
    }
  return (0);
}

int		my_del_exit(t_exit **ll)
{
  t_exit	*tmp;

  while (*ll)
    {
      tmp = *ll;
      *ll = (*ll)->next;
      free(tmp);
    }
}

void	show_exit_status(t_exit *ll)
{
  while (ll)
    {
      if (WIFSIGNALED(ll->exit))
	my_printf("exit error : %d, ", ll->exit);
      if (WIFEXITED(ll->exit))
	my_printf("exit : %d, ", WEXITSTATUS(ll->exit));
      my_printf("pid : %d\n", ll->pid);
      if (WIFSIGNALED(ll->exit))
	check_sig(ll->exit);
      else
	my_printf("\n");
      ll = ll->next;
    }
}

void	setlast(t_exit *ll, int pid, int exitval)
{
  while (ll)
    {
      if (ll->pid == pid)
	{
	  ll->exit = exitval;
	}
      ll = ll->next;
    }
}
