/*
** pipe.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar 29 21:29:03 2017 
** Last update Fri Apr  7 11:41:19 2017 
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

void		setexitvalue(t_status *status, t_info *info)
{
  int		last;
  t_exit	*tmp;

  tmp = status->pipeline;
  while (tmp)
    {
      if (WIFSIGNALED(tmp->exit))
  	check_sig(tmp->exit);
      if (tmp->exit)
	{
	  last = tmp->exit;
	  if (tmp->pid < 0)
	    info->last = last;
	  else if (WIFEXITED(last))
	    info->last = WEXITSTATUS(last);
	  else if (WIFSIGNALED(last))
	    info->last = last % 128 + 128;
	}
      tmp = tmp->next;
    }
}

void		wait_cmd(t_status *status, t_info *info)
{
  int		pid;
  int		i;
  int		last;

  my_close_fd(&(status->fd), &(status->piped), &(status->pipe_max));
  i = -1;
  while (++i < status->cmd)
    {
      pid = wait(&last);
      setlast(status->pipeline, pid, last);
    }
  setexitvalue(status, info);
  my_del_exit(&(status->pipeline));
}

void		pipe_and_send(t_node *root, t_status *status, t_info *info)
{
  int		pid;

  if (!search_double_input(root->left, status, info))
    {
      status->forced.out = status->piped[status->cmd * 2 + 1];
      pid = fork();
      if (pid == 0)
	{
	  status->status += ON_FORK;
	  search_actions(root->left, status, info);
	  exit(info->last);
	}
      else if (pid < 0)
	return (my_puterror("fork: Invalid fork stop of the pipeline.\n"));
      my_put_list_exit(&(status->pipeline), pid, 0);
    }
  else
    my_put_list_exit(&(status->pipeline), -1, 1);
  status->forced.in = status->piped[status->cmd * 2];
  status->forced.out = 1;
  status->cmd += 1;
  search_actions(root->right, status, info);
}

int		open_pipes(t_status *status, t_node *root)
{
  t_node	*temp;
  int           i;
  int		size;

  size = 0;
  temp = root;
  while (temp->type == T_FLUX)
    {
      size += 1;
      temp = temp->right;
    }
  if ((status->piped = malloc(sizeof(int) * (size * 2))) == NULL)
    exit(84);
  i = -1;
  while (++i < size)
    if (pipe(status->piped + i * 2) < 0)
      return (1);
  status->pipe_max = size;
  return (0);
}

t_fd		my_pipe(t_node *root, t_status *status, t_info *info)
{
  int		first;

  first = 0;
  if ((status->status & ON_PIPELINE) != ON_PIPELINE)
    {
      first = 1;
      status->status += ON_PIPELINE;
      if (open_pipes(status, root))
	{
	  my_puterror("Can't make pipe\n");
	  info->last = 1;
	  return (myfds(0, 1));
	}
    }
  pipe_and_send(root, status, info);
  if (first)
    wait_cmd(status, info);
  return (status->forced);
}
