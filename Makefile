NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
RM = rm -rf



DIR_ENV = env/
SRCS_ENV = env.c get_env.c
ENV = $(addprefix $(DIR_ENV), $(SRCS_ENV))


DIR_MINISHELL_INIT = minishell_init/
SRCS_MINISHELL_INIT = minishell.c init_input.c
MINISHELL_INIT = $(addprefix $(DIR_MINISHELL_INIT), $(SRCS_MINISHELL_INIT))


DIR_TOOLS = tools/
SRCS_TOOLS = double_str.c token_list.c
TOOLS = $(addprefix $(DIR_TOOLS), $(SRCS_TOOLS))


DIR_FREE = free/
SRCS_FREE = free.c exit.c
FREE = $(addprefix $(DIR_FREE), $(SRCS_FREE))


DIR_PARSING = parsing/
SRCS_PARSING = input_to_tokens.c token_types.c token_parsing.c parse_basic_redir.c parse_text.c
PARSING = $(addprefix $(DIR_PARSING), $(SRCS_PARSING))


SRCS = $(ENV) $(MINISHELL_INIT) $(TOOLS) $(FREE) $(PARSING)
OBJS = $(SRCS:.c=.o)


INCLUDE = -I include -I libft
LIBRARY = -L libft -lft -lreadline


%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Objects created"
	@make -C libft
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBRARY) -o $(NAME)
	@echo "$(NAME) created"


clean:
	@make clean -C libft
	@$(RM) $(OBJS)
	@echo "Objects removed"

fclean: clean
	@make fclean -C libft
	@$(RM) $(NAME)
	@echo "$(NAME) removed"

re: fclean all

run: all clean

.PHONY: all clean fclean re run 
