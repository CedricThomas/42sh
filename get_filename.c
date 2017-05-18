/*
** history.c for 42sh in /home/maje/Dropbox/delivery/B2/PSU/PSU_2016_42sh/marin
** 
** Made by maje
** Login   <marin.brunel@epitech.eu>
** 
** Started on  Tue May  9 14:18:09 2017 maje
** Last update Thu May 18 17:31:41 2017 maje
*/

#include "my.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "get_next_line.h"
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"

static char     *get_filename(t_info *info)
{
  char          *home;
  char          *path;

  if ((home = getkey(info->env, "HOME", 1)) == NULL)
    return (NULL);
  if ((path = malloc(sizeof(char) *
		     (strlen(home) + strlen(FILE_HISTORY) + 2))) == NULL)
    return (NULL);
  strcpy(path, home);
  strcat(path, "/");
  strcat(path, FILE_HISTORY);
  free(home);
  return (path);
}

int	create_file(t_info *info)
{
  FILE	*fp;
  char	*path;

  if ((path = get_filename(info)) == NULL)
    return (-1);
  if ((fp = fopen(path, "w")) == NULL)
    {
      perror("fopen");
      return (-1);
    }
  fclose(fp);
  free(path);
  return (0);
}

static int	*size_read(char	*str)
{
  int	i[2];
  char	c;
  int	fd;

  if ((fd = open(str, O_RDONLY)) == -1)
    return (-1);
  i[0] = 0;
  i[1] = 0;
  while (read(fd, &c, 1) > 0)
    {
      if (c == '\n')
	i[1] += 1;
      i[0]++;
    }
  close(fd);
  return (i);
}

char		**read_history(t_info *info)
{
  char		**tab;
  char		*buf;
  char		*path;
  int		size[2];
  int		fd;
  int		i;

    if ((path = get_filename(info)) == NULL)
    return (-1);
  if (access(path, R_OK))
    return (NULL);
  if ((fd = open(path, O_RDONLY)) == -1)
    return (NULL);
  if ((size = size_read(path)) == -1)
    return (NULL);
  if ((buf = malloc(sizeof(char) * (size[0] + 1))) == NULL)
    return (NULL);
  if (read(fd, buf, size[0]) == -1)
    return (NULL);
  buf[size[0]] = '\0';
  if ((info->hist = malloc(sizeof(t_info) * (size[1] + 1))) == NULL)
    exit(84);
  i = size[1];
  /* while (i > = */
  free(buf);
  close(fd);
  free(path);
  return (tab);
}
