/*
** fct_history.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/history
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Sat May 20 15:39:02 2017 Thibaut Cornolti
** Last update Sat May 20 16:04:51 2017 Thibaut Cornolti
*/

#include <termio.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"
#include "get_next_command.h"

char	*history_fct_exclam(char *src, int idx, t_history_info *history)
{
  delete_nbchar(src, 1, idx);
  insert_str(src, history->end->cmd, idx, 0);
  return (src);
}

char	*history_fct_dollar(char *src, int idx, t_history_info *history)
{
  
  return (src);
}

char	*history_fct_colon(char *src, int idx, t_history_info *history)
{

  return (src);
}

char	*history_fct_dash(char *src, int idx, t_history_info *history)
{

  return (src);
}

char	*history_fct_number(char *src, int idx, t_history_info *history)
{

  return (src);
}
