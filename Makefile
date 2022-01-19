# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/01 22:25:32 by tshimoda          #+#    #+#              #
#    Updated: 2022/01/19 18:27:48 by tshimoda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= pipex

AR= ar rc
RM= rm -rf

CC= gcc
CFLAGS= -Wall -Werror -Wextra -c

SDIR= sources
SDIR_B= src_bonus

ODIR= objects
ODIR_B= obj_bonus

SRCS= main.c \
		process.c \

SRCS_B= main_bonus.c \
		process_bonus.c \


OBJS= $(SRCS:.c=.o)
OBJS_B= $(SRCS_B:.c=.o)

SFIX= $(addprefix $(SDIR)/, $(SRCS))
OFIX= $(addprefix $(ODIR)/, $(OBJS))

SFIX_B= $(addprefix $(SDIR_B)/, $(SRCS_B))
OFIX_B= $(addprefix $(ODIR_B)/, $(OBJS_B))

VPATH= $(SDIR) $(SDIR_B)

$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(ODIR_B)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(NAME): $(ODIR) $(OFIX)
	$(MAKE) -C ./libft
	$(CC) $(OFIX) -lft -L./libft -o $(NAME)
	@echo "\033[1;32m 下田、徳太郎のPIPEX\033[0;39m"

all:    $(NAME)

bonus: $(ODIR_B) $(OFIX_B)
		$(MAKE) -C ./libft
		$(CC) $(OFIX_B) -lft -L./libft -o $(NAME)
		@echo "\033[1;32m 下田、徳太郎のPIPEX\033[0;39m"

$(ODIR):
		mkdir -p $(ODIR)

$(ODIR_B):
		mkdir -p $(ODIR_B)


clean:
	$(MAKE) clean -C ./libft
	$(RM) $(ODIR) $(ODIR_B)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)
	@echo "\033[1;34m make fclean done!\033[0;39m"

re:     clean all

.PHONY: all bonus clean flcean re