##
## Makefile for Makefile in /home/thibrex/delivery/CPool_Day10/do-op
## 
## Made by Thibaut Cornolti
## Login   <thibaut.cornolti@epitech.eu>
## 
## Started on  Sat Oct 15 22:12:03 2016 Thibaut Cornolti
## Last update Wed Apr 12 09:14:39 2017 Thibaut Cornolti
##
SRC	=	main.c		\
		run.c		\
		msg.c		\
		get_env.c	\
		get_argv.c	\
		chained.c	\
		commander.c	\
		builtin.c	\
		fct.c		\
		utils.c		\
		cat_path.c	\
		search_path.c	\
		check.c		\
		cd.c		\
		exit.c		\
		parse.c		\
		pipe.c		\
		redirection.c	\
		tools.c		\
		redirect_utils.c

OBJS	=	$(SRCS:.c=.o)

NAME	=	42sh

CC	=	gcc -g

HEADER	=	include/

RM	=	rm -f

LIB_P	=	-Llib/my

LIB	=	-lmy

all:	$(NAME)

$(NAME):
	cd lib/my/ && make
	$(CC) -o $(NAME) -I$(HEADER) $(SRC) $(LIB_P) $(LIB) -Wall -Wextra -pedantic

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
