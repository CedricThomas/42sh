/*
** main.c for main.c in /home/cedric/delivery/ex
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
** Last update Thu Apr 27 09:49:38 2017 
*/
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

void		free_syntax(t_syntax **my_syntax)
{
  int			i;

  i = -1;
  while ((*my_syntax)[++i].weight > 0)
    free_tab((*my_syntax)[i].values);
  free(*my_syntax);
  *my_syntax = NULL;
}

t_syntax		*get_syntax()
{
  t_syntax		*my_syntax;

  if ((my_syntax = malloc(sizeof(t_syntax) * (MAX_TYPES + 1))) == NULL)
    return (NULL);
  my_syntax[0].weight = T_SEPAR;
  my_syntax[0].values = tab_create(2, "&&", "||");
  my_syntax[1].weight = T_FLUX;
  my_syntax[1].values = tab_create(1, "|");
  my_syntax[2].weight = T_FLUX_REDIR;
  my_syntax[2].values = tab_create(4, ">>", "<<", ">", "<");
  my_syntax[3].weight = T_COMMON | INIB_ON;
  my_syntax[3].values = tab_create(1, "*");
  my_syntax[4].weight = -1;
  my_syntax[4].values = NULL;
  return (my_syntax);
}

t_node			*parse_cmd(t_syntax *my_syntax, char *str, t_info *info)
{
  int			ret;
  t_token		*tokens;
  t_node		*root;

  ret = 0;
  if ((tokens = get_token(str, my_syntax)) == NULL)
    return (NULL);
  root = create_tree(NULL, my_syntax, tokens, NULL);
  if (!ret && (ret += (check_syntax_redir_out(root)
		       || check_double_redir(root, '>'))))
    my_puterror("Ambigous output redirect.\n");
  if (!ret && (ret += (check_syntax_redir_in(root)
		       || check_double_redir(root, '<'))))
    my_puterror("Ambigous input redirect.\n");
  if (!ret && (ret += check_syntax_pipe(root)))
    my_puterror("Invalid null command.\n");
  my_free_token(&tokens);
  if (ret)
    {
      info->last = 1;
      my_free_tree(&root);
    }
  return (root);
}
