/*
** fill_history.c for 42sh in /home/maje/Dropbox/delivery/B2/PSU/PSU_2016_42sh
** 
** Made by maje
** Login   <marin.brunel@epitech.eu>
** 
** Started on  Thu May 18 09:56:38 2017 maje
** Last update Thu May 18 18:45:23 2017 Cédric THOMAS
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "syntax.h"
#include "exec.h"

static char		*get_path_history(t_info *info)
{
  int		len;
  char		*home;
  char		*path;

  if ((home = getkey(info->env, "HOME", 0)) == NULL)
    return (NULL);
  len = my_strlen(home);
  if (len > 0 && home[len - 1] != '/')
    path = my_strcatdup("/", FILE_HISTORY, 0);
  else
    path = my_strdup(FILE_HISTORY);
  if (path)
    path = my_strcatdup(home, path, 2);
  return (path);
}

int			write_history(t_info *info)
{
  char		*path;
  int		fd;
  t_history	*tmp;

  tmp = info->histo->start;
  if ((path = get_path_history(info)) == NULL)
    return (1);
  if ((fd = open(path, O_RDONLY)) == -1)
    return (1);
  free(path);
  while (tmp)
    {
      dprintf("%ld#%s", tmp->time, tmp->cmd);
      tmp = tmp->next;
    }
  close(fd);
  return (0);
}

static void	put_history(t_info *info, long time, char *cmd)
{
  if (info->histo->start == NULL)
    {
      my_put_list_history(&info->histo->start, cmd, time);
      info->histo->current = info->histo->start;
    }
  else
    {
      my_put_list_history(info->histo->current, cmd, time);
      info->histo->current = info->histo->current->next;
    }
}

int	load_history(t_info *info)
{
  char		*path;
  long		time;
  char		*cmd;
  FILE		*stream;
  char		*line;
  size_t	len;
  ssize_t	read;

  if ((path = get_path_history(info)) == NULL)
    return (1);
  if ((stream = fopen(path, "r")) == NULL)
    return (1);
  free(path);
  len = 0;
  line = NULL;
  while ((getline(&line, &len, stream)) != -1)
    {
      sscanf(line, "%ld#%s", &time, &cmd);
      put_history(info, time, cmd);
      free(line);
    }
  info->histo->end = info->histo->current;
  fclose(stream);
  return (0);
}
