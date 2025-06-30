NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCDIR = .
OBJDIR = obj

SOURCES = philo.c \
		  action.c \
		  init.c \
		  memory.c \
		  utils.c \
		  utils_base.c \
		  cose_in_piu.c

OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo "$(GREEN)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	rm -rf $(OBJDIR)

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(RESET)"
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
