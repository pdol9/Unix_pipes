# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 22:12:33 by pdolinar          #+#    #+#              #
#    Updated: 2022/05/03 16:45:47 by pdolinar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
BONUS		=	pipex_bonus
HEADER		=	-I ./include/

CC			=	gcc
RM			=	rm -rf
CFLAGS		=	-Wall -Wextra -Werror -g

REV = \033[0m
PR = \033[1;35m
GR = \033[1;32m

SRCDIR		=	src/
OBJDIR		=	build/
OBJDIR_B	=	build_bonus/

SRC			=	pipex.c utils_pipex.c split.c utils.c utils2.c
SRC_BONUS	=	pipex_bonus.c utils.c utils1_bonus.c utils2_bonus.c \
				split.c get_next_line.c get_next_line_utils.c

PRESRC		=	$(addprefix $(SRCDIR), $(SRC))
OBJ			=	$(SRC:%.c=%.o)
PREOBJ		=	$(addprefix $(OBJDIR), $(OBJ))

PRESRC_B	=	$(addprefix $(SRCDIR), $(SRC_BONUS))
OBJ_B		=	$(SRC_BONUS:%.c=%.o)
PREOBJ_B	=	$(addprefix $(OBJDIR_B), $(OBJ_B))

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADER)

$(NAME): $(PREOBJ)
	@$(CC) $(CFLAGS) $(PREOBJ) $(HEADER) -o $@
	@echo												"$(GR)\n\
      ___                     ___         ___           ___     \n\
     /  /\      ___          /  /\       /  /\         /__/|    \n\
    /  /::\    /  /\        /  /::\     /  /:/_       |  |:|    \n\
   /  /:/\:\  /  /:/       /  /:/\:\   /  /:/ /\      |  |:|    \n\
  /  /:/~/:/ /__/::\      /  /:/~/:/  /  /:/ /:/_   __|__|:|    \n\
 /__/:/ /:/  \__\/\:\__  /__/:/ /:/  /__/:/ /:/ /\ /__/::::\____\n\
 \  \:\/:/      \  \:\/\ \  \:\/:/   \  \:\/:/ /:/    ~\~~\::::/\n\
  \  \::/        \__\::/  \  \::/     \  \::/ /:/      |~~|:|~~ \n\
   \  \:\        /__/:/    \  \:\      \  \:\/:/       |  |:|   \n\
    \  \:\       \__\/      \  \:\      \  \::/        |  |:|   \n\
     \__\/                   \__\/       \__\/         |__|/    \n\
	 															\n\
			SUCCESSFULLY	COMPILED !							\n\
															$(REV)"

clean:
	@$(RM) $(OBJDIR)
	@echo "$(PR)All object files deleted$(REV)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(PR)All compiled files deleted$(REV)"

re:	fclean all

bonus: $(BONUS)

$(OBJDIR_B)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR_B)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADER)

$(BONUS): $(PREOBJ_B)
	@$(CC) $(CFLAGS) $(PREOBJ_B) $(HEADER) -o $@
	@echo																			"$(GR)\n\
  _____  _____  _____  _______ _     _       |      ______   _____  __   _ _     _ _______\n\
 |_____]   |   |_____] |______  \___/        |      |_____] |     | | \  | |     | |______\n\
 |       __|__ |       |______ _/   \_       |      |_____] |_____| |  \_| |_____| ______|\n\
                                             |                                            \n\
																						$(REV)"

bonus_clean:
	@$(RM) $(OBJDIR_B)
	@echo "$(PR)BONUS part: All object files deleted$(REV)"

bonus_fclean: bonus_clean
	@$(RM) $(BONUS)
	@echo "$(PR)BONUS part: All compiled files deleted$(REV)"

re_bonus: bonus_fclean bonus

norm: norminette $(SRCDIR) $(HEADER)

.PHONY: all clean fclean re norm bonus bonus_clean bonus_fclean re_bonus
