/*
** syntax.h for parseur in /home/cedric/delivery/parseur_ll
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar 22 18:26:36 2017 
** Last update Wed Apr  5 18:27:23 2017 Cédric Thomas
*/

#ifndef SYNTAX_H_
# define SYNTAX_H_

# define SKIP	" \t"

# define INIB	"\"'"

# define T_ARGS		(1 << 0)
# define T_COMMAND	(1 << 1)
# define T_FILE		(1 << 2)
# define T_FLUX_REDIR	(1 << 3)
# define T_FLUX		(1 << 4)
# define T_SEPAR	(1 << 5)

# define INIB_ON	(1 << 30)

# define T_COMMON	(T_ARGS | T_COMMAND | T_FILE)

# define INIBED(x)	((x & INIB_ON) == INIB_ON)
# define UNTAG(x, y)	(x & ~y)

# define MAX_TYPES	4

typedef struct s_info	t_info;

typedef struct		s_node
{
  char			*data;
  int			type;
  struct s_node		*root;
  struct s_node		*left;
  struct s_node		*right;
}			t_node;

typedef struct		s_syntax
{
  int			weight;
  char			**values;
}			t_syntax;

typedef struct		s_token
{
  int			type;
  char			*token;
  struct s_token	*prev;
  struct s_token	*next;
}			t_token;

/*
**lexer.c
*/
t_node		*parse_cmd(t_syntax *my_syntax, char *str, t_info *info);
t_syntax	*get_syntax();
void		free_syntax(t_syntax **my_syntax);

/*
**misc
*/

/*
**str.c
*/
int	my_cstrnlen(char *str, char c);
int	my_strnlen(char *str, char *c);
char	*my_strndup(char *str, int len);
int	composed_of(char *str, char *only_composed);
void	*my_free_null(void *ptr);

/*
**tab.c
*/

char	**tab_create(int size, ...);

/*
**match.c
*/
int     match(char *tested, char *pattern);

/*
**lexer
*/

/*
**shape_it.c
*/
char	*shape_for_token(char *str, t_syntax *my_syntax);
int	redefine_tokens(t_token **token);

/*
**list_lexer.c
*/

int	my_free_token(t_token **ll);
int	my_del_list_token(t_token **ll, t_token *elem);
int	my_show_token(t_token *ll);
int	my_put_list_token(t_token **ll, char *token, int type);
void	swap_token(t_token *one, t_token *two);

/*
**lexer.c
*/

t_token	*get_token(char *str, t_syntax *my_syntax);

/*
**lexer/misc
*/

/*
**separators.c
*/

char	*shape_separator(char *str, char **seq);
int	is_in_tab(char *str, char **tab, int *index);

/*
**quote.c
*/
char	*delete_nbchar(char *str, int nb, int index);
char	*add_substr(char *str, char *substr, int index);
char	*replace_unquoted_str(char *str, char *find, char *replace);
char    *dequotificator(char *str);

/*
**tree/
*/

/*
**tree.c
*/
t_node	*create_tree(t_node *root, t_syntax *my_syntax,
		     t_token *start, t_token *end);

/*
**tree_list.c
*/
t_node	*create_node(t_node *root, char *value, int type);
t_node	*show_nodes(t_node *root, int depth, int side);
void	my_free_tree(t_node **root);

/*
**syntax_checker/
*/

/*
**search.c
*/
int	search_parent(t_node *root,
		      int (*searcher)(t_node *root, char c),
		      char c);
int	search_child(t_node *root,
		     int (*searcher)(t_node *root, int branch),
		     int branch);
int	search_child_auto(t_node *root,
		     int (*searcher)(t_node *root, int branch));

/*
**searcher_redir.c
*/
int	search_rightflux_error(t_node *root, int branch);
int	search_leftflux_error(t_node *root, int branch);
int	search_flux_parent(t_node *root, char c);
int	search_in(t_node *root, char c);

/*
**seacher_cmd.c
*/
int	search_command(t_node *root, int branch);

/*
**check_syntax_pipe.c
*/
int	check_syntax_pipe(t_node *root);
int	check_syntax_redir_in(t_node *root);
int	check_syntax_redir_out(t_node *root);
int	check_double_redir(t_node *root, char c);

#endif /* !SYNTAX_H_ */
