NAME = minishell

SRCDIR = src
LIBFTDIR = libft

SRC = $(SRCDIR)/init_hashmap.c \
      $(SRCDIR)/init_hashmap2.c \
      $(SRCDIR)/init_hashmap3.c \
	  $(SRCDIR)/init_hashmap4.c\
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
	  $(SRCDIR)/builtin.c\
	  $(SRCDIR)/builtin1.c\
	  $(SRCDIR)/cd_shell.c\
	  $(SRCDIR)/delete_in_hashmap.c\
	  $(SRCDIR)/env_shell.c\
	  $(SRCDIR)/env_shell2.c\
	  $(SRCDIR)/env_shell3.c\
	  $(SRCDIR)/execute_commands.c\
	  $(SRCDIR)/execute_commands2.c\
	  $(SRCDIR)/export_shell.c\
	  $(SRCDIR)/export_shell2.c\
	  $(SRCDIR)/ft_expand.c\
	  $(SRCDIR)/ft_expand2.c\
	  $(SRCDIR)/ft_node.c\
	  $(SRCDIR)/ft_node2.c\
	  $(SRCDIR)/ft_print_error.c\
	  $(SRCDIR)/ft_update_list.c\
	  $(SRCDIR)/ft_update_list2.c\
	  $(SRCDIR)/heredoc.c\
	  $(SRCDIR)/manage_exit.c\
	  $(SRCDIR)/manage_signals.c\
	  $(SRCDIR)/print_table.c\
	  $(SRCDIR)/unset.c\



	
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
