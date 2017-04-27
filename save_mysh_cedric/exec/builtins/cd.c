/*
** cd.c for cd in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sun Jan  8 18:51:02 2017 
** Last update Sat Apr  1 15:10:32 2017 
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

static void	print_cderror(char *path)
{
  t_stat	my_stat;

  my_puterror(path);
  if (stat(path, &my_stat) < 0)
    return (my_puterror(": No such file or directory.\n"));
  if (!S_ISDIR(my_stat.st_mode))
    return (my_puterror(": Not a directory.\n"));
  if (access(path, R_OK))
    return (my_puterror(": Permission denied.\n"));
}

static void	changepwd(t_info *info)
{
  char	*pwd;

  free(info->old_pwd);
  info->old_pwd = info->pwd;
  pwd = getcleanpwd();
  if (getkey(info->env, "PWD", 0) == NULL)
    info->env = addkey(info->env, "PWD", pwd, 0);
  else
    changekey(info->env, "PWD", pwd, 0);
  info->pwd = pwd;
}

static void	noparams(t_info *info, t_toexec *exec)
{
  char		*home;

  if ((home = getkey(info->env, "HOME", 0)) == NULL)
    {
      my_puterror("cd: No home directory.\n");
      return ;
    }
  if (chdir(home) < 0)
    {
      my_puterror("cd: Can't change to home directory.\n");
      return ;
    }
  changepwd(info);
  info->last = 0;
}

static void	oneparams(t_info *info, t_toexec *exec)
{
  char		*home;
  char		*path;

  if (!my_strcmp(exec->argv[1], "-"))
    path = my_strdup(info->old_pwd);
  else
    path = my_strdup(exec->argv[1]);
  home = getkey(info->env, "HOME", 0);
  path = replaceinstr(path, "~", home);
  if (!my_strcmp(path, "~") && !home)
    {
      my_puterror("No $home variable set.\n");
      return (free(path));
    }
  if (chdir(path) < 0)
    {
      print_cderror(path);
      return (free(path));
    }
  free(path);
  changepwd(info);
  info->last = 0;
}

int	cd(t_info *info, t_toexec *exec, t_status *status)
{
  char	*pwd;

  info->last = 1;
  if (exec->argc == 1)
    noparams(info, exec);
  else if (exec->argc == 2)
    oneparams(info, exec);
  else
    my_puterror("cd: Too many arguments.\n");
  return (0);
}

