##
## Makefile for Makefile in /home/cedric/lib
## 
## Made by Cédric Thomas
## Login   <cedric@epitech.net>
## 
## Started on  Sat Oct 22 10:37:32 2016 Cédric Thomas
## Last update Sat Apr 22 12:19:30 2017 
##

SRC		=	main.c				\
			misc.c				\
			line_edit/get_next_cmd.c	\
			line_edit/setup.c		\
			line_edit/bind.c		\

OBJ		=	$(SRC:.c=.o)

NAME		=	GNC

LIB_F		=	./lib/

LIB		=	-lmy -lmyprintf -lgnl -lalloc -lncurses

INCLUDE		=	-I./include/

CFLAGS		+=	 $(INCLUDE) -g -W -Wall -Wextra

REDDARK         =       \033[31;2m

RED             =       \033[31;1m

GREEN           =       \033[32;1m

YEL             =       \033[33;1m

BLUE            =       \033[34;1m

PINK            =       \033[35;1m

CYAN            =       \033[36;1m

RES             =       \033[0m

all:		$(NAME)

$(NAME): .CMPLIB .SILENT

.CMPLIB:
	@echo "$(CYAN)Compiling libmy...$(RES)"
	@make --no-print-directory -sC lib/my
	@echo "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
	@echo "$(CYAN)Compiling liballoc...$(RES)"
	@make --no-print-directory -sC lib/libmalloc
	@echo "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
	@echo "$(CYAN)Compiling libmyprintf...$(RES)"
	@make --no-print-directory -sC lib/my_printf
	@echo "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
	@echo "$(CYAN)Compiling libgnl...$(RES)"
	@make --no-print-directory -sC lib/GNL
	@echo "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
	@echo

.SILENT:$(OBJ)
	@echo
	@echo "$(GREEN)Everything compiled smoothly. Now compiling dependancies...$(RES)"
	@echo
	@echo "$(CYAN)Linking $(NAME)...$(RES)"
	@gcc -o $(NAME) $(OBJ) -L$(LIB_F) $(LIB)
	@echo "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
	@echo
	@echo "$(GREEN)---- $(NAME) READY ----$(RES)"
	@echo

clean:
		@$(foreach var, $(OBJ), if [ -e $(var) ] ; then \
		printf "[$(RED)RM$(RES)] $(YEL)$(var)$(RES)\n" \
		&& $(RM) $(var) ; fi ;)
		@make --no-print-directory -sC lib/GNL fclean
		@make --no-print-directory -sC lib/my fclean
		@make --no-print-directory -sC lib/my_printf fclean
		@make --no-print-directory -sC lib/libmalloc fclean
		@rm -f $(OBJ)
		@echo "$(GREEN)---- $(NAME) CLEANED ----$(RES)"
		@echo

fclean:		clean
		@if [ -e $(NAME) ] ; then \
		printf "[$(RED)RM EXEC$(RES)] $(YEL)$(NAME)$(RES)\n" \
		&& rm -f $(NAME) ; fi
		@rm -f $(NAME)
		@echo "$(GREEN)---- $(NAME) REMOVED ----$(RES)"
		@echo


re: 		fclean all

%.o:	%.c
	@echo "[$(RED)COMPILE$(RES)] $(YEL)$<$(RES) $(BLUE)=>$(RES) $(YEL)$@$(RES)"
	@gcc $(CFLAGS) -o $@ -c $<

.PHONY: all clean fclean re
