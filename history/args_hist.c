/*
** args_hist.c for hist in /home/cedric/delivery/PSU/PSU_2016_42sh/history
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sat May 20 13:43:45 2017 Cédric THOMAS
** Last update Sat May 20 16:19:13 2017 Cédric THOMAS
*/

#include <stdio.h>
#include <string.h>
#include "match.h"
#include "syntax.h"
#include "exec.h"

static void	fill_fct(char *pattern[6],
			 char *(*fct[6])(char *, int, t_history_info *))
{
  fct[0] = history_fct_exclam;
  fct[1] = history_fct_dollar;
  fct[2] = history_fct_colon;
  fct[3] = history_fct_dash;
  fct[4] = history_fct_number;
  fct[5] = NULL;
  pattern[0] = "!*";
  pattern[1] = "$*";
  pattern[2] = ":*";
  pattern[3] = "-*";
  pattern[4] = "*";
  pattern[5] = NULL;
}

int	get_index(char *cmd)
{
  int	i;
  int	backslash;

  i = -1;
  backslash = 0;
  while (cmd[++i] && !(cmd[i] == '!' && !backslash))
    {
      if (cmd[i] != '!' && backslash)
	backslash = 0;
      if (cmd[i] == '\\')
	backslash = 1;
    }
  if (!cmd[i])
    return (-1);
  return (i);
}

char	*change_hist(char *cmd, t_info *info)
{
  char	*flag[6];
  char	*(*fct[6])(char *, int, t_history_info *);
  int	index;
  int	i;

  fill_fct(flag, fct);
  while ((index = get_index(cmd)) > 0)
    {
      i = -1;
      while (flag[++i])
	if (advanced_match(cmd + index, flag[i]))
	  {
	    cmd = fct[i](cmd, index, info->histo);
	    //	    printf("%s\n", cmd);
	  }
    }
  return (cmd);
}
