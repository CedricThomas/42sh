##
## Makefile for Makefile in /home/thibrex/delivery/CPool_Day10/do-op
## 
## Made by Thibaut Cornolti
## Login   <thibaut.cornolti@epitech.eu>
## 
## Started on  Sat Oct 15 22:12:03 2016 Thibaut Cornolti
## Last update Thu Apr 13 12:09:56 2017 Thibaut Cornolti
##
SRC	=	main.c				\
		core/run.c			\
		utils/msg.c			\
		utils/get_env.c			\
		utils/get_argv.c		\
		parse/chained.c			\
		core/commander.c		\
		builtin/builtin.c		\
		builtin/fct.c			\
		utils/utils.c			\
		path/cat_path.c			\
		path/search_path.c		\
		parse/check.c			\
		builtin/cd.c			\
		builtin/exit.c			\
		parse/parse.c			\
		redirection/pipe.c		\
		redirection/redirection.c	\
		utils/tools.c			\
		parse/get_token.c		\
		redirection/redirect_utils.c

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
