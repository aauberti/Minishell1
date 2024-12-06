NAME = minishell

SRCDIR = src
LIBFTDIR = libft

SRC = $(SRCDIR)/init_hashmap.c \
      $(SRCDIR)/init_hashmap2.c \
      $(SRCDIR)/init_hashmap3.c \
      $(SRCDIR)/main.c \
      $(SRCDIR)/print_table.c \
	  $(SRCDIR)/prompt.c \
	  $(SRCDIR)/prompt_utils.c \
	  $(SRCDIR)/execution.c \
	  $(SRCDIR)/init_shell.c \
	  $(SRCDIR)/input_manager.c \
	  $(SRCDIR)/ft_split_str.c \
	  $(SRCDIR)/ft_split_in_word.c \
	  $(SRCDIR)/ft_expand.c\
	  $(SRCDIR)/ft_expand2.c\
	  $(SRCDIR)/ft_list_update.c\
	
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I$(LIBFTDIR)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFTDIR) # Compile la libft (génère libft.a)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFTDIR)/libft.a -lreadline

$(SRCDIR)/%.o: $(SRCDIR)/%.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBFTDIR)
	rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIBFTDIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
