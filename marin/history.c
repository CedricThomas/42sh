/*
** history.c for 42sh in /home/maje/Dropbox/delivery/B2/PSU/PSU_2016_42sh/marin
** 
** Made by maje
** Login   <marin.brunel@epitech.eu>
** 
** Started on  Tue May  9 14:18:09 2017 maje
** Last update Mon May 15 13:34:50 2017 maje
*/

//#include "my.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


char	*fill_history()
{
  int	fd;

  if ((fd = open("/home/usr/.42sh_hystory", O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH)) != -1)
    return (-1);
  
  printf("lol\n");
  return (0);
}

int	main(int ac, char **av)
{
  fill_history();
}
