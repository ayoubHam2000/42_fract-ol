# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/03 17:21:43 by aben-ham          #+#    #+#              #
#    Updated: 2022/02/10 11:55:03 by aben-ham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = \
	src/events/on_mouse_wheel.c \
	src/events/on_mouse_move.c \
	src/events/on_key_up.c \
	src/fract/mandelbrot_set.c \
	src/fract/julia_set.c \
	src/fract/bonus_fract.c \
	src/init.c \
	src/graph_loop.c \
	src/utils/check_args.c \
	src/utils/ft_atof.c \
	src/utils/ft_atoi.c \
	src/utils/ft_put_str.c \
	src/utils/get_colors.c \
	src/utils/ft_put_pixel.c \
	src/utils/update_window.c \
	main.c

NAME = fractol

#-Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -Werror -O3
INCLUDE = -I ./includes/
LINKING = -L/usr/local/lib -lSDL2  -lm
# -fsanitize=address

DEPFLAGS = -MMD -MF $(@:.o=.d)

OBJ_DIR = _OUT/

OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

deps = $(OBJ:.o=.d)

all : $(NAME)


#$(COMPILE) -c $< -o $@

$(NAME) : $(OBJ)
	gcc $(OBJ) $(LINKING) -o $(NAME)

$(OBJ) : $(OBJ_DIR)%.o : %.c
	mkdir -p $(dir $@)
	gcc $(CFLAGS) $(INCLUDE) -c $(@:_OUT/%.o=%.c) $(DEPFLAGS) -o $@

-include $(deps)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all
