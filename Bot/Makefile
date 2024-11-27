# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root <root@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 14:13:59 by lhojoon           #+#    #+#              #
#    Updated: 2024/11/27 13:28:06 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bot
CPP = c++
CFLAGS = -std=c++98 -Wall -Wextra -Werror -g3

SRCS = Bot.cpp main.cpp

OBJS = $(SRCS:cpp=o)
INCLUDES = -Iincludes -Ilibft


all: $(NAME)
$(NAME): $(OBJS)
	$(CPP) $(CFLAGS) $(OBJS) $(DEBUG) -o $(NAME)
%.o: %.cpp
	$(CPP) -c $< -o $@ $(CFLAGS) $(INCLUDES) $(DEBUG)
clean:
	rm $(OBJS) $(OBJB) -f
fclean: clean
	rm $(NAME) -f
re: fclean all
r: clean all
