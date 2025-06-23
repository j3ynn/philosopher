NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
DEBUG_FLAGS = -g -fsanitize=thread
OPTIMIZE_FLAGS = -O2

SRCDIR = .
OBJDIR = obj

SRCS = 	action.c \
		init.c \
		memory.c \
		utils.c \
		utils_base.c \
		main.c

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

HEADER = philo.h

GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += $(DFLAGS)
debug: fclean $(NAME)
	@echo "$(GREEN)✓ Debug version compiled!$(RESET)"

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)
	@echo "$(GREEN)✓ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ All cleaned!$(RESET)"

re: fclean all

test: $(NAME)
	@echo "$(BLUE)Running test cases...$(RESET)"
	@echo "Test 1: 4 philosophers, 410ms die, 200ms eat, 200ms sleep"
	@./$(NAME) 4 410 200 200
	@echo "\nTest 2: 5 philosophers, 800ms die, 200ms eat, 200ms sleep"
	@./$(NAME) 5 800 200 200

test_meals: $(NAME)
	@echo "$(BLUE)Testing with limited meals...$(RESET)"
	@echo "Test: 5 philosophers, each must eat 7 times"
	@./$(NAME) 5 800 200 200 7

valgrind: $(NAME)
	@echo "$(BLUE)Running valgrind...$(RESET)"
	@valgrind --tool=helgrind --read-var-info=yes ./$(NAME) 4 410 200 200

help:
	@echo "$(BLUE)Available targets:$(RESET)"
	@echo "  all       - Compile the project"
	@echo "  debug     - Compile with debug flags"
	@echo "  clean     - Remove object files"
	@echo "  fclean    - Remove object files and executable"
	@echo "  re        - Recompile everything"
	@echo "  test      - Run basic tests"
	@echo "  test_meals- Test with limited meals"
	@echo "  valgrind  - Run with helgrind (thread checker)"
	@echo "  help      - Show this help"

.PHONY: all clean fclean re debug test test_meals valgrind help
