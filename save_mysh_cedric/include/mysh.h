/*
** mysh.h for mysh.h in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Wed Jan  4 12:56:25 2017 Cédric Thomas
** Last update Thu Apr  6 16:46:18 2017 
*/
#ifndef MYSH_H_
# define MYSH_H_

# include "syntax.h"

# define NODE_TYPES	4
# define REDIR_TYPES	4
# define BUILTINS_NB	5

# define ON_FORK	(1 << 0)
# define ON_PIPELINE	(1 << 1)

typedef struct stat		t_stat;
typedef	struct s_builtin	t_builtin;

typedef struct		s_fd
{
  int			in;
  int			out;
  struct s_fd		*prev;
  struct s_fd		*next;
}			t_fd;

typedef struct		s_exit
{
  int		        exit;
  int			pid;
  struct s_exit		*next;
}			t_exit;

/*
**structure contenant une commande simple
*/

typedef struct		s_toexec
{
  char			**argv;
  int			argc;
  char			**env;
}			t_toexec;

/*
**structure de status de l'execution en cours
** et passage de paramètre dynamique
*/

typedef struct		s_status
{
  t_fd			forced;
  t_fd		        *fd;
  int			*piped;
  int			pipe_max;
  int			cmd;
  int			status;
  int			exit;
  t_exit		*pipeline;
}			t_status;

/*
**structure d'info du systeme et du shell
*/
typedef struct		s_info
{
  t_builtin		*builtins;
  char			**env;
  unsigned int		last;
  char			*old_pwd;
  char			*pwd;
  t_syntax		*syntax;
}			t_info;

typedef struct		s_builtin
{
  char			*builtins;
  int			(*fct)(t_info *info, t_toexec *exec, t_status *status);
}			t_builtin;

typedef struct		s_parse_fct
{
  char			*tag;
  int			type;
  t_fd			(*fct)(t_node *root, t_status *status, t_info *info);
}			t_parse_fct;

/*
** main.c
*/
void		free_info(t_info *info);
void		reset_status(t_status *status);

/*
** prompt/prompt.c
*/
void		print_prompt(t_info *info);

/*
** str.c
*/
char		*strappend(char *s1, char *s2, int freeit);
int		my_nullstrlen(char *str);
char		**tabdup(char **tab);
char		*replaceinstr(char *tochange, char *tofind, char *toreplace);
int		my_strtocharlen(char *str, char c);

/*
** env/env.c
*/
char		*getkey(char **ae, char *str, int dup);
int		changekey(char **ae, char *str, char *value, int freeit);
char		**deletekey(char **ae, char *key, int freeit);
char		**addkey(char **ae, char *key, char *value, int freeit);

/*
** env/key.c
*/
char		*getcleanpwd();
char		*getcleanhostname();

/*
** misc.c
*/
t_fd		myfds(int in, int out);
void		*multi_free(int size, ...);
int		multi_close(int size, ...);
t_toexec	mytoexec(char **argv, char **env);

/*
**interpretor/misc.c
*/
char	**args_node_to_argv(t_node *root);
void	close_errors(t_fd *forced);

/*
**interpretor/
*/
t_fd	search_actions(t_node *root, t_status *status, t_info *info);
t_fd	my_cmd(t_node *root, t_status *status, t_info *info);
t_fd	my_separ(t_node *root, t_status *status, t_info *info);
t_fd	my_pipe(t_node *root, t_status *status, t_info *info);
t_fd	my_redir(t_node *root, t_status *status, t_info *info);

/*
**interpretor/redir
*/
t_fd	double_output(t_node *root, t_status *status, t_info *info);
t_fd	output(t_node *root, t_status *status, t_info *info);
t_fd	input(t_node *root, t_status *status, t_info *info);
t_fd	double_input(t_node *root, t_status *status, t_info *info);
int	search_double_input(t_node *root, t_status *status, t_info *info);

/*
** exec/exec.c
*/
int		try_builtins(t_info *info, t_toexec *exec, t_status *status);
int		exec_full(t_info *info, t_toexec *exec, t_status *status);
t_builtin	*get_builtins();

/*
** exec/builtins/
*/
int		exitsh(t_info *info, t_toexec *exec, t_status *status);
int		cd(t_info *info, t_toexec *exec, t_status *status);
int		setenvsh(t_info *info, t_toexec *exec, t_status *status);
int		unsetenvsh(t_info *info, t_toexec *exec, t_status *status);
int		envsh(t_info *info, t_toexec *exec, t_status *status);

/*
** exec/execve/my_fork.c
*/
int		my_fork(t_toexec *exec, char *name, t_info *info, t_status *status);
void		check_sig(int status);
void		son(char **argv, char *name, t_info *info);
void		father(t_info *info);

/*
** exec/execve/pathfinder.c
*/
void		replacepath(t_info *info, t_toexec *exec, char **pathabs);
int		my_exec(t_info *info, t_toexec *exec, t_status *status);

/*
**status/list_fds.c
*/
int		my_put_list_fd(t_fd **ll, int in, int out);
int		my_del_list_fd(t_fd **ll, t_fd *elem);
int		my_close_fd(t_fd **ll, int **pipes, int *size);

/*
**status/list_status.c
*/
int	my_put_list_exit(t_exit **ll, int pid, int last);
int	my_del_exit(t_exit **ll);
void	setlast(t_exit *ll, int pid, int exit);
void	show_exit_status(t_exit *ll);

#endif /* !MYSH_H_ */
