/*
** match.c for CPool_matchnmatch in /home/cedric/delivery/matchnmatch
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Thu Oct 13 23:20:58 2016 Cédric Thomas
** Last update Sun Oct 16 12:23:23 2016 Cédric Thomas
*/

int	match(char *s1, char *s2)
{
  if (*s1 == '\0' && (*s2 == '\0' || (*s2 == '*' && *(s2 + 1) == '\0')))
    return (1);
  if (*s2 == '*' && *s1 != '\0')
    return (match(s1 + 1, s2) || match(s1, s2 + 1));
  else if (*s2 == '*' && *s1 == '\0')
    return (match(s1, s2 + 1));
  if (*s1 == *s2)
    return (match(s1 + 1, s2 + 1));
  else
    return (0);
}
