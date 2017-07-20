#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sprosian <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/28 15:16:40 by sprosian          #+#    #+#              #
#    Updated: 2017/01/25 18:28:52 by sromanet         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = bus_errrror
SRC = main.c
SRCO = $(SRC:.c=.o)
INCLUDES = bus_errrror.h
FLAGS =

all: $(NAME)

$(NAME): $(SRCO)
	gcc $(FLAGS) -o $(NAME) $(SRCO) libft/libft.a

.c.o:
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(SRCO)

fclean: clean
	rm -f $(NAME)

re: fclean all
