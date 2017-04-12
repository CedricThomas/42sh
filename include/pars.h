/*
** pars.h for mysh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_minishell2
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Thu Mar 23 14:01:31 2017 Thibaut Cornolti
** Last update Tue Apr  4 13:18:04 2017 Thibaut Cornolti
*/

#ifndef PARS_H_
# define PARS_H_

# define TOK_PIPE	(1 << 0)
# define TOK_SRDD	(1 << 1)
# define TOK_SRDG	(1 << 2)
# define TOK_DRDD	(1 << 3)
# define TOK_DRDG	(1 << 4)
# define TOK_SEPA	(1 << 5)

t_ll		*my_pars(char *);
void		my_malloc_list(t_ll *);

#endif /* !PARS_H_ */
