/*
** set.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Wed May 17 16:07:30 2017 Bastien
** Last update Wed May 17 21:36:14 2017 Bastien
*/

static int	verify_set(char *str, t_var *var)
{
  int	i;
  int	len;

  i = -1;
  len = my_cstrlen(str, '=');
  while (var && var[++i].name)
    if (!strcmp(var[i].name, str))
      {
	
      }
    
}

void		builtin_set(t_command *cmd, t_status *status, t_info *info)
{
  int		i;
  static int	size = 0;

  i = 0;
  while (cmd->argv[++i])
    if (verify_set(cmd->argv[i], info->var))
      return ;
  
}
