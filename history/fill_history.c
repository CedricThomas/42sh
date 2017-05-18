/*
** fill_history.c for 42sh in /home/maje/Dropbox/delivery/B2/PSU/PSU_2016_42sh
** 
** Made by maje
** Login   <marin.brunel@epitech.eu>
** 
** Started on  Thu May 18 09:56:38 2017 maje
** Last update Thu May 18 17:31:26 2017 maje
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
#include <time.h>
#include "get_next_line.h"
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"

static char	*changeint_to_str(int nb)
{
  char		*str;
  int		i;

  if ((str = malloc(sizeof(char) * 11)) == NULL)
    exit(84);
  i = 9;
  while (i >= 0)
    {
      str[i] = nb % 10 + '0';
      nb /= 10;
      i--;
    }
  str[10] = '\0';
  return (nb);
}

int	fill_history(char *cmd, t_info *info)
{
  int	i;

  i = 0;
  while (info->hist[i])
    i++;
  if ((info->history = realloc(info->history, (((i+1) + 1) * sizeof(char*)))) == NULL)
    exit(84);
  info->history[i] = my_strcatdup(my_strdup(changeint_to_str(time(NULL))), cmd, 1);
  info->history[i+1] = '\0';
  i = -1;
}
