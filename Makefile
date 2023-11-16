# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/19 02:47:29 by jaqribei          #+#    #+#              #
#    Updated: 2023/10/31 07:10:35 by jaqribei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#+++++++++ COLORS +++++++++
CYAN = \033[1;36m
RESET = \033[0m
GREEN = \033[1;32m
#+++++++++ COLORS +++++++++

S_NAME = server
C_NAME = client

S_NAME_BONUS = server_bonus
C_NAME_BONUS = client_bonus

CC = cc

FLAGS = -Wall -Wextra -Werror -g3

INCLUDES = -I ./libft/

S_SRC = server.c
S_SRC_BONUS = server_bonus.c

S_OBJ = $(S_SRC:%.c=%.o)
S_OBJ_BONUS = $(S_SRC_BONUS:%.c=%.o)

C_SRC = client.c
C_SRC_BONUS = client_bonus.c

C_OBJ = $(C_SRC:%.c=%.o)
C_OBJ_BONUS = $(C_SRC_BONUS:%.c=%.o)

all: norm libft $(S_NAME) $(C_NAME)

$(S_NAME): $(S_OBJ) | libft
	@$(CC) $(FLAGS) $(S_OBJ) ./libft/libft.a -o $(S_NAME)
	@echo "$(GREEN)[✓] $(RESET)$(CYAN)$(S_NAME) created$(RESET)"

$(C_NAME): $(C_OBJ) | libft
	@$(CC) $(FLAGS) $(C_OBJ) ./libft/libft.a -o $(C_NAME)
	@echo "$(GREEN)[✓] $(RESET)$(CYAN)$(C_NAME) created$(RESET)"

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@ $(INCLUDES)

bonus: norm libft $(S_NAME_BONUS) $(C_NAME_BONUS) 
	@echo "$(CYAN)\nBONUS MODE ACTIVATED$(RESET)"
	
$(S_NAME_BONUS): $(S_OBJ_BONUS)
	@$(CC) $(FLAGS) $(S_OBJ_BONUS) ./libft/libft.a -o $(S_NAME_BONUS)
	@echo "$(GREEN)[✓] $(RESET)$(CYAN)$(S_NAME_BONUS) created$(RESET)"

$(C_NAME_BONUS): $(C_OBJ_BONUS)
	@$(CC) $(FLAGS) $(C_OBJ_BONUS) ./libft/libft.a -o $(C_NAME_BONUS)
	@echo "$(GREEN)[✓] $(RESET)$(CYAN)$(C_NAME_BONUS) created$(RESET)"

libft:
	@make -C ./libft
	@echo "$(GREEN)[✓] $(RESET)$(CYAN)libft created$(RESET)"

clean:
	@rm -f $(S_OBJ) $(C_OBJ) $(S_OBJ_BONUS) $(C_OBJ_BONUS)
	@make clean -C ./libft

fclean: clean
	@rm -f $(S_NAME) $(C_NAME) $(S_NAME_BONUS) $(C_NAME_BONUS)
	@make fclean -C ./libft
	@echo "$(CYAN)$(S_NAME) && $(C_NAME) removed.$(RESET)"

re: fclean all

norm:
	@norminette -R CheckForbiddenSource
	@echo "$(CYAN)NORMINETTE OK $(RESET)"

.PHONY: all clean fclean re libft bonus 