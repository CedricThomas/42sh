/*
** GNC.h for GNC in /home/cedric/Desktop/get_next_cmd
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Fri Apr 21 17:37:03 2017 
** Last update Sat Apr 22 21:20:42 2017 Cédric Thomas
*/
#ifndef GNC_H_
# define GNC_H_

# define READ_SIZE	64
# define KEY_LINKED	4

typedef struct s_keypad	t_keypad;

typedef struct		s_keypad_fct
{
  int			(*fct)(t_keypad *);
  char			*sequence;
}			t_keypad_fct;

typedef struct		s_keypad
{
  int			index;
  char			*buffer;
  struct s_keypad_fct	key_parse[KEY_LINKED];
  struct termio		term;
}			t_keypad;

/*
**misc.c
*/
char	*my_seq(int size, ...);
void	my_putprintable(char *str, t_keypad *keypad);
char	*insert_str(char *s1, char *s2, int pos, t_keypad *pad);

/*
**LINE_EDIT
*/

/*
**bind.c
*/
int	enter(t_keypad *keypad);
int	end_of_file(t_keypad *keypad);
int	left_arrow(t_keypad *keypad);
int	right_arrow(t_keypad *keypad);

/*
**setup.c
*/
t_keypad	*init_keypad();
void		*end_keypad(t_keypad *keypad);

/*
**get_next_cmd.c
*/
char		*get_next_cmd(t_keypad *keypad);

#endif /* !GNC_H_ */
