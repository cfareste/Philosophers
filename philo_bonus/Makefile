# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 13:59:33 by cfidalgo          #+#    #+#              #
#    Updated: 2024/05/03 01:40:17 by cfidalgo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==========# COLORS #==========#
DEF_COLOR = \033[0m
WHITE_BOLD = \033[1m
BLACK = \033[1;30m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
PINK = \033[1;35m
CIAN = \033[1;36m
#==============================#


#===========# NAME #===========#
NAME = philo_bonus
#==============================#


#=========# COMMANDS #=========#
CC = GCC
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

RMRF = rm -rf
MKDIR = mkdir -p
#==============================#


#===========# DIRS #===========#
INC = ./
SRC_DIR = ./
OBJS_DIR = bin/
#==============================#


#===========# FILE #===========#
FILES = philo_bonus.c \
		checker_bonus.c \
		initiators_bonus.c \
		destroyers_bonus.c \
		simulation_bonus.c \
		simulation_helpers_bonus.c \
		activities_bonus.c \
		utils_bonus.c \
		error_handler_bonus.c
#==============================#


#===========# SRCS #===========#
SRC = $(addprefix $(SRC_DIR), $(FILES))
#==============================#


#===========# OBJS #===========#
OBJS = $(addprefix $(OBJS_DIR), $(FILES:.c=.o))
#==============================#


#===========# DEPS #===========#
DEPS = $(OBJS:.o=.d)
#==============================#


#============ RULE ============#
all:
	@echo "$(CIAN)Compiling program $(PINK)\"$(NAME)\"$(CIAN)...$(YELLOW)"
	@$(MAKE) $(NAME) --no-print-directory
	@echo "$(GREEN)Program compiled and ready to use.$(DEF_COLOR)"


$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


$(OBJS_DIR)%.o: $(SRC_DIR)%.c Makefile
	@$(MKDIR) $(OBJS_DIR)
	@$(CC) $(CFLAGS) -MMD -c $< -o $@
	@echo "$(YELLOW)Compiling object $(PINK)$<$(YELLOW)...$(DEF_COLOR)"


clean:
	@$(RMRF) $(OBJS_DIR)
	@echo "$(RED)Objects and dependencies for $(YELLOW)'$(NAME)'$(RED) removed.$(DEF_COLOR)"


fclean: clean
	@$(RMRF) $(NAME)
	@echo "$(RED)Removed program $(YELLOW)'$(NAME)'$(RED).$(DEF_COLOR)"


re: fclean all


#==============================#


#=========== EXTRAS ===========#
.PHONY: all clean fclean re

-include $(DEPS)
#=========== EXTRAS ===========#