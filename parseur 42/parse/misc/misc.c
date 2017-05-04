/*
** str.c for asm in /home/cedric/delivery/CPE/CPE_2016_corewar/asm
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar  1 15:05:53 2017 
** Last update Tue May  2 20:37:33 2017 
*/
#include <unistd.h>
#include <stdlib.h>
#include "my.h"

void	*my_free_null(void *ptr)
{
  free(ptr);
  return (NULL);
}

int	my_putfd(int fd, char *str)
{
  int	i;

  i = 0;
  if  (str == NULL)
    return (1);    
  while (str[i])
    i += 1;
  write(fd, str, i);
  return (1);
}
