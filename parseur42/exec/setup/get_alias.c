/*
** alias.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh/parseur 42/exec/setup
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Fri May 12 15:28:34 2017 Bastien
** Last update Mon May 15 17:11:41 2017 Bastien
*/

#include <string.h>
#include <fnmatch.h>
#include "syntax.h"
#include "exec.h"

static int	verify_cmd(t_token **save, t_token *token, t_info *info, t_syntax *syntax)
{
  int		i;
  t_token	*new;

  i = -1;
  while (info->alias[++i].link)
    if (!strcmp(info->alias[i].link, token->token))
      {
	new = get_token(info->alias[i].value, syntax);
	new->prev = token->prev;
	token->prev->next = new;
	while (new->next)
	  new = new->next;
	new->next = token->next;
	token->next->prev = new;
	if (!token->prev)
	  *save = new;
	my_free_token(&token);
	return (1);
      }
  return (0);
}

static t_token 	*check_alias(t_token *token, t_info *info, t_syntax *syntax)
{
  int		count;
  t_token	*temp;

  temp = token;
  count = -1;
  while (temp && ++count < 1000)
    {
      if (temp->type & T_COMMAND)
	{
	  if (verify_cmd(&token, temp, info, syntax))
	    temp = token;
	  else
	    temp = temp->next;
	}
    }
  my_free_token(&temp);
  return (token);
}

t_token	*get_alias(t_token *token, t_info *info, t_syntax *syntax)
{
  if (!info->alias)
    return (token);
  token = check_alias(token, info, syntax);
  return (token);
}
