NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRCS = pipex.c utils.c\

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	$(CC) -I. -I$(LIBFTDIR) $(SRCS) $(LIBFT) $(CFLAGS) -o $(NAME)
	@echo "Compiled $(NAME) successfully!"

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re