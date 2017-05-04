/*
** epurstr.c for asm in /home/cedric/delivery/CPE/CPE_2016_corewar/asm
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar  1 15:08:23 2017 
** Last update Thu May  4 14:01:50 2017 
*/

#include <stdlib.h>
#include "my.h"
#include "match.h"
#include "syntax.h"

static int	match_pattern(char *str, char **pattern, int *len)
{
  int		i;
  int		ret;
  char		*current;
  int		idx;

  ret = 0;
  i = -1;
  while (str[++i])
    {
      if ((current = my_strndup(str, i + 1)) == NULL)
	return (0);
      idx = -1;
      while (pattern[++idx])
	if (advanced_match(current, pattern[idx]))
	  {
	    *len = i + 1;
	    ret = 1;
	  }
      free(current);
    }
  if (ret)
    printf("len : %d\n", *len);
  return (ret);
}

static int	my_epur_size(char *str, char **sep_list)
{
  int	size;
  int	len;
  int	i;
  char	quote;

  i = -1;
  size = 0;
  quote = 0;
  while (str[++i])
    {
      if ((quote == 0 && is_in(str[i], INIB)) || str[i] == quote)
	quote = (!quote ? str[i] : 0);
      if (!quote && match_pattern(str + i, sep_list, &len))
	{
	  size += len + 1;
	  i += len - 1;
	}
      size += 1;
    }
  return (size);
}

static void	my_cpy(char *str, char *epured, char **sep_list)
{
  int		len;
  int		i;
  char		quote;
  int		j;

  i = -1;
  j = 0;
  quote = 0;
  while (str[++i])
    {
      if ((quote == 0 && is_in(str[i], INIB)) || str[i] == quote)
	quote = (!quote ? str[i] : 0);
      if (match_pattern(str + i, sep_list, &len) && !quote)
	{
	  my_strncpy(epured + j + 1, str + i, len);
	  j += len + 1;
	  i += len - 1;
	}
      else
	epured[j] = str[i];
      j += 1;
    }
  epured[j] = 0;
}

char	*shape_separator(char *str, char **sep_list)
{
  char	*epured;
  int	size;

  if (str == NULL || sep_list == NULL)
    return (NULL);
  size = my_epur_size(str, sep_list);
  printf("old : %d, new : %d\n", my_strlen(str), size);
  if ((epured = malloc(sizeof(char) * (size + 1))) == NULL)
    return (NULL);
  my_memset(epured, ' ', size);
  my_cpy(str, epured, sep_list);
  free(str);
  printf("epured : %s\n",epured);
  return (epured);
}
