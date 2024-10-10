# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 22:56:00 by tfregni           #+#    #+#              #
#    Updated: 2024/10/10 23:12:59 by tfregni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
RED = \033[0;31m
YELLOW = \033[0;33m
GREEN = \033[0;32m
BLUE = \033[0;34m
NC = \033[0m

SRCS_DIR = src
OBJS_DIR = obj
INCLUDE_DIR = inc
SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = test
LIB_DIR = ../
LIB = libasm.a
RM = rm -r
MAKE = make -s

help:
	@printf "$(YELLOW)Usage: make [test | debug | profile | re | clean | fclean]\n$(NC)"
	@printf "$(BLUE)\ttest: $(NC)Compile the project\n"
	@printf "$(BLUE)\tdebug: $(NC)Compile the project with debug message and flags\n"
	@printf "$(BLUE)\tprofile: $(NC)Compile the project with time profiling messages\n"
	@printf "$(BLUE)\tre: $(NC)Recompile the project\n"
	@printf "$(BLUE)\tclean: $(NC)Remove object files\n"
	@printf "$(BLUE)\tfclean: $(NC)Remove object files and executable\n"

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
	@cp $(NAME) $(LIB_DIR)

clean:
ifneq ($(wildcard $(OBJS)),)
	@$(RM) $(OBJS_DIR)
endif

fclean: clean
ifneq ($(wildcard $(NAME)),)
	@$(RM) $(NAME)
	@$(RM) $(LIB_DIR)$(NAME)
endif

re: fclean all

.PHONY: all clean fclean re debug profile