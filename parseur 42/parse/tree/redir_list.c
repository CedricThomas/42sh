/*
** redir_list.c for parseur 42 in /home/cedric/delivery/PSU/PSU_2016_42sh/parseur 42
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Thu May  4 21:28:56 2017 
** Last update Thu May  4 22:07:21 2017 
*/
#include <stdlib.h>
#include "my_alloc.h"
#include "syntax.h"
#include "match.h"

static int	get_tag(char *type)
{
  int		flag;

  flag = 0;
  if (advanced_match(type, "*<<*") || advanced_match(type, "*>>*"))
    flag += DOUBLE;
  if (advanced_match(type, "*<*"))
    {
      flag += STDIN;
      return (flag);
    }
  if (advanced_match(type, "2{>>, >}") ||
      advanced_match(type, "&{>>, >}"))
    flag += STDERROR;
  if (advanced_match(type, "1{>>, >}") ||
      advanced_match(type, "&{>>, >}"))
    flag += STDOUT;
  return (flag);
}

int		add_redir_list(t_redir **my_redir, char *file, char *type)
{
  t_redir	*elem;

  if ((elem = my_alloc(sizeof(t_redir))) == NULL)
    exit(84);
  elem->tag = get_tag(type);
  if ((elem->file = alloc_strdup(file)) == NULL)
    exit(84);
  elem->next = *my_redir;
  *my_redir = elem;
  return (0);
}
