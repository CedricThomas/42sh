/*
** misc.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Wed Jan  4 12:55:32 2017 Cédric Thomas
** Last update Mon Apr  3 22:44:08 2017 
*/
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "my_printf.h"
#include "mysh.h"

char	*getpromptpwd(char **ae, char *prompt)
{
  char	*home;
  char	*folder;
  char	*pwd;
  int	i;

  pwd = getkey(ae, "PWD", 0);
  i = my_nullstrlen(pwd);
  while (i > 0 && pwd[i] != '/')
    i -= 1;
  folder = pwd + i + (i ? 1 : 0);
  home = getkey(ae, "HOME", 0);
  while (my_strstr(prompt, "\\W") && folder)
    prompt = replaceinstr(prompt, "\\W", folder);
  while (my_strstr(prompt, "\\w") && pwd)
    prompt = replaceinstr(prompt, "\\w", pwd);
  while (my_strstr(prompt, "\\e"))
    prompt = replaceinstr(prompt, "\\e", "\e");
  while (home && my_strlen(home) && my_strstr(prompt, home))
    prompt = replaceinstr(prompt, home, "~");
  return (prompt);
}

char	*getpromptsys(char **ae, char *prompt)
{
  while (my_strstr(prompt, "\\u") && getkey(ae, "USER", 0))
    prompt = replaceinstr(prompt, "\\u", getkey(ae, "USER", 0));
  while (my_strstr(prompt, "\\h") && getkey(ae, "HOST", 0))
    prompt = replaceinstr(prompt, "\\h", getkey(ae, "HOST", 0));
  return (prompt);
}

char	*getdefault(char **ae)
{
  int	i;
  int	count;
  char	*pwd;

  pwd = getkey(ae, "PWD", 0);
  count = 0;
  i = my_nullstrlen(pwd);
  while (i > 0 && count < 2)
    {
      if (pwd[i] == '/')
	count += 1;
      i -= 1;
    }
  if (i != 0)
    i += 1;
  else
    i -= 1;
  pwd = strappend(pwd + i + 1, ">", 0);
  return (pwd);
}

void	print_prompt(t_info *info)
{
  char	*prompt;

  if (!isatty(0))
    return ;
  prompt = getkey(info->env, "MYSH", 1);
  if (prompt == NULL)
    prompt = getkey(info->env, "PS1", 1);
  if (prompt == NULL)
    prompt = getdefault(info->env);
  else
    {
      prompt = getpromptpwd(info->env, prompt);
      prompt = getpromptsys(info->env, prompt);
    }
  prompt = strappend("\e[0;31mmysh\e[0m ", prompt, 2);
  my_printf("{%u} ", info->last);
  my_putstr(prompt);
  free(prompt);
}
