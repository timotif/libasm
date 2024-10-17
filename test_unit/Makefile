# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 22:56:00 by tfregni           #+#    #+#              #
#    Updated: 2024/10/17 22:30:16 by tfregni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
RED = \033[0;31m
YELLOW = \033[0;33m
CYAN = \033[0;36m
MAGENTA = \033[0;35m
GREEN = \033[0;32m
BLUE = \033[0;34m
NC = \033[0m

SRCS_DIR = src
OBJS_DIR = obj
INCLUDE_DIR = inc
SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR)
NAME = test
LIB_DIR = ../
LIB = libasm.a
LIB_BONUS = libasm_bonus.a
RM = rm -r
MAKE = make -s

test_me:
ifeq ($(wildcard $(NAME)),)
	@echo ""
	@echo "$(CYAN)*************"
	@echo "* TEST_UNIT *"
	@echo "*************$(NC)"
endif
	@$(MAKE) all

help:
	@printf "$(YELLOW)Usage: make [test | debug | profile | re | clean | fclean]\n$(NC)"
	@printf "$(BLUE)\ttest: $(NC)Compile the project\n"
	@printf "$(BLUE)\tdebug: $(NC)Compile the project with debug message and flags\n"
	@printf "$(BLUE)\tprofile: $(NC)Compile the project with time profiling messages\n"
	@printf "$(BLUE)\tre: $(NC)Recompile the project\n"
	@printf "$(BLUE)\tclean: $(NC)Remove object files\n"
	@printf "$(BLUE)\tfclean: $(NC)Remove object files and executable\n"

all: bonus

no-sleep: CFLAGS += -DNOSLEEP
no-sleep: re

bonus: $(LIB_BONUS)

debug: CFLAGS += -g -DDEBUG
debug: re

profile: CFLAGS += -DPROFILE
profile: re

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c | $(OBJS_DIR)
	@echo "$(BLUE)Compiling $(notdir $<)$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIB_DIR)$(LIB):
	@$(MAKE) -C $(LIB_DIR)

$(LIB_DIR)$(LIB_BONUS):
	@$(MAKE) -C $(LIB_DIR) bonus

$(LIB_BONUS): $(LIB_DIR)$(LIB_BONUS) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIB_DIR) -lasm_bonus
	@cp $(NAME) $(LIB_DIR)

$(NAME): $(LIB_DIR)$(LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIB_DIR) -lasm 
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

.PHONY: all test_me clean fclean re debug profile