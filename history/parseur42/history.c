/*
** history.c for 42sh in /home/maje/Dropbox/delivery/B2/PSU/PSU_2016_42sh/marin
** 
** Made by maje
** Login   <marin.brunel@epitech.eu>
** 
** Started on  Tue May  9 14:18:09 2017 maje
** Last update Mon May 15 15:48:09 2017 maje
*/

//#include "my.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	create_file()
{
  FILE	*fp;

  if ((fp = fopen("/home/usr/.42sh_hystory", "rw")) == NULL)
    return (-1);
  printf("lol\n");
  return (0);
}

char	**read_hystory()
{
  char	**tab;
  char	*buf;

  
  return (tab);
}

int	check_file()
{
  FILE	*file;

  if ((file = fopen("/home/usr/.42sh_hystory", "r")) == NULL)
    return (-1);
  else
    return (0);
}
