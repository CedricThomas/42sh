/*
** fct.h for my_ls in /home/thibrex/delivery/PSU/PSU_2016_my_ls
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Tue Nov 22 10:10:36 2016 Thibaut Cornolti
** Last update Sat Apr  8 16:07:27 2017 Thibaut Cornolti
*/

#ifndef SH_H_
# define SH_H_

#include <dirent.h>

typedef struct dirent	dir;

typedef struct	s_ll
{
  struct s_ll	*prev;
  struct s_ll	*next;
  char		token;
  char		*cmd;
  int		pipefd[2];
  int		std_tmp[2];
  int		fork_pid;
}		t_ll;

typedef struct	s_cd_data
{
  char		*path;
  char		*home;
  char		*pwd;
  char		*oldpwd;
}		t_cd_d;

typedef struct	s_search_path_data
{
  char		*rs;
  char		**path;
  int		i;
  DIR		*dir;
  dir		*dirent;
}		t_sp_d;

char	*my_sh(char ***);
char	*my_getenv(char **, char *);
char	*my_epure_str(char *);
int	my_igetenv(char **, char *);
void	assist_add_env(char *, char *, char ***);
void	set_lr(int, char ***);
char	**get_argv(char *, char);
int	free_argv(char ***);
char	*getenv_var(char *);
char	*getenv_pa(char *);
void	commander(t_ll *, char ***);
void	commander_error(int, char ***);
void	builtin(char *, char ***);
char	*cat_path(char *, char *);
char	*cat_path_wm(char *, char *, int *);
int	my_msg(char *, char **, int);
int	my_arglen(char **);
void	sig(int);
void	prompt();
int	check_slash(char *);
int	check_alphanum(char *);
char	*search_local_path(char ***, char *);
char	*search_path(char ***, char *);
void	fct_exit(char **, char ***);
void	fct_cd(char **, char ***);
void	fct_env(char **, char ***);
void	fct_setenv(char **, char ***);
void	fct_unsetenv(char **, char ***);
int	fct_srdd(t_ll *, int);
int	fct_srdg(t_ll *, int);
int	fct_drdd(t_ll *, int);
int	fct_drdg(t_ll *, int);
int	fct_pipe(t_ll *, int);
int	redirect_open(t_ll *);
void	redirect_close(t_ll *);
int	is_builtin(char *);
void	wait_fork(t_ll *, char ***);
int	check_syntax(t_ll *);

#endif /* SH_H_ */
