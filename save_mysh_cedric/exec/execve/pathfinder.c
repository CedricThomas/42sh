/*
** fork.c for mysh.c in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue Jan 10 16:30:38 2017 
** Last update Thu Apr  6 07:57:35 2017 Cédric Thomas
*/
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

void		check_error(char *pathabs, t_info *info, char *str)
{
  int		isadir;
  t_stat	mstat;

  isadir = 0;
  if (!stat(pathabs, &mstat))
    isadir = S_ISDIR(mstat.st_mode);
  if (pathabs && (access(pathabs, F_OK) || !is_in('/', pathabs)))
    {
      my_puterror(str);
      my_puterror(": Command not found.\n");
      info->last = 1;
    }
  else if (pathabs && access(pathabs, X_OK) || isadir)
    {
      my_puterror(str);
      my_puterror(": Permission denied.\n");
      info->last = 1;
    }
}

char	*try_path(char *str, char **path, t_info *info)
{
  int	i;
  char	*pathabs;
  int	baccess;

  i = -1;
  baccess = 0;
  pathabs = NULL;
  while (path[++i] && !baccess && !is_in('/', str))
    if (!access(str, X_OK) && !my_strncmp(str, "./", 2))
      baccess = 1;
    else if (!access(path[i], F_OK))
      {
	baccess = 1;
	if (!access(path[i], X_OK))
	  pathabs = my_strdup(path[i]);
      }
  free_tab(path);
  return (pathabs ? pathabs : my_strdup(str));
}

void	replacepath(t_info *info, t_toexec *exec, char **pathabs)
{
  int	i;
  char	**path;

  if ((path = my_split(getkey(info->env, "PATH", 0), ':')) == NULL)
    if ((path = my_split("/bin:/usr/bin", ':')) == NULL)
      exit(84);
  i = -1;
  while (path && path[++i])
    {
      if (path[i][my_strlen(path[i])] != '/')
	path[i] = strappend(path[i], "/", 1);
      path[i] = strappend(path[i], exec->argv[0], 1);
    }
  *pathabs = try_path(exec->argv[0], path, info);
  check_error(*pathabs, info, exec->argv[0]);
}

int		my_exec(t_info *info, t_toexec *exec, t_status *stat)
{
  char		*pathabs;
  int		ret;
  int		status;

  info->last = 0;
  replacepath(info, exec, &pathabs);
  ret = 0;
  if (!info->last)
    ret = my_fork(exec, pathabs, info, stat);
  else if (info->last && (stat->status & ON_PIPELINE) == ON_PIPELINE)
    my_put_list_exit(&(stat->pipeline), -1, info->last);
  free(pathabs);
  return (ret);
}
