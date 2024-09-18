#ifndef	MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "messages.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_token
{
	char			*type;
	char			*str;
	
	int				infile;
	int				outfile;
	int				cmd;

	struct s_token	*next;
}	t_token;

typedef struct s_minishell
{
	struct s_token	**tokens;
	char			**env;
	int				size_of_env;

	int				exit;
	int				exit_status;
	int				error;

	char			*user_input;

	int				pipes;
}	t_minishell;

// ENV FUNCTIONS //

extern char	**mini_env;

void	set_env_value(char *str, char *value, t_minishell *minishell);
char	*get_env_value(char *str, t_minishell *minishell);
void	get_list_of_env(char **environ, t_minishell *minishell);
void	sum_one_to_shlvl(t_minishell *minishell);

// INPUT FUNCTIONS //

char	*init_input(t_minishell *minishell);

// PARSING FUNCTIONS //

void	input_to_tokens(t_minishell *minishell);

int		redirection_token(t_minishell *minishell, int i);
int		pipe_token(t_minishell *minishell, int i);
int		quote_token(t_minishell *minishell, int i);
int		text_token(t_minishell *minishell, int i);

int		parse_tokens(t_minishell *minishell);

void	parse_redir_input(t_minishell *minishell, t_token *list);
void	parse_redir_output(t_minishell *minishell, t_token *list);
void	parse_redir_append(t_minishell *minishell, t_token *list);
void	parse_redir_heredoc(t_minishell *minishell, t_token *list);
void	parse_pipe(t_minishell *minishell, t_token *list);
void	parse_text(t_token *list);
void	parse_quotes(t_token *list);

// TOOLS FUNCTIONS //

int		double_str_len(char **double_array);
void	ft_free_double_array(char **double_array);

t_token	**ft_create_double_list(void);
t_token	*ft_lstnew_token(char *type, char *str);
void	ft_lstadd_token_back(t_token **token_list, t_token *new);
char	*get_first_word(t_token *list);

// FREE FUNCTIONS //

void	ft_exit(char *str, t_minishell *minishell);
void	free_all(t_minishell *minishell);

// TEST FUNCTIONS //

void	env_test(t_minishell *minishell);

#endif