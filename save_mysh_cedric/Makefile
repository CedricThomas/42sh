##
## Makefile for Makefile in /home/cedric/lib
## 
## Made by Cédric Thomas
## Login   <cedric@epitech.net>
## 
## Started on  Sat Oct 22 10:37:32 2016 Cédric Thomas
## Last update Wed Apr  5 16:14:04 2017 Cédric Thomas
##

SRC	=	env/env.c				\
		env/key.c				\
		interpretor/misc.c			\
		interpretor/inter.c			\
		interpretor/separ.c			\
		interpretor/cmd.c			\
		interpretor/pipe.c			\
		interpretor/redir.c			\
		interpretor/redir/input.c		\
		interpretor/redir/double_input.c	\
		interpretor/redir/output.c		\
		interpretor/redir/double_output.c	\
		exec/exec.c				\
		exec/builtins/exit.c			\
		exec/builtins/cd.c			\
		exec/builtins/setenv.c			\
		exec/builtins/unsetenv.c		\
		exec/builtins/env.c			\
		exec/execve/pathfinder.c		\
		exec/execve/my_fork.c			\
		status/list_fds.c			\
		status/list_status.c			\
		prompt/prompt.c				\
		misc/str.c				\
		misc/misc.c				\
		main.c

PARSER	=	parsing.c				\
		lexer/list_lexer.c			\
		lexer/lexer.c				\
		lexer/shape_it.c			\
		lexer/misc/quote.c			\
		lexer/misc/separators.c			\
		tree/tree_list.c			\
		tree/tree.c				\
		syntax_checker/search.c			\
		syntax_checker/searcher_redir.c		\
		syntax_checker/searcher_cmd.c		\
		syntax_checker/check.c			\
		misc/match.c				\
		misc/tab.c				\
		misc/str.c

OBJ	=	$(SRC:.c=.o) $(addprefix parse/, $(PARSER:.c=.o))

NAME	=	mysh

LIB_F	=	./lib/

LIB	=	-lmy -lmyprintf -lgnl

INCLUDE	=	-I./include/

CFLAGS	+=	 $(INCLUDE) -g


all:		$(NAME)

$(NAME):	.SILENT

.SILENT:	$(OBJ)
		@echo "GNL..."
		@make -sC lib/GNL
		@echo "OK"
		@echo "my..."
		@make -sC lib/my
		@echo "OK"
		@echo "my_printf..."
		@make -sC lib/my_printf
		@echo "OK"
		@gcc -o $(NAME) $(OBJ) -L$(LIB_F) $(LIB)

clean:
		@make -sC lib/GNL fclean
		@make -sC lib/my fclean
		@make -sC lib/my_printf fclean
		@rm -f $(OBJ)

fclean:		clean
		@rm -f $(NAME)

re: 		fclean all

.PHONY: all clean fclean re
