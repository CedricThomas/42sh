/*
** exec.h for 42sh in /home/cedric/Desktop/parseur 42
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue May  9 09:25:48 2017 
** Last update Tue May  9 15:40:55 2017 
*/
#ifndef EXEC_H_
# define EXEC_H_

# define BUILTINS_NB	5
# define REDIR_NB	4

typedef struct		s_status
{
  unsigned int		last;
  int			exit;
}			t_status;

typedef struct		s_info
{
  char			*builtins[BUILTINS_NB];
  char			**env;
  unsigned int		last;
  char			*old_pwd;
  char			*pwd;
}			t_info;

typedef struct		s_exec_fct
{
  int                   type;
  int                  (*fct)(void *root, t_status *status, t_info *info);
}			t_exec_fct;

/*
**MISC
*/
char		**tab_dup(char **tab);

/*
**SETUP
*/
t_info		*get_info(char **env);
void		*free_info(t_info *info);

/*
**ENV
*/

/*
**keys
*/
char		*getkey_hostname();
char		*getkey_pwd();

/*
**env
*/
int	changekey(char **ae, char *key, char *value, int freeit);
char	**addkey(char **ae, char *key, char *value, int freeit);
char	**deletekey(char **ae, char *key, int freeit);
char	*getkey(char **ae, char *key, int dup);

/*
**EXEC SELECTOR
*/

int	auto_select(t_node *root, t_status *status, t_info *info);

int	exec_cmd(t_node *root, t_status *status, t_info *info);

/*
**REDIR
*/
int	redir_output(char *file);
int	double_redir_output(char *file);
int	redir_input(char *file);
int	double_redir_input(char *file);

#endif /* !EXEC_H_ */
