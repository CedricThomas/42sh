/*
** auto_complete.c for 42sh in /home/cedric/Desktop/get_next_cmd
**
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Tue May 16 14:34:55 2017 Cédric THOMAS
** Last update Wed May 17 21:42:12 2017 Cédric THOMAS
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
  if ((cmd = my_strdup("echo")) == NULL)
    exit(84);
  while (tab && tab[++i])
    {
      if ((cmd = my_strcatdup(cmd, " ", 1)) == NULL)
	exit(84);
      if ((cmd = my_strcatdup(cmd, tab[i], 1)) == NULL)
	exit(84);
      if ((cmd = my_strcatdup(cmd, "\n", 1)) == NULL)
	exit(84);
    }
  if ((cmd = my_strcatdup(cmd, " | column", 1)) == NULL)
    exit(84);
  my_system(cmd, key->sys);
}

static int		add_matching_files(char *folder, char *pattern,
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
	if (((*tab)[*size] = my_strdup(dirent->d_name)) == NULL)
	  exit(84);
	(*tab)[*size + 1] = NULL;
	*size += 1;
      }
  closedir(dir);
  return (0);
}

static void	get_folder_and_path(char *full_path,
				    char **path, char **file)
{
  int		i;

  i = my_strlen(full_path);
  while (full_path[i] != '/' && i > 0)
    i -= 1;
  if (full_path[i] == '/')
    i += 1;
  if (i == 0)
    *path = my_strdup(".");
  else
    *path = my_strndup(full_path, i);
  if (full_path[i] == 0)
    *file = my_strdup("<.>");
  else
    *file = my_strdup(full_path + i);
}

static void	search_cmd(t_keypad *key, char ***files, int *size, char *cmd)
{
  char		**path;

}

static void	search_folder(t_keypad *key, char ***files, int *size)
{
  t_token	*temp;
  t_token	*token;
  char		*file;
  char		*path;

  token = get_token(my_strndup(key->line, key->index), key->sys->syntax);
  temp = token;
  while (temp && temp->next)
    temp = temp->next;
  if (temp == NULL ||
      (key->index > 0 && is_in(key->line[key->index - 1], SKIP)))
    get_folder_and_path("", &path, &file);
  else
    {
      if (!is_in('/', temp->token))
	search_cmd(key, files, size, temp->token);
      get_folder_and_path(temp->token, &path, &file);
    }
  add_matching_files(path, my_strcatdup(file, "*", 1), size, files);
  my_free_token(&token);
}

//
//rien/espace avant/arg  = dossier courant avec match
//cmd en cours -> path + dossier courant + builtin + alias
//

int		auto_complete(t_keypad *key)
{
  int		size;
  char		**files;

  my_printf("\n");
  if (key->line == NULL)
    key->line = my_strdup("");
  size = 0;
  files = NULL;
  search_folder(key, &files, &size);
  search_path(key, &files, &size);
  exec_complete(files, key);
  free_tab(files);
  return (0);
}
