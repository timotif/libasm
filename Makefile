# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/05 18:50:50 by tfregni           #+#    #+#              #
#    Updated: 2024/10/11 11:59:51 by tfregni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[0;33m
CYAN = \033[0;36m
MAGENTA = \033[0;35m
NC = \033[0m

NAME = libasm.a

SRCS = $(wildcard $(SRCS_DIR)/*.s)
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.s=.o)))
EXECS = $(notdir $(OBJS:.o=)) # Remove the .o extension
SRCS_DIR = src
OBJS_DIR = obj
TEST_DIR = test_unit

ASMC = nasm
ASM_FLAGS = -f elf64 -g # -f: format, elf64: 64-bit ELF format
AR = ar	# archive
AR_FLAGS = rcs # r: insert files, c: create archive, s: write an object-file index
LINKER = ld -g
RM = rm -rf 
MAKE = make -s

all: $(NAME) test	# Default target to compile the library and the test unit

help:	# Display this helpful message
# Automatically generating the help taking the rules from the Makefile with awk
	@awk 'BEGIN { \
	FS = ":.*#"; printf "Usage:\n\t$(YELLOW)make $(CYAN)<target> \
	$(NC)\n\nTargets:\n"; } \
	/^[a-zA-Z_0-9-]+:.*?#/ { \
	printf "$(CYAN)%-16s$(MAGENTA)%s\n$(NC)", $$1, $$2 } ' \
	Makefile
	@printf "\n$(RED)Note:$(NC) You can call $(YELLOW)./test $(BLUE)[ mandatory | bonus | <function_name> ]$(NC) to run the test unit\n"

$(NAME): $(OBJS)	# Create the library
	@$(AR) $(AR_FLAGS) $(NAME) $(OBJS)
	@echo "$(GREEN)Library '$(NAME)' created$(NC)"

# create the object files directory
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Rule to compile .s files to .o files
$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.s | $(OBJS_DIR)
	@$(ASMC) $(ASM_FLAGS) $< -o $@
	@echo "$(BLUE)Compiling $(notdir $<)$(NC)"

# Rule to create the executable
exec: $(EXECS)

test: $(NAME)	# Compile the test unit
	@$(MAKE) -C $(TEST_DIR) test

test_debug: $(NAME)	# Compile the test unit in debug mode
	@$(MAKE) -C $(TEST_DIR) debug

test_profile: $(NAME)	# Compile the test unit with profiling
	@$(MAKE) -C $(TEST_DIR) profile

test_help:	# Display the help message of the test unit
	@$(MAKE) -C $(TEST_DIR) help

run_test: test	# Run the test unit
	@./test

# Rule to link .o files to executables	
$(EXECS): %: $(OBJS_DIR)/%.o
	@$(LINKER) -fPIE -pie -lc -L. -lasm -o $(notdir $@) $<
	@echo "$(GREEN)Executable '$(notdir $@)' created$(NC)"

clean:	# Remove object files from the library and the test unit
	@$(MAKE) -C $(TEST_DIR) clean
ifneq ($(wildcard $(OBJS_DIR)),)
	@echo "$(RED)Removing object files...$(NC)"
	@$(RM) $(OBJS_DIR)
endif

fclean: clean	# Remove object files, executables and the library
	@$(MAKE) -C $(TEST_DIR) fclean
ifneq ($(wildcard $(NAME) $(notdir $(OBJS:.o=))),)
	@echo "$(RED)Removing library and executables...$(NC)"
	@$(RM) $(NAME) $(notdir $(OBJS:.o=))
endif

re: fclean all test	# Recompile the library and the test unit

.PHONY: all clean fclean exec re test test_debug test_profile test_help run_test help