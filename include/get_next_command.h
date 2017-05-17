/*
** GNC.h for GNC in /home/cedric/Desktop/get_next_cmd
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Fri Apr 21 17:37:03 2017 
** Last update Wed May 17 10:09:38 2017 Thibaut Cornolti
*/
#ifndef GNC_H_
# define GNC_H_

# define READ_SIZE	20
# define KEY_LINKED	10

typedef struct s_keypad t_keypad;

typedef struct		s_keypad_fct
{
  int			(*fct)(t_keypad *keypad);
  char			*sequence;
}			t_keypad_fct;

typedef struct		s_keypad
{
  int			valid;
  int			end;
  int			index;
  char			*line;
  struct s_keypad_fct	keys[KEY_LINKED];
  struct termio		term;
  struct s_system	*sys;
}			t_keypad;

/*
**str.c
*/
char		*insert_str(char *s1, char *s2, int pos);
char		*delete_a_char(char *str, int index);

/*
**binds
*/
int		enter(t_keypad *keypad);
int		end_of_file(t_keypad *keypad);
int		left_arrow(t_keypad *keypad);
int		right_arrow(t_keypad *keypad);
int		delete_char(t_keypad *keypad);
int		suppr_char(t_keypad *keypad);
int		go_end(t_keypad *keypad);
int		go_start(t_keypad *keypad);
int		bind_clear(t_keypad *keypad);
int		auto_complete(t_keypad *keypad);

void		default_append(char *buff, t_keypad *keypad, int size_buff);

/*
**setup.c
*/
t_keypad	*init_keypad();
void		*end_keypad(t_keypad *keypad);

/*
**get_next_cmd.c
*/
char		*get_next_cmd(t_keypad *keypad);

/*
**term set
*/
int	my_set_term(t_keypad *pad);
int	my_reset_term(t_keypad *pad);

#endif /* !GNC_H_ */
