/*
** shape_it.c for parseur in /home/cedric/delivery/parseur_ll/lexer
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Thu Mar 23 17:12:35 2017 
** Last update Fri May 12 13:47:56 2017 
*/
#include <stdlib.h>
#include "my.h"
#include "syntax.h"

char	*shape_str(char *str)
{
  char	**delim;

  delim = tab_create(8, ";", "||", "&&", "|",
		     ">>", ">",
		     "1>>", "1>",
		     "2>>", "2>",
		     "&>>", "&>",
		     "\\<\\<", "\\<");
  str = shape_separator(str, delim);
  free_tab(delim);
  return (str);
}
