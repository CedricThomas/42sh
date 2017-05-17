/*
** exec.h for 42sh in /home/cedric/Desktop/parseur 42
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue May  9 09:25:48 2017 
** Last update Wed May 17 12:50:45 2017 Thibaut Cornolti
*/

#ifndef EXEC_H_
# define EXEC_H_

# define PIPELINE	(1 << 0)
# define LEFT_PIPE	(1 << 1)
# define RIGHT_PIPE	(1 << 2)
# define FORK		(1 << 3)
# define JOB		(1 << 4)
# define JOBLINE	(1 << 5)

# define JOB_SUSPENDED	(1 << 0)
# define JOB_FOREGROUND	(1 << 1)
# define JOB_BACKGROUND	(1 << 2)

# define BUILTINS_NB	9
# define REDIR_NB	4

# define FILE_RC	".42shrc"

typedef struct		s_alias
{
  char			*link;
  char			*value;
  int			loop;
}			t_alias;

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

typedef struct		s_job
{
  int			pid;
  int			status;
  int			number;
  int			step;
  struct s_job		*next;
  struct s_job		*prev;
}			t_job;

typedef struct		s_status
{
  int			exit;
  int			status;
  int			fd_to_close;
  struct s_exit		*exit_list;
  struct s_job		*job_list;
  int			job_nbr;
}			t_status;

typedef struct		s_exec_fct
{
  int                   type;
  int                  (*fct)(t_node *root, t_status *status, t_info *info);
}			t_exec_fct;

typedef struct		s_system
{
  struct s_keypad	*keypad;
  t_syntax		*syntax;
  t_status		*status;
  t_info		*info;
}			t_system;

int	my_system(char *command, t_system *system);

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
t_token		*get_alias(t_token *token, t_info *info, t_syntax *syntax);

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
int	exec_job(t_node *root, t_status *status, t_info *info);

/*
**SELECTOR/CMD
*/
int	load_redir(t_command *cmd, t_status *status);

int	redir_output(char *file);
int	double_redir_output(char *file);
int	redir_input(char *file);
int	double_redir_input(char *file);

void	my_undup(t_command *cmd, int save[3]);
void	my_dup(t_command *cmd, int *save);

/*
**EXECVE
*/
char	*my_pathfinder(t_command *cmd, t_info *info);
void	simple_exec(t_command *cmd, t_status *status, t_info *info);

/*
**STATUS
*/

void	auto_wait(t_status *status, t_info *info);
void	auto_wait_job(t_status *status);
void	print_wait_job(t_status *status);
int	my_fork(t_command *cmd, t_status *status, t_info *info,
		void (*fct)(t_command *cmd, t_status *status, t_info *info));
int	my_fork_job(void *root, t_status *status, t_info *info,
		int (*fct)(t_node *root, t_status *status, t_info *info));

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
void	builtin_alias(t_command *cmd, t_status *status, t_info *info);
void	builtin_fg(t_command *cmd, t_status *status, t_info *info);
void	builtin_bg(t_command *cmd, t_status *status, t_info *info);
void	builtin_jobs(t_command *cmd, t_status *status, t_info *info);
void	check_loop(t_info *info);

/*
**LOAD
*/

void	load_rc(t_status *status, t_info *info, t_syntax *syntax);

/*
**JOB
*/

t_job	*my_put_list_job(t_status *status, int pid, int stats);
void	set_job_value(t_job *ll, int pid, int status);
void	show_job_status(t_job *ll);
int	my_del_job(t_job **ll);
int	get_free_job(t_job *ll);
void	plane_job(t_job *ll);
t_job	*get_job(t_job *ll, int pid);

#endif /* !EXEC_H_ */
