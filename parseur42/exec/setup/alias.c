/*
** alias.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh/parseur 42/exec/setup
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Fri May 12 15:28:34 2017 Bastien
** Last update Fri May 12 17:07:39 2017 Bastien
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fnmatch.h>
#include "syntax.h"

void	*add_alias(char *str, t_alias *alias)
{
  int	i;
  char	**tab;

  i = my_strtablen(alias);
  if (!(alias = realloc(sizeof(t_alias) * (i + 1))))
    return (NULL);
  if (!(tab = str_to_wordtab(str + 6, '=')))
    return (NULL);
  alias[i]->alias = tab[0];
  alias[i]->link = tab[1];
  free(tab);
  return (alias);
}

char		*check_alias(char *str, t_alias *alias, char **used)
{
  int		i;
  int		idx;
  t_command	*temp;

  i = -1;
  idx = 0;
  temp = 0;
  while (alias[++i]->alias)
    {
      if (!fnmatch(alias->alias, str, 0) &&
	  (idx = is_acmd((temp = get_token(str, alias->alias)))))
	replace_alias(str, alias[i], idx);
    }
  my_free_token(temp);
}

t_token			*get_alias(char *str, int cmd)
{
  static t_alias	*alias = 0;
  char			**used;

  if (!alias && cmd)
    return (get_token(str));
  if (!cmd)
    {
      alias = add_alias(str, alias);
      return (NULL);
    }
  while (str = check_alias(str, alias, used));
  return (get_token(cmd));
}
