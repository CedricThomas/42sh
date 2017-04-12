/*
** my_str_to_wordtab.c for my_str_to_wordtab in /home/thibrex/delivery/CPool_Day08
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu@epitech.net>
** 
** Started on  Wed Oct 12 11:08:17 2016 Thibaut Cornolti
** Last update Tue Jan 17 00:03:45 2017 Thibaut Cornolti
*/

#include <stdlib.h>
#include "my.h"

static int	get_word_count(char *str, char split)
{
  int		count;
  int		i;

  i = 0;
  count = 0;
  while (str[i] != 0)
    {
      if (str[i] == split)
	count += 1;
      i += 1;
    }
  return (count + 1);
}

static char	**init_tab(char *str, char **tab, char split)
{
  int		i;
  int		count;
  int		word;

  i = 0;
  count = my_strlen(str);
  word = get_word_count(str, split);
  tab = malloc(sizeof(char *) * (word + 2));
  if (tab == NULL)
    exit(my_puterror("error") + 84);
  while (word >= 0)
    {
      if ((tab[word] = malloc(sizeof(char) * count + 1)) == NULL)
	exit(my_puterror("error") + 84);
      tab[word][0] = 0;
      word -= 1;
    }
  return (tab);
}

char	**my_strsplit(char *str, char split)
{
  int	i;
  int	j;
  int	k;
  char	**wordtab;

  wordtab = init_tab(str, wordtab, split);
  i = -1;
  j = 0;
  k = 0;
  while (str[++i] != 0)
      if (str[i] == split && k != 0)
	{
	  k = 0;
	  j += 1;
	}
      else if (str[i] != split)
	{
	  wordtab[j][k] = str[i];
	  wordtab[j][k + 1] = 0;
	  k += 1;
	}
  if (wordtab[j][0] == 0)
    wordtab[j] = NULL;
  wordtab[j + 1] = NULL;
  return (wordtab);
}
