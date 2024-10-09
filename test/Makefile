# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 22:56:00 by tfregni           #+#    #+#              #
#    Updated: 2024/10/09 00:03:25 by tfregni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
NC = \033[0m

SRCS_DIR = src
OBJS_DIR = obj
INCLUDE_DIR = inc
SRCS = $(addprefix $(SRCS_DIR)/, main.c test_strlen.c test_strcpy.c)
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = test
LIB_DIR = ../
LIB = libasm.a
RM = rm -rf
MAKE = make -s

all: $(NAME)

debug: CFLAGS += -g -DDEBUG
debug: re

profile: CFLAGS += -DPROFILE
profile: re

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c | $(OBJS_DIR)
	@echo "$(BLUE)Compiling $(notdir $<)$(NC)"
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(LIB_DIR)$(LIB):
	@$(MAKE) -C $(LIB_DIR)

$(NAME): $(LIB_DIR)$(LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIB_DIR) -lasm -o $(NAME)

clean:
	@$(MAKE) -C $(LIB_DIR) clean
ifneq ($(wildcard $(OBJS)),)
	@$(RM) $(OBJS_DIR)
endif

fclean: clean
	@$(MAKE) -C $(LIB_DIR) fclean
ifneq ($(wildcard $(NAME)),)
	@$(RM) $(NAME)
endif

re: fclean all

.PHONY: all clean fclean re debug profile