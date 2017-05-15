/*
** cd.c for builtin in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur 42/exec/builtin
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu May 11 13:22:48 2017 Thibaut Cornolti
** Last update Fri May 12 17:41:22 2017 
*/

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static int	error_msg(int code, char *prefix, t_info *info)
{
  static char	*msg[3];

  msg[0] = ": No home directory.\n";
  msg[1] = ": No such file or directory.\n";
  msg[2] = ": Too many arguments.\n";
  info->exit_value = 1;
  if (prefix)
    my_puterror(prefix);
  my_puterror(msg[code]);
  return (0);
}

static int	builtin_cd_dash(t_info *info, char *path)
{
  char		*pwd;

  free(path);
  if (chdir(info->old_pwd) == -1)
    return (error_msg(1, info->old_pwd, info));
  pwd = info->pwd;
  info->pwd = info->old_pwd;
  info->old_pwd = pwd;
  if (changekey(info->env, "OLDPWD", info->old_pwd, 0))
    info->env = addkey(info->env, "OLDPWD", info->old_pwd, 0);
  if (changekey(info->env, "PWD", info->pwd, 0))
    info->env = addkey(info->env, "PWD", info->pwd, 0);
  return (0);
}

static int	builtin_cd_param(t_info *info, char *path)
{
  if (!my_strcmp(path, "-"))
    return (builtin_cd_dash(info, path));
  if (chdir(path) == -1)
    return (error_msg(1, path, info));
  free(path);
  if ((path = getcwd(NULL, PATH_MAX)) == NULL)
    exit(84);
  free(info->old_pwd);
  info->old_pwd = info->pwd;
  info->pwd = path;
  if (changekey(info->env, "OLDPWD", info->old_pwd, 0))
    info->env = addkey(info->env, "OLDPWD", info->old_pwd, 0);
  if (changekey(info->env, "PWD", info->pwd, 0))
    info->env = addkey(info->env, "PWD", info->pwd, 0);
  return (0);
}

static int	builtin_cd_no_param(t_info *info)
{
  char		*home;

  if ((home = getkey(info->env, "HOME", 1)) == NULL)
    return (error_msg(0, "cd", info));
  if (chdir(home) == -1)
    return (error_msg(1, home, info));
  free(info->old_pwd);
  info->old_pwd = info->pwd;
  info->pwd = home;
  if (changekey(info->env, "OLDPWD", info->old_pwd, 0))
    info->env = addkey(info->env, "OLDPWD", info->old_pwd, 0);
  if (changekey(info->env, "PWD", info->pwd, 0))
    info->env = addkey(info->env, "PWD", info->pwd, 0);
  return (0);
}

void		builtin_cd(t_command *cmd, t_status *status, t_info *info)
{
  info->exit_value = 0;
  if (cmd->argv[1] && cmd->argv[2])
    error_msg(2, "cd", info);
  else if (!cmd->argv[1])
    builtin_cd_no_param(info);
  else if (!cmd->argv[2])
    builtin_cd_param(info, my_strdup(cmd->argv[1]));
  else
    error_msg(2, "cd", info);
  UNUSED(status);
}
