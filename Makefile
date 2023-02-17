NAME = pipex
FILES = pipex.c libft.c get_next_line_utils.c utils.c pipex_utils.c libft_utils.c
SRC_BONUS = pipex_bonus.c get_next_line.c get_next_line_utils.c libft.c utils.c pipex_bonus_heredoc_utils.c pipex_bonus_utils.c bonus_utils.c libft_utils.c
OBJ = $(FILES:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -I pipex.h

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
bonus: $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME)
%.o : %.c pipex.h
	$(CC) $(CFLAGS) -c $<
clean :
	rm -rf $(OBJ) $(OBJ_BONUS)
fclean : clean
	rm -rf $(NAME)
re: fclean all