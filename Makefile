# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/30 16:29:20 by ssar              #+#    #+#              #
#    Updated: 2021/07/06 09:11:51 by ssar             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLX = -Lmlx_linux -lmlx -lXext -lX11 -lm
CC = clang -Wall -Werror -Wextra
NAME = fdf
#DFLAG = -MP -MMD
SRCS = srcs/start/main.c \
       srcs/start/points.c \
       srcs/parse/get_map.c \
       srcs/utils/get_next_line.c \
       srcs/utils/get_next_line_utils.c \
       srcs/utils/ft_split.c \
       srcs/utils/basic_utils.c \
       srcs/utils/fdf_utils.c \
       srcs/utils/ft_atoi.c \
       srcs/utils/draw_utils.c \
       srcs/close/erreur.c \
       srcs/close/close.c


OBJS = $(SRCS:.c=.o)
#DEP = $(OBJS:.h=.d)
$(NAME) : $(OBJS)
	$(MAKE) -C ./mlx_linux
	$(CC) $(OBJS) -I./includes -I./usr/include $(MLX) -o $(NAME)
#	$(CC) $(DFLAG) $(OBJS) -I./includes -I./usr/include $(MLX) -o $(NAME)
all : $(NAME)
clean :
	rm -rf $(OBJS)
fclean : clean
	$(MAKE) clean -C ./mlx_linux
	rm -rf $(NAME)
re : fclean all

#-include $(DEP)
