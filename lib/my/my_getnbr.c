/*
** my_getnbr.c for my_getnbr in /home/thibrex/delivery/CPool_Day04
** 
** Made by Cornolti Thibaut
** Login   <thibrex@epitech.net>
** 
** Started on  Thu Oct  6 19:20:57 2016 Cornolti Thibaut
** Last update Fri Jan 20 12:42:07 2017 Thibaut Cornolti
*/

#include <unistd.h>
#include "my.h"

int	my_getnbr(char *str)
{
  int	nbr;

  if (str == NULL)
    return (0);
  nbr = my_getnbr_base(str, "0123456789");
  return (nbr);
}
