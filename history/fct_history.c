/*
** fct_history.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/history
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Sat May 20 15:39:02 2017 Thibaut Cornolti
** Last update Sat May 20 18:28:50 2017 Thibaut Cornolti
*/

#include <termio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"
#include "get_next_command.h"

char		*history_fct_exclam(char *src, int *idx, t_history_info *history)
{
  if (history->end == NULL || history->end->cmd == NULL)
    return (NULL);
  if ((src = delete_nbchar(src, 2, *idx)) == NULL)
    exit(84);
  if ((src = insert_str(src, history->end->cmd, *idx, 0)) == NULL)
    exit(84);
  *idx += my_strlen(history->end->cmd);
  return (src);
}

char		*history_fct_dollar(char *src, int *idx, t_history_info *history)
{
  t_token	*token;
  t_system	*sys;

  if (history->end == NULL || history->end->cmd == NULL)
    return (NULL);
  sys = getter_system(NULL);
  if ((token = get_token(history->end->cmd, sys->syntax, NULL)) == NULL)
    return (NULL);
  if (delete_nbchar(src, 1, *idx) == NULL ||
      insert_str(src, history->end->cmd, *idx, 0) == NULL)
    exit(84);  
  return (src);
}

char		*history_fct_colon(char *src, int *idx, t_history_info *history)
{
  if (delete_nbchar(src, 1, *idx) == NULL ||
      insert_str(src, history->end->cmd, *idx, 0) == NULL)
    exit(84);
  return (src);
}

char		*history_fct_dash(char *src, int *idx, t_history_info *history)
{
  t_history	*hist;
  int		nbr;
  int		size;

  if ((hist = history->end) == NULL)
    {
      *idx += 1;
      return (src);
    }
  nbr = atoi(src + *idx + 1);
  while (hist && ++nbr)
    hist = hist->prev;
  if (!hist)
    {
      dprintf(2, "%d: Event not found.\n", nbr + history->end->index);
      return (NULL);
    }
  size = -1;
  while (is_in(src[*idx + 1 + ++size], "-0123456789"));
  if ((src = delete_nbchar(src, size + 1, *idx)) == NULL)
    exit(84);
  if ((src = insert_str(src, hist->cmd, *idx, 0)) == NULL)
    exit(84);
  *idx += my_strlen(hist->cmd);
  return (src);
}

char		*history_fct_number(char *src, int *idx, t_history_info *history)
{
  t_history	*hist;
  int		nbr;
  int		size;

  if ((hist = history->start) == NULL)
    {
      *idx += 1;
      return (src);
    }
  nbr = atoi(src + *idx + 1);
  while (hist && hist->index != nbr)
    hist = hist->next;
  if (!hist)
    {
      dprintf(2, "%d: Event not found.\n", nbr);
      return (NULL);
    }
  size = -1;
  while (is_in(src[*idx + 1 + ++size], "0123456789"));
  if ((src = delete_nbchar(src, size + 1, *idx)) == NULL)
    exit(84);
  if ((src = insert_str(src, hist->cmd, *idx, 0)) == NULL)
    exit(84);
  *idx += my_strlen(hist->cmd);
  return (src);
}
