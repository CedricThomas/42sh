/*
** misc.c for gnc in /home/cedric/Desktop/get_next_cmd
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sat Apr 22 11:50:50 2017 
** Last update Wed May 17 14:20:05 2017 Cédric THOMAS
*/
#include <curses.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <termio.h>
#include "get_next_command.h"
#include "my.h"
#include "my_printf.h"
#include "syntax.h"
#include "exec.h"
#include "my_alloc.h"

char	*delete_a_char(char *str, int index)
{
  int	nb;
  char	*first;
  char	*second;
  char	*full;

  nb = 1;
  if (str == NULL)
    return (NULL);
  if ((first = my_strndup(str, index)) == NULL)
    return (NULL);
  if ((second = my_strdup(str + index + nb)) == NULL)
    return (NULL);
  if ((full = my_strcatdup(first, second, 3)) == NULL)
    return (NULL);
  free(str);
  return (full);
}

char		*insert_str(char *s1, char *s2, int pos)
{
  int	len2;
  char	*dest;
  int	len;

  len = 0;
  if (s1 != NULL)
    len = my_strlen(s1);
  len2 = my_strlen(s2);
  if ((dest = malloc(sizeof(char) * (len + len2 + 1))) == NULL)
    return (NULL);
  dest[0] = 0;
  if (s1)
    {
      my_strncpy(dest, s1, pos);
      dest[pos] = 0;
    }
  dest = my_strcat(dest, s2);
  if (s1)
    my_strcat(dest, s1 + pos);
  free(s1);
  return (dest);
}

void		print_line(t_keypad *pad)
{
  int		len;
  char		*seq;

  if (isatty(0))
    print_prompt(pad->sys->info);
  if (pad->line)
    {
      my_printf(pad->line);
      if ((seq = tigetstr("cub1")) == (char *) -1)
  	return ;
      len = my_strlen(pad->line) + 1;
      while (--len > pad->index)
    	my_printf(seq);
    }
}
