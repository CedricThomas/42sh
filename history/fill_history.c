/*
** fill_history.c for 42sh in /home/maje/Dropbox/delivery/B2/PSU/PSU_2016_42sh
** 
** Made by maje
** Login   <marin.brunel@epitech.eu>
** 
** Started on  Thu May 18 09:56:38 2017 maje
** Last update Thu May 18 18:07:45 2017 Cédric THOMAS
*/
#include <stdio.h>

stream = fopen("/etc/motd", "r");
if (stream == NULL)
  exit(EXIT_FAILURE);

while ((read = getline(&line, &len, stream)) != -1) {
  printf("Retrieved line of length %zu :\n", read);
  printf("%s", line);
 }

free(line);
fclose(stream);
exit(EXIT_SUCCESS);


static char		get_path_history()
{


}

int			write_history(t_info *info)
{
  char		*path;
  int		fd;
  t_history	*tmp;

  tmp = info->histo->start;
  if ((path = get_path()) == NULL)
    return (1);
  if ((fd = open()))
    return (1);
  while (tmp)
    {
      
      
      
      
      
      
      
    }
  return (0);
}

int	load_history(t_info *info)
{
  char		*line = NULL;
  size_t	len = 0;
  ssize_t	read;
}
