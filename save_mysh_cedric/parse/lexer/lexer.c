/*
** lexer.c for parseur in /home/cedric/delivery/parseur_ll
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Wed Mar 22 22:10:45 2017
** Last update Thu Mar 30 21:04:43 2017 
*/
#include <unistd.h>
#include <stdlib.h>
#include "syntax.h"
#include "my.h"

int	auto_cmp(char *str, t_syntax my_syntax, int index)
{
  int	type;
  char	*pattern;
  int	quote;
  int	i;

  i = -1;
  quote = 0;
  type = my_syntax.weight;
  pattern = my_syntax.values[index];
  if (INIBED(type))
    while (str[++i] && (quote || !is_in(str[i], SKIP)))
      {
	if (is_in(str[i], INIB) && !quote || quote == str[i])
	  quote = (!quote ? str[i] : 0);
      }
  else
    if (!my_strncmp(pattern, str, my_strlen(pattern)))
      return (my_strlen(pattern));
  return (i);
}

int		match_pattern(int *size, char *str, t_syntax *my_syntax)
{
  int		j;
  int		i;

  i = -1;
  while (my_syntax[++i].weight > 0)
    {
      j = -1;
      while (my_syntax[i].values[++j])
	{
	  *size = auto_cmp(str, my_syntax[i], j);
	  if (*size > 0)
	    return (UNTAG(my_syntax[i].weight, INIB_ON));
	}
    }
}

static int      checkdouble(char *str)
{
  int		i;
  char		quote;

  i = -1;
  quote = 0;
  while (str && str[++i])
    if (quote == 0 && is_in(str[i], INIB) || str[i] == quote)
      quote = (!quote ? str[i] : 0);
  if (quote)
    {
      my_puterror("Unmatched ");
      write(2, &quote, 1);
      my_puterror(".\n");
    }
  return (!quote ? 1 : 0);
}

t_token		*get_token(char *str, t_syntax *my_syntax)
{
  t_token	*token;
  int		type;
  int		size;
  int		idx;

  idx = 0;
  token = NULL;
  if (!checkdouble(str))
    return (my_free_null(str));
  str = shape_for_token(str, my_syntax);
  while (str[idx])
    {
      size = 0;
      while (is_in(str[idx], SKIP))
	idx += 1;
      type = match_pattern(&size, str + idx, my_syntax);
      my_put_list_token(&token, my_strndup(str + idx, size), type);
      idx += size;
      while (is_in(str[idx], SKIP))
	idx += 1;
    }
  if (redefine_tokens(&token))
    return (my_free_null(str));
  free(str);
  return (token);
}
