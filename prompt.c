/*
** main.c for main.c in /home/cedric/delivery/ex
**
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
**
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
** Last update Tue May 16 16:46:31 2017 maje
*/

#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "my.h"
#include "get_next_line.h"
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

static char  *extractor(char *str)
{
  if (my_strncmp(str, "ref", 3) == 0)
    printf("\033[31;01mmaster\033[00m");
  my_printf("\033[34;01m)\033[00m", str);
}

static char     *read_for_prompt(char *str)
{
  int   fd;
  char  *buf;
  struct stat st;

  if (stat(str, &st) == -1)
    return (NULL);
  if ((fd = open(str, O_RDONLY)) == -1)
    return (NULL);
  if ((buf = malloc(sizeof(char) * st.st_size)) == NULL)
    exit(84);
  if (read(fd, buf, st.st_size) == -1)
    exit(84);
  buf[st.st_size] = '\0';
  close(fd);
  return (buf);
}

static void     git(char *info)
{
  DIR           *dir;
  char          *buf;
  char		*str;
  int           i;
  struct dirent *dirent;

  if ((dir = opendir(info)) == NULL)
    return ;
  i = 0;
  while ((dirent = readdir(dir)) != NULL)
    {
      if (my_strcmp(".git", dirent->d_name) == 0)
	{
	  my_printf("\033[34;01m git:(\033[00m", str);
	  str = strdup(info);
	  str = my_strcatdup(str, "/.git/HEAD", 1);
	  str = read_for_prompt(str);
	  extractor(str);
	  i++;
	}
    }
  if (i == 0)
    {
      buf = my_strdup(info);
      git(my_strcatdup(buf, "/..", 1));
    }
  closedir(dir);
}

static void	extract(t_info *info)
{
  char		*home;
  int		i;

  i = my_strlen(info->pwd);
  home = getkey(info->env, "HOME", 0);
  if (home && !my_strcmp(info->pwd, home))
    my_printf("\033[36;01m~\033[00m");
  else
    {
      while (i > 0 && info->pwd[i] != '/')
	i -= 1;
      if (i != 0)
	i += 1;
      my_printf("\033[36;01m%s\033[00m", info->pwd + i);
    }
}

void	print_prompt(t_info *info)
{
  if ((info->exit_value) != 0)
    my_printf("\033[31;01m➜ %u \033[00m", info->exit_value);
  else
    my_printf("\033[32;01m➜ %u \033[00m", info->exit_value);
  extract(info);
  git(info->pwd);
  my_printf(" ");
}
