/*
** pars.h for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell2
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu Mar 23 14:01:31 2017 Thibaut Cornolti
** Last update Thu Apr 13 12:11:09 2017 Thibaut Cornolti
*/

#ifndef PARS_H_
# define PARS_H_

# define TOK_PIPE	(1 << 0)
# define TOK_SRDD	(1 << 1)
# define TOK_SRDG	(1 << 2)
# define TOK_DRDD	(1 << 3)
# define TOK_DRDG	(1 << 4)
# define TOK_SEPA	(1 << 5)

# define TOK_DPIP	(1 << 6)
# define TOK_DESP	(1 << 7)

t_ll		*my_pars(char *);
int		get_token(char *);
void		my_malloc_list(t_ll *);

#endif /* !PARS_H_ */
