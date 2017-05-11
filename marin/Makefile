##
## Makefile for lib_llist in /home/maje/Dropbox/delivery/B2/PSU/PSU_2016_42sh/marin
## 
## Made by maje
## Login   <marin.brunel@epitech.eu>
## 		add_begin_list.c	\
##		create_list.c
## Started on  Thu Apr 13 17:25:15 2017 maje
## Last update Tue May  9 14:17:34 2017 maje
##

SRC	=	add_begin_list.c		\
		aff_list.c			\
		remove_end_list.c		\
		remove_begin_list.c		\
		add_end_list.c

OBJ     =      	$(SRC:.c=.o)

RM      =      	rm -f

MV      =      	mv

CP     	=      	cp

CC     	=      	gcc

AR     	=      	ar rc

CFLAGS	+=	-Iinclude	

NAME    =      	liblist.a

all:   	$(NAME)

$(NAME):       	$(OBJ)
	$(AR) $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
#$(CC) -w -c $(SRC) -Wall -pedantic
