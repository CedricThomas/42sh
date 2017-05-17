/*
** auto_complete.c for 42sh in /home/cedric/Desktop/get_next_cmd
**
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Tue May 16 14:34:55 2017 Cédric THOMAS
** Last update Wed May 17 10:11:09 2017 Cédric THOMAS
*/
#include <unistd.h>
#include <curses.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <termio.h>
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"
#include "get_next_command.h"
#include "my.h"
#include "match.h"

static void	exec_complete(char **tab, t_keypad *key)
{
  int		i;
  char		*cmd;

  i = -1;
  if ((cmd = my_strdup("echo ; echo")) == NULL)
    exit(84);
  while (tab[++i])
    {
      if ((cmd = my_strcatdup(cmd, " ", 1)) == NULL)
	exit(84);
      if ((cmd = my_strcatdup(cmd, tab[i], 1)) == NULL)
	exit(84);
    }
  if ((cmd = my_strcatdup(cmd, " | sort | column -t", 1)) == NULL)
    exit(84);
  my_system(cmd, key->sys);
}

static int		get_matching_files(char *folder, char *pattern,
					 int *size, char ***tab)
{
  DIR		*dir;
  struct dirent	*dirent;

  if ((dir = opendir(folder)) == NULL)
    return (1);
  while ((dirent = readdir(dir)) != NULL)
    if (advanced_match(dirent->d_name, pattern))
      {	
	if ((*tab = realloc(*tab, (sizeof(char *) * (*size + 2)))) == NULL)
	  exit(84);
	(*tab)[*size] = my_strdup(dirent->d_name);
	(*tab)[*size + 1] = NULL;
	*size += 1;
      }
  closedir(dir);
  return (0);
}

int		auto_complete(t_keypad *key)
{
  int		i;
  char		*seq;
  char		**files;

  i = 0;
  files = NULL;
  get_matching_files(".", "<.>*", &i, &files);
  exec_complete(files, key);
  free_tab(files);
  if (isatty(0))
    print_prompt(key->sys->info);
  if (key->line)
    {
      if ((seq = tigetstr("cub1")) == (char *) -1)
	return (0);
      my_printf(key->line);
      i = my_strlen(key->line) + 1;
      while (--i > key->index)
	my_printf(seq);
    }
  return (0);
}
