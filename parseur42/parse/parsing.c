/*
** main.c for main.c in /home/cedric/delivery/ex
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
** Last update Mon May 15 14:42:54 2017 Thibaut Cornolti
*/
#include <stdlib.h>
#include "syntax.h"
#include "my.h"
#include "my_alloc.h"
#include "my_printf.h"

void		free_syntax(t_syntax **my_syntax)
{
  int		i;

  i = -1;
  while ((*my_syntax)[++i].values)
    {
      free_tab((*my_syntax)[i].values);
      free((*my_syntax)[i].already);
    }
  free(*my_syntax);
  *my_syntax = NULL;
}

t_syntax		*get_syntax()
{
  t_syntax		*my_syntax;

  if ((my_syntax = malloc(sizeof(t_syntax) *
			  (MAX_TYPES + 1))) == NULL)
    return (NULL);
  my_syntax[0] = syntax_create(T_SEPAR, 1, ";");
  my_syntax[1] = syntax_create(T_LOGIC, 2, "&&", "||");
  my_syntax[2] = syntax_create(T_FLUX, 1, "|");
  my_syntax[3] = syntax_create(T_FLUX_REDIR_OUT, 8,
			       ">>", ">", "2>>", "2>",
			       "1>>", "1>", "&>>", "&>");
  my_syntax[4] = syntax_create(T_FLUX_REDIR_IN, 2, "\\<\\<", "\\<");
  my_syntax[5] = syntax_create(T_COMMON, 1, "#");
  my_syntax[5].already[0] = ULIMT_MATCH;
  my_syntax[6].values = NULL;
  return (my_syntax);
}

static void		cut_comment(char *str)
{
  int			i;

  i = -1;
  if (!str[0])
    return ;
  while (str[++i] && str[i] != '#');
  if (i == 0 || (i != 0 && (str[i - 1] == ' ' || str[i - 1] == '\t')))
    str[i] = 0;
  else
    cut_comment(str + i + 1);
}

t_node			*parse_cmd(t_syntax *my_syntax, char *str)
{
  t_token		*tokens;
  void			*root;

  cut_comment(str);
  if ((tokens = get_token(str, my_syntax)) == NULL)
    return (NULL);
  if ((root = auto_create_node(NULL, tokens, NULL)) == NULL)
    my_free_tree(&root);
  my_free_token(&tokens);
  return (root);
}
