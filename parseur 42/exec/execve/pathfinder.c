/*
** fork.c for mysh.c in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue Jan 10 16:30:38 2017 
** Last update Thu May 11 16:33:52 2017 
*/
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "exec.h"
#include "my_alloc.h"
#include "my.h"

static int	check_error(char *path, t_info *info, char *exec_name)
{
  int		isadir;
  t_stat	mstat;

  isadir = 0;
  if (!stat(path, &mstat))
    isadir = S_ISDIR(mstat.st_mode);
  if (!path || (access(path, F_OK) || !is_in('/', path)))
    {
      my_puterror(exec_name);
      my_puterror(": Command not found.\n");
      return (1);
    }
  else if (path && access(path, X_OK) || isadir)
    {
      my_puterror(exec_name);
      my_puterror(": Permission denied.\n");
      return (1);
    }
  return (0);
}

static char	**get_full_path(t_info *info, char *exec_name)
{
  int		i;
  char		**paths;

  if ((paths = my_split(getkey(info->env, "PATH", 0), ':')) == NULL)
    if ((paths = my_split("/bin:/usr/bin", ':')) == NULL)
      exit(84);
  i = -1;
  while (paths[++i])
    {
      if (path[i][my_strlen(path[i])] != '/')
	path[i] = my_strcatdup(path[i], "/", 1);
      path[i] = my_strcatdup(path[i], exec->argv[0], 1);
    }
  return (path);
}

static char	*identify_path(char *exec_name, char **path, t_info *info)
{
  int   i;
  char  *my_path;
  int   baccess;

  i = -1;
  baccess = 0;
  my_path = NULL;
  while (path[++i] && !baccess)
    if (!access(path[i], F_OK))
      {
	baccess = 1;
	pathabs = my_strdup(path[i]);
      }
  free_tab(path);
  return (pathabs);
}

char		*my_pathfinder(t_command *cmd, t_status *status, t_info *info)
{
  char		*path;

  if (is_in('/', cmd->path))
    {
      if (!check_error(cmd->path, info, cmd->path))
	return (my_strdup(cmd->path));
      else
	return (NULL);
    }
  path = identify_path(exec_name, path, info);
  if (check_error(path, info, cmd->path))
    {
      free(path);
      path = NULL;
    }    
  return (path);
}
