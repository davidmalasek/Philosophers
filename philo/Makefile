# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 16:14:47 by dmalasek          #+#    #+#              #
#    Updated: 2025/07/28 20:06:53 by dmalasek         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread

# Source files
SRC_DIR = src
SRC = main.c valid.c utils.c init.c routine.c monitor.c thread.c actions.c cleanup.c

# Output
NAME = philo

# Temporary directory for object files
OBJ_DIR = build
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Rules
all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

# Rule to compile .c files into .o files inside the temporary directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "[\033[0;32mBUILT\033[0m] %s\n" "$<"

# Ensure the build directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean:
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)

re: $(NAME)

.PHONY: all clean fclean re