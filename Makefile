# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root <root@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 14:13:59 by lhojoon           #+#    #+#              #
#    Updated: 2024/09/06 13:52:45 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
CPP = c++
CFLAGS = -std=c++98 -Wall -Wextra -Werror -g3

DIR = src
SRCS_RAW =	main.cpp \
			utils.cpp \
			ircserv.cpp \
			CommandPass.cpp \
			ACommand.cpp \
			Channel.cpp \
			User.cpp \
			Errors.cpp

SRCS = $(addprefix $(DIR)/,$(SRCS_RAW))
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
