/*
** auto_complete.c for 42sh in /home/cedric/Desktop/get_next_cmd
**
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Tue May 16 14:34:55 2017 Cédric THOMAS
** Last update Tue May 16 16:54:48 2017 Cédric THOMAS
*/
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <termio.h>
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"
#include "get_next_command.h"
#include "my.h"

/* static char	**add_to_tab(char **tab, char *str, int size) */
/* { */
/*   if ((tab = realloc(tab, (sizeof(char *) * size))) == NULL) */
/*     exit(84); */
/*   tab[size] = str; */
/*   return (tab); */
/* } */

/* static void	exec_cmd(char **tab) */
/* { */
/*   int		i; */
/*   char		*cmd; */

/*   i = -1; */
/*   if ((cmd = my_strdup("echo")) == NULL) */
/*     exit(84); */
/*   while (tab[++i]) */
/*     { */
/*       if ((cmd = my_strcatdup(cmd, " ", 1)) == NULL) */
/* 	exit(84); */
/*       if ((cmd = my_strcatdup(cmd, tab[i], 1)) == NULL) */
/* 	exit(84); */
/*     } */
/*   if ((cmd = my_strcatdup(cmd, t, 1)) == NULL) */
/*     exit(84); */
/*   my_printf(cmd); */
/* } */

/* static char		*get_folder(t_token *token) */
/* { */
/*   while () */
/* } */

/* static char		**get_file_list()
{
  struct dirent	**namelist;
  int		n;

  n = scandir(".", &namelist, NULL, alphasort);
  if (n < 0)
    perror("scandir");
  else {
    while (n--) {
      my_printf("%s\n", namelist[n]->d_name);
      free(namelist[n]);
    }
    free(namelist);
  }
return (0);
} */

int		auto_complete(t_keypad *key)
{
  t_token	*tokens;

  /* if ((tokens = get_token(my_strdup(key->line), key->sys->syntax)) == NULL) */
  /*   return (0); */
  return (0);
}
