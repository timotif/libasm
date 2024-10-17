# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/05 18:50:50 by tfregni           #+#    #+#              #
#    Updated: 2024/10/17 21:53:14 by tfregni          ###   ########.fr        #
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
BONUS_NAME = libasm_bonus.a
TEST_NAME = test

SRCS = $(wildcard $(SRCS_DIR)/*.s)
BONUS_SRCS = $(wildcard $(BONUS_DIR)/*.s)
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.s=.o)))
BONUS_OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(BONUS_SRCS:.s=.o)))
EXECS = $(notdir $(OBJS:.o=)) # Remove the .o extension
SRCS_DIR = src
BONUS_DIR = bonus
OBJS_DIR = obj
TEST_DIR = test_unit

ASMC = nasm
ASM_FLAGS = -f elf64 -g # -f: format, elf64: 64-bit ELF format
AR = ar	# archive
AR_FLAGS = rcs # r: insert files, c: create archive, s: write an object-file index
LINKER = ld -g
RM = rm -rf 
MAKE = make -s --no-print-directory

banner:
	clear
	@echo "$(YELLOW)"
	@echo "▗▖   ▗▄▄▄▖▗▄▄▖  ▗▄▖  ▗▄▄▖▗▖  ▗▖"
	@echo "▐▌     █  ▐▌ ▐▌▐▌ ▐▌▐▌   ▐▛▚▞▜▌"
	@echo "▐▌     █  ▐▛▀▚▖▐▛▀▜▌ ▝▀▚▖▐▌  ▐▌"
	@echo "▐▙▄▄▖▗▄█▄▖▐▙▄▞▘▐▌ ▐▌▗▄▄▞▘▐▌  ▐▌"
	@echo "               tfregni@42berlin$(NC)"
	@echo ""
	@echo "$(CYAN)To use my tests check your options with $(YELLOW)make help$(NC)" 
	@echo ""
	@$(MAKE) all
	
$(NAME): $(OBJS)	# Create the library
	@$(AR) $(AR_FLAGS) $(NAME) $(OBJS)
	@echo "$(GREEN)Library '$(NAME)' created$(NC)"
	
all: bonus test	# Target to compile the library and the test unit

help:	# Display this helpful message
# Automatically generating the help taking the rules from the Makefile with awk
# (credit to mcutura@42berlin for the idea!)
	@awk 'BEGIN { \
	FS = ":.*#"; printf "Usage:\n\t$(YELLOW)make $(CYAN)<target> \
	$(NC)\n\nTargets:\n"; } \
	/^[a-zA-Z_0-9-]+:.*?#/ { \
	printf "$(CYAN)%-16s$(MAGENTA)%s\n$(NC)", $$1, $$2 } ' \
	Makefile
ifneq ("$(wildcard $(TEST_NAME))", "")
	@printf "\n$(RED)Note:$(NC) You can call $(YELLOW)./test $(BLUE)[ mandatory | bonus | <function_name> ]$(NC) to run the test unit\n"
endif

bonus: $(BONUS_NAME)	# Compile the bonus functions

$(BONUS_NAME): $(NAME) $(BONUS_OBJS)	# Compile the bonus functions
	@$(AR) $(AR_FLAGS) $(BONUS_NAME) $(OBJS) $(BONUS_OBJS)
	@echo "$(GREEN)Bonus functions added to the library$(NC)"

# create the object files directory
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Rule to compile .s files to .o files
$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.s | $(OBJS_DIR)
	@$(ASMC) $(ASM_FLAGS) $< -o $@
	@echo "$(BLUE)Compiling $(notdir $<)$(NC)"

# Rule to compile bonus .s files to .o files
$(OBJS_DIR)/%.o: $(BONUS_DIR)/%.s | $(OBJS_DIR)
	@$(ASMC) $(ASM_FLAGS) $< -o $@
	@echo "$(MAGENTA)Compiling bonus $(notdir $<)$(NC)"

test: bonus	# Compile the test unit
	@$(MAKE) -C $(TEST_DIR) test_me
ifneq ("$(wildcard $(TEST_NAME))", "")
	@printf "\n$(RED)Note:$(NC) You can call $(YELLOW)./test $(BLUE)[ mandatory | bonus | <function_name> ]$(NC) to run the test unit\n"
endif

test_nosleep:	# Compile the test unit with the NOSLEEP flag
	@$(MAKE) -C $(TEST_DIR) no-sleep

test_debug: bonus	# Compile the test unit in debug mode
	@$(MAKE) -C $(TEST_DIR) debug

test_profile: bonus	# Compile the test unit with profiling
	@$(MAKE) -C $(TEST_DIR) profile

test_help:	# Display the help message of the test unit
	@$(MAKE) -C $(TEST_DIR) help

run_test: test	# Run the test unit
	@./test

clean:	# Remove object files from the library and the test unit
ifneq ($(wildcard $(OBJS_DIR) $(TEST_DIR)/obj/*),)
	@$(MAKE) -C $(TEST_DIR) clean
	@echo "$(RED)Removing object files...$(NC)"
	@$(RM) $(OBJS_DIR)
endif

fclean: clean	# Remove object files, executables and the library
ifneq ($(wildcard $(NAME) $(notdir $(OBJS:.o=)) $(BONUS_NAME) $(TEST_DIR)/obj/* $(TEST_NAME)),)
	@$(MAKE) -C $(TEST_DIR) fclean
	@echo "$(RED)Removing library and executables...$(NC)"
	@$(RM) $(NAME) $(notdir $(OBJS:.o=)) $(BONUS_NAME)
endif

re: fclean all	# Recompile the library and the test unit

.PHONY: all clean fclean exec re help \
		test test_debug test_profile test_help \
		run_test test_nosleep