/*
** msg.c for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell1
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Wed Jan 11 23:31:54 2017 Thibaut Cornolti
** Last update Thu Mar 23 14:04:59 2017 Thibaut Cornolti
*/

#include <unistd.h>
#include "my.h"
#include "sh.h"

static void	init_msg(char *msg[10], int code[10])
{
  int		i;

  i = -1;
  msg[++i] = "Command not found.\n";
  code[i] = 127;
  msg[++i] = "Floating exception (core dumped)\n";
  code[i] = 136;
  msg[++i] = "Segmentation fault (core dumped)\n";
  code[i] = 139;
  msg[++i] = "Floating exception\n";
  code[i] = 8;
  msg[++i] = "Segmentation fault\n";
  code[i] = 11;
  msg[++i] = "Permission denied.\n";
  code[i] = -1;
  msg[++i] = "Not a directory.\n";
  code[i] = -2;
  msg[++i] = "No such file or directory.\n";
  code[i] = -3;
  msg[++i] = "Can't change to home directory.\n";
  code[i] = -4;
  msg[++i] = "Exec format error. Binary file not executable.\n";
  code[i] = -5;
}

int		my_msg(char *e, char **ae, int error)
{
  static char	*msg[10];
  static int	code[10];
  static int	already = 0;
  int		i;

  if (ae != NULL)
    error = my_getnbr(my_getenv(ae, "LAST_RETURN"));
  if (!already)
    {
      init_msg(msg, code);
      already = 1;
    }
  if (e != NULL)
    {
      my_puterror(e);
      my_puterror(": ");
    }
  i = -1;
  while (++i < 10)
    if (code[i] == error)
      {
	my_puterror(msg[i]);
        return (error);
      }
  return (error);
}
