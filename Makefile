# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/05 18:50:50 by tfregni           #+#    #+#              #
#    Updated: 2024/10/09 21:48:50 by tfregni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
NC = \033[0m

NAME = libasm.a

SRCS = $(wildcard $(SRCS_DIR)/*.s)
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.s=.o)))
EXECS = $(notdir $(OBJS:.o=)) # Remove the .o extension
SRCS_DIR = src
OBJS_DIR = obj

ASMC = nasm
ASM_FLAGS = -f elf64 -g # -f: format, elf64: 64-bit ELF format
AR = ar	# archive
AR_FLAGS = rcs # r: insert files, c: create archive, s: write an object-file index
LINKER = ld -g
RM = rm -rf 
MAKE = make -s

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(AR_FLAGS) $(NAME) $(OBJS)
	@echo "$(GREEN)Library '$(NAME)' created$(NC)"

# Rule to create the object files directory
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Rule to compile .s files to .o files
$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.s | $(OBJS_DIR)
	@$(ASMC) $(ASM_FLAGS) $< -o $@
	@echo "$(BLUE)Compiling $(notdir $<)$(NC)"

# Rule to create the executable
exec: $(EXECS)

test: $(NAME)
	@$(MAKE) -C test test
	./test/test

# Rule to link .o files to executables	
$(EXECS): %: $(OBJS_DIR)/%.o
	@$(LINKER) -lc -o $(notdir $@) $<
	@echo "$(GREEN)Executable '$(notdir $@)' created$(NC)"

# Clean target to remove object files and the directory
clean:
ifneq ($(wildcard $(OBJS_DIR)),)
	@echo "$(RED)Removing object files...$(NC)"
	@$(RM) $(OBJS_DIR)
endif

fclean: clean
ifneq ($(wildcard $(NAME) $(notdir $(OBJS:.o=))),)
	@echo "$(RED)Removing library and executables...$(NC)"
	@$(RM) $(NAME) $(notdir $(OBJS:.o=))
endif

re: fclean all

.PHONY: all clean fclean exec re test