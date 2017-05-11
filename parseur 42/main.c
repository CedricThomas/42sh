/*
** main.c for main.c in /home/cedric/delivery/ex
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
** Last update Thu May 11 18:10:01 2017 maje
*/
#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "get_next_line.h"
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"

static void	extract(t_info *info)
{
  int	i;
  int	j;
  int	count;

  i = -1;
  count = 0;
  while (info->pwd[++i] != '\0')
    if (info->pwd[i] == '/')
      count++;
  i = 0;
  j = 0;
  while (info->pwd[i] != '\0')
    {
      if (info->pwd[i] == '/')
	j++;
      if (j == count)
	if (info->pwd[i] != '/')
	  my_printf("\033[36;01m%c\033[00m", info->pwd[i]);
      i++;
    }
}

static void     print_prompt(t_info *info)
{
  int   i;
  char  *buf;


  if ((info->exit_value) != 0)
    {
      my_printf("\033[31;01m➜  \033[00m");
      extract(info);
      my_printf(" \033[31;01m \033[00m");
    }
  else
    {
      my_printf("\033[32;01m➜  \033[00m");
      extract(info);
      my_printf(" \033[31;01m \033[00m");
    }
}

int		main(int ac, char **av, char **env)
{
  void		*root;
  t_syntax	*syntax;
  t_status	status;
  t_info	*info;
  char		*str;

  syntax = get_syntax();
  info = get_info(env);
  my_memset(&status, 0, sizeof(status));
  if (isatty(0))
    print_prompt(info);
  while ((str = get_next_line(0)))
    {
      if ((root = parse_cmd(syntax, str)))
	{
	  //	  show_nodes(root, 0, 0);
	  auto_select(root, &status, info);
	  my_free_tree(&root);
	}
      if (isatty(0))
	print_prompt(info);
    }
  free_syntax(&syntax);
  free_info(info);
  UNUSED(av);
  UNUSED(ac);
  return (0);
}
