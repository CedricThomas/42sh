/*
** fg.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon May 15 22:40:26 2017 Thibaut Cornolti
** Last update Tue May 16 14:51:08 2017 Thibaut Cornolti
*/

#include "syntax.h"
#include "exec.h"
#include "my.h"

void		builtin_fg(t_command *cmd, t_status *status, t_info *info)
{
  t_job		*job;

  job = status->job_list;
  while (job && job->status);
  if (!job)
    {
      my_puterror("fg: No current job.\n");
      return ;
    }
  my_put_list_exit(&(status->exit_list), job->pid, 0);
  job->status = 0;
}
