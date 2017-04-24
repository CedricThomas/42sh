/*
** cd.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell1
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Fri Jan  6 09:13:49 2017 Thibaut Cornolti
** Last update Thu Mar 23 14:03:28 2017 Thibaut Cornolti
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "my.h"
#include "sh.h"

char		*calc_path(char *cmd)
{
  int		i;
  char		*result;
  int		j;

  i = -1;
  if (cmd == NULL ||
      (result = malloc(sizeof(char) * PATH_MAX)) == NULL)
    return (NULL);
  result[0] = 0;
  i = -1;
  j = -1;
  while (cmd[++i])
    {
      result[++j] = cmd[i];
      result[j + 1] = 0;
    }
  result[++j] = 0;
  free(cmd);
  return (result);
}

static int	check_error(char **av, char *s)
{
  struct stat	st;

  stat(s, &st);
  my_puterror(s);
  if (my_arglen(av) == 1)
    my_msg("cd", NULL, -4);
  else if (!S_ISDIR(st.st_mode))
    my_msg("", NULL, -2);
  else if (access(s, F_OK) == -1)
    my_msg("", NULL, -3);
  else if (access(s, R_OK) == -1)
    my_msg("", NULL, -1);
  else
    my_msg("", NULL, -3);
  return (1);
}

static void	init_fct_cd(t_cd_d *cd, char **av, char ***ae)
{
  if ((cd->path = malloc(sizeof(char) * PATH_MAX)) == NULL)
    return ;
  my_strcpy(cd->path, ".");
  if (av[1] && !my_strcmp(av[1], "--"))
    av[2] = calc_path(av[2]);
  else
    av[1] = calc_path(av[1]);
  cd->home = my_getenv(*ae, "HOME");
  cd->pwd = my_getenv(*ae, "PWD");
  cd->oldpwd = my_getenv(*ae, "OLDPWD");
}

static char	*fct_cd_2(char **av, t_cd_d *cd)
{
  int		len;

  len = my_arglen(av);
  if ((len == 1 || (my_arglen(av) == 2 && !my_strcmp(av[1], "--"))) &&
      !chdir((*cd).home))
    return (getcwd((*cd).path, PATH_MAX));
  else if (len == 3 && !my_strcmp(av[1], "--") &&
	   !chdir(av[2]))
    return (getcwd((*cd).path, PATH_MAX));
  else if (len == 3 &&
	   !my_strcmp(av[1], "--") && !chdir(cat_path((*cd).pwd, av[2])))
    return (getcwd((*cd).path, PATH_MAX));
  else if (len == 2 && !my_strcmp("-", av[1]) && (*cd).oldpwd &&
	   !chdir((*cd).oldpwd))
    return (getcwd((*cd).path, PATH_MAX));
  else if (len == 2 && !chdir(av[1]))
    return (getcwd((*cd).path, PATH_MAX));
  else if (len == 2 && av[1][0] != '/' &&
	   !chdir(cat_path((*cd).pwd, av[1])))
    return (getcwd((*cd).path, PATH_MAX));
  else
    return (NULL);
}

void		fct_cd(char **av, char ***ae)
{
  t_cd_d	cd;

  init_fct_cd(&cd, av, ae);
  if (my_arglen(av) == 1 && cd.home == NULL)
    my_puterror("cd: No home directory.\n");
  else if (fct_cd_2(av, &cd));
  else if (check_error(av, ((av[1] && !my_strcmp(av[1], "--") ?
			     av[2] : av[1]))))
    {
      assist_add_env("LAST_RETURN", "1", ae);
      return ;
    }
  assist_add_env("LAST_RETURN", "0", ae);
  assist_add_env("OLDPWD", cd.pwd, ae);
  assist_add_env("PWD", cd.path, ae);
  free(cd.path);
}
