/*
** rc.c for rc in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon May 15 13:59:16 2017 Thibaut Cornolti
** Last update Mon May 15 14:30:03 2017 Thibaut Cornolti
*/

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"
#include "get_next_line.h"

static char	*get_filename(t_info *info)
{
  char		*home;
  char		*path;

  if ((home = getkey(info->env, "HOME", 1)) == NULL)
    return (NULL);
  if ((path = malloc(sizeof(char) *
		     (strlen(home) + strlen(FILE_RC) + 2))) == NULL)
    return (NULL);
  strcpy(path, home);
  strcat(path, "/");
  strcat(path, FILE_RC);
  free(home);
  return (path);
}

void		load_rc(t_status *status, t_info *info, t_syntax *syntax)
{
  int		fd;
  char		*filename;
  void		*root;
  char		*cmd;

  if ((filename = get_filename(info)) == NULL)
    return ;
  if ((fd = open(filename, O_RDONLY)) < 0)
    return ;
  free(filename);
  while (!status->exit && (cmd = get_next_line(fd)))
    {
      if ((root = parse_cmd(syntax, cmd)))
	{
	  auto_select(root, status, info);
	  my_free_tree(&root);
	}
    }
}
