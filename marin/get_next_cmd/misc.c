/*
** misc.c for gnc in /home/cedric/Desktop/get_next_cmd
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sat Apr 22 11:50:50 2017 
** Last update Mon Apr 24 09:39:46 2017 
*/
#include <stdarg.h>
#include <stdlib.h>
#include <termio.h>
#include "GNC.h"
#include "my.h"
#include "my_alloc.h"

void		my_putprintable(char *str, t_keypad *keypad)
{
  int		j;
  int		match;

  j = -1;
  match = 1;
  while (++j < KEY_LINKED && match == 1)
    if (!my_strcmp(keypad->key_parse[j].sequence, str))
      match = 0;
  if (match)
    my_putstr(str);
}

char		*my_seq(int size, ...)
{
  char	       *str;
  int		i;
  va_list	char_list;
  char		c;

  if ((str = my_alloc(sizeof(char) * (size + 1))) == NULL)
    return (NULL);
  my_tag_alloc(str, "seq", 's');
  va_start(char_list, size);
  i = -1;
  while (++i < size)
    {
      c = va_arg(char_list, int);
      str[i] = c;
    }
  str[i] = 0;
  va_end(char_list);
  return (str);
}

char		*insert_str(char *s1, char *s2, int pos, t_keypad *keypad)
{
  char	*dest;
  int	len;

  len = 0;
  if (s1 != NULL)
    len = my_strlen(s1);
  if ((dest = malloc(sizeof(char) * (len + my_strlen(s2) + 1))) == NULL)
    return (NULL);
  if (s1)
    my_strncpy(dest, s1, pos);
  my_strcpy(dest + pos, s2);
  if (s1)
    my_strcpy(dest + len + my_strlen(s2), s1 + pos);
  free(s1);
  if (pos != len)
    my_putprintable(dest + len + pos, keypad);
  return (dest);
}
