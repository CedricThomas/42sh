/*
** my_strcmp.c for my_strcmp in /home/thibrex/delivery/CPool_Day06/tests
** 
** Made by Cornolti Thibaut
** Login   <thibrex@epitech.net>
** 
** Started on  Mon Oct 10 11:28:45 2016 Cornolti Thibaut
** Last update Mon Jan 16 16:59:57 2017 Thibaut Cornolti
*/

#include <unistd.h>

int	my_strcmp(char *s1, char *s2)
{
  int	i;

  i = 0;
  while (s1[i] != 0 || s2[i] != 0)
    {
      if (s1[i] != s2[i])
	return ((s1[i] - s2[i] < 0) ? -1 : 1);
      i += 1;
    }
  return (0);
}
