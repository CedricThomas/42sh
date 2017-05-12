/*
** lexer.c for parseur in /home/cedric/delivery/parseur_ll
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Wed Mar 22 22:10:45 2017
** Last update Fri May 12 15:30:41 2017 Thibaut Cornolti
*/
#include <unistd.h>
#include <stdlib.h>
#include "syntax.h"
#include "match.h"
#include "my.h"

static int	change_len(int *last, int len, t_syntax *syntax)
{
  *last = len;
  return (syntax->weight);
}

static int	len_token(int *type, char *str, t_syntax *my_syntax)
{
  char		*current;
  int		i;
  int		j;
  int		len;
  int		last;

  len = 0;
  last = 0;
  while (str[++len - 1])
    {
      current = my_strndup(str, len);
      i = -1;
      while (my_syntax[++i].values)
	{
	  j = -1;
	  while (my_syntax[i].values[++j])
	    if (advanced_match(current, my_syntax[i].values[j]) &&
		*type <= my_syntax[i].weight)
	      *type = change_len(&last, len, &my_syntax[i]);
	}
      free(current);
    }
  return (last);
}

static char	*next_token(int *type, char *str, t_syntax *my_syntax)
{
  static int	idx = 0;
  int		len;
  char		*token;

  if (str == NULL || my_syntax == NULL)
    {
      idx = 0;
      return (NULL);
    }
  while (str[idx] && is_in(str[idx], SKIP))
    idx += 1;
  if (str[idx] == 0)
    return (NULL);
  *type = 0;
  len = len_token(type, str + idx, my_syntax);
  token = my_strndup(str + idx, len);
  idx += len;
  return (token);
}

t_token		*get_token(char *str, t_syntax *my_syntax)
{
  int		type;
  char		*current;
  t_token	*token;

  token = NULL;
  if (check_input_lexer(str))
    return (my_free_null(str));
  if ((str = shape_str(str)) == NULL)
    return (NULL);
  while ((current = next_token(&type, str, my_syntax)))
    if (my_put_list_token(&token, current, type))
      return (NULL);
  next_token(NULL, NULL, NULL);
  shape_token(token);
  free(str);
  return (token);
}
