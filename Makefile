##
## Makefile for Makefile in /home/cedric/lib
## 
## Made by Cédric Thomas
## Login   <cedric@epitech.net>
## 
## Started on  Sat Oct 22 10:37:32 2016 Cédric Thomas
## Last update Mon May 15 13:11:23 2017 Thibaut Cornolti
##
## Last update Thu May 11 17:40:01 2017 Thibaut Cornolti
##

all:
		make -C parseur42
		cp parseur42/42sh .

clean:
		make clean -C parseur42

fclean:
		make fclean -C parseur42

re: 		fclean all

.PHONY: all clean fclean re
