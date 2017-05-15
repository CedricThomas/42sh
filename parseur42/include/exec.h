/*
** exec.h for 42sh in /home/cedric/Desktop/parseur 42
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue May  9 09:25:48 2017 
** Last update Mon May 15 13:24:51 2017 Bastien
*/

#ifndef EXEC_H_
# define EXEC_H_

# define _GNU_SOURCE

# define PIPELINE	(1 << 0)
# define LEFT_PIPE	(1 << 1)
# define RIGHT_PIPE	(1 << 2)

# define BUILTINS_NB	5
# define REDIR_NB	4

typedef struct		s_alias
{
  char			*link;
  char			*real_cmd;
}			t_alias

typedef struct		s_info
{
  char			*builtins[BUILTINS_NB + 1];
  char			**env;
  unsigned int		exit_value;
  char			*old_pwd;
  char			*pwd;
  t_alias		*alias;
}			t_info;

typedef struct          s_exit
{
  int                   exit;
  int                   pid;
  struct s_exit         *next;
}                       t_exit;

typedef struct		s_status
{
  int			exit;
  int			status;
  struct s_exit		*exit_list;
}			t_status;

typedef struct		s_exec_fct
{
  int                   type;
  int                  (*fct)(t_node *root, t_status *status, t_info *info);
}			t_exec_fct;

/*
**PROMPT
*/
void    print_prompt(t_info *info);

/*
**MISC
*/
int	exist_in_tab(char *str, char **tab);
char	**tab_dup(char **tab);
int	my_perror(char *cmd, char *error);

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
**SELECTOR
*/

int	auto_select(t_node *root, t_status *status, t_info *info);

int	exec_cmd(t_node *root, t_status *status, t_info *info);
int	exec_separ(t_node *root, t_status *status, t_info *info);
int	exec_logic(t_node *root, t_status *status, t_info *info);
int	exec_pipe(t_node *root, t_status *status, t_info *info);

/*
**SELECTOR/CMD
*/
int	load_redir(t_command *cmd);

int	redir_output(char *file);
int	double_redir_output(char *file);
int	redir_input(char *file);
int	double_redir_input(char *file);

void	my_undup(t_command *cmd, int save[3]);
void	my_dup(t_command *cmd, int save[3]);

/*
**EXECVE
*/
char	*my_pathfinder(t_command *cmd, t_info *info);
void	simple_exec(t_command *cmd, t_status *status, t_info *info);

/*
**STATUS
*/

void	auto_wait(t_status *status, t_info *info);
int	my_fork(t_command *cmd, t_status *status, t_info *info,
		void (*fct)(t_command *cmd, t_status *status, t_info *info));

int	my_put_list_exit(t_exit **ll, int pid, int last);
void	set_exit_value(t_exit *ll, int pid, int exitval);
void	show_exit_status(t_exit *ll);
int	my_del_exit(t_exit **ll);

/*
**list
*/
int	my_put_list_exit(t_exit **ll, int pid, int last);
void	set_exit_value(t_exit *ll, int pid, int exitval);
void	show_exit_status(t_exit *ll);
int	my_del_exit(t_exit **ll);

/*
**BUILTINS
*/
void	builtin_echo(t_command *cmd, t_status *status, t_info *info);
void	builtin_cd(t_command *cmd, t_status *status, t_info *info);
void	builtin_setenv(t_command *cmd, t_status *status, t_info *info);
void	builtin_unsetenv(t_command *cmd, t_status *status, t_info *info);
void	builtin_exit(t_command *cmd, t_status *status, t_info *info);

#endif /* !EXEC_H_ */
