/*
** my_strncmp.c for my_strncmp in /home/thibrex/delivery/CPool_Day06/tests
** 
** Made by Cornolti Thibaut
** Login   <thibrex@epitech.net>
** 
** Started on  Mon Oct 10 11:40:45 2016 Cornolti Thibaut
** Last update Thu May 11 14:00:59 2017 maje
*/

int	my_strncmp(char *s1, char *s2, int l)
{
  int	i;

  i = 0;
  while (l > i && s1[i] != 0 && s2[i] != 0)
    {
      if (s1[i] != s2[i])
	return ((s1[i] - s2[i] < 0) ? -1 : 1);
      i += 1;
    }
  return (0);
}
