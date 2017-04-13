/*
** search_path.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell1
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Tue Jan 17 23:48:38 2017 Thibaut Cornolti
** Last update Thu Mar 23 14:03:39 2017 Thibaut Cornolti
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "my.h"
#include "sh.h"

char		*search_local_path(char ***ae, char *cmd)
{
  struct stat	st;

  stat(cmd, &st);
  if (access(cmd, F_OK) == -1)
    return (cmd);
  else if (S_ISDIR(st.st_mode) || access(cmd, X_OK) == -1)
    {
      assist_add_env("LAST_RETURN",
		     my_int_to_str(my_msg(cmd, NULL, -1) + 2, NULL), ae);
      return (NULL);
    }
  return (cmd);
}

static int	fill_sp_d(char ***ae, char *cmd, t_sp_d *d)
{
  if ((d->rs = malloc((my_strlen(cmd)
		       + my_strlen(my_getenv(*ae, "PATH"))
		       + 16) * sizeof(char))) == NULL)
    return (-1);
      d->i = -1;
  if (my_getenv(*ae, "PATH"))
    d->path = get_argv(my_getenv(*ae, "PATH"), ':');
  else
    {
      if ((d->path = malloc(sizeof(char *) * 5)) == NULL)
	return (-1);
      d->path[0] = my_strdup("/usr/local/bin");
      d->path[1] = my_strdup("/usr/bsd");
      d->path[2] = my_strdup("/bin");
      d->path[3] = my_strdup("/usr/bin");
      d->path[4] = NULL;
    }
  return (0);
}

char		*search_path(char ***ae, char *cmd)
{
  t_sp_d	d;
  struct stat	st;

  if (fill_sp_d(ae, cmd, &d) == -1)
    return ((char *) (long) 1);
  while (d.path != NULL && d.path[++d.i])
    {
      my_strcpy(d.rs, d.path[d.i]);
      my_strcat(d.rs, "/");
      my_strcat(d.rs, cmd);
      stat(d.rs, &st);
      if (access(d.rs, F_OK) == -1);
      else if (S_ISDIR(st.st_mode) || access(d.rs, X_OK) == -1)
	{
	  assist_add_env("LAST_RETURN", my_int_to_str(my_msg(d.rs, NULL, -1)
						     + 2, NULL), ae);
	  return ((char *) (long) (free_argv(&(d.path)) * 0));
	}
      else
	return (free_argv(&(d.path)) + d.rs);
    }
  free_argv(&(d.path));
  return ((char *) (long) 1);
}
