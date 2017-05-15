##
## Makefile for Makefile in /home/cedric/lib
## 
## Made by Cédric Thomas
## Login   <cedric@epitech.net>
## 
## Started on  Sat Oct 22 10:37:32 2016 Cédric Thomas
## Last update Mon May 15 13:12:18 2017 Thibaut Cornolti
##
## Last update Thu May 11 17:40:01 2017 Thibaut Cornolti
##

all:
		@make -sC parseur42
		@cp parseur42/42sh .

clean:
		@make clean -sC parseur42

fclean:
		@make fclean -sC parseur42

re: 		fclean all

.PHONY: all clean fclean re
