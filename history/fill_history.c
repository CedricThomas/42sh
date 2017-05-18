/*
** fill_history.c for 42sh in /home/maje/Dropbox/delivery/B2/PSU/PSU_2016_42sh
** 
** Made by maje
** Login   <marin.brunel@epitech.eu>
** 
** Started on  Thu May 18 09:56:38 2017 maje
** Last update Thu May 18 10:01:48 2017 maje
*/

#include "my.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "get_next_line.h"
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"

int	fill_hystory()
