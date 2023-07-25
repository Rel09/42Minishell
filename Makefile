CC = gcc
RM = rm -rf
NAME = minishell
FLAG = -Wall -Wextra -Werror
SPECIAL_FLAG = -lreadline

# Source files
FILES := main.c \
		srcs/env/init.c \
		srcs/env/show.c \
		srcs/env/findandremove.c \
        srcs/parser/input.c \
		srcs/tools/ft_bzero.c \
		srcs/tools/ft_strlen.c \
		srcs/tools/ft_strdup.c \
		srcs/tools/ft_strcmp.c \
		srcs/tools/ft_isdigit.c \
		srcs/tools/ft_isalpha.c \
		srcs/tools/ft_strncmp.c \
		srcs/tools/ft_strncat.c \
		srcs/tools/ft_isin2darray.c \
		srcs/tools/ft_sort2darray.c \
		srcs/tools/ft_copy2darray.c \
		srcs/tools/ft_count2darray.c \
		srcs/tools/ft_insert2darray.c \
		srcs/tools/ft_remove2darray.c \
		srcs/tools/ft_iscorrectenvname.c

# Object files
OBJS_DIR := objs
OBJS := $(addprefix $(OBJS_DIR)/, $(FILES:.c=.o))

#---------------------------  Colors & Prompt ---------------------------

CYAN="\033[1;36m"
GREEN="\033[1;32m"
ENDCOLOR="\033[0m"
CLEANING := $(GREEN)[+] Cleaning Completed$(ENDCOLOR)
SUCCESS := $(GREEN)[+] $(NAME) Successfully Compiled!$(ENDCOLOR)

#---------------------------  Compilation Main ---------------------------

all: $(OBJS_DIR) $(NAME)

# Create the objs directory and the subdirectory structure if it doesn't exist
$(OBJS_DIR):
	@mkdir -p $(dir $(OBJS))

# Compile source files into object files
$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@$(CC) $(FLAG) -c $< -o $@

# Build the final executable
$(NAME): $(OBJS)
	@$(CC) $(FLAG) $(OBJS) -lncurses $(READLINE) $(HISTORY) -o $(NAME) $(SPECIAL_FLAG)
	@echo $(SUCCESS)

#---------------------------     Cleaning      ---------------------------
clean:
	@$(RM) $(OBJS)
	@echo $(CLEANING)

fclean: clean
	@$(RM) $(NAME) $(OBJS_DIR)

re: fclean all

leaks: $(NAME)
	valgrind --track-fds=yes --trace-children=yes ./$(NAME)

run: $(NAME)
	./$(NAME)

#---------------------------       Phony        ---------------------------
.PHONY: all clean fclean re leaks run
