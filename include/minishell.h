#ifndef	MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "messages.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>

typedef struct s_token
{
	int				type;
	char			*str;
	
	int				infile;
	int				outfile;
	int				heredoc;
	int				append;
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

	int				infile;
	int				outfile;
	int				pipe_fd[2];
	pid_t			*pid;
}	t_minishell;



// DIRECTORIES_PIPES FUNCTIONS //

int		get_infile(t_minishell *minishell, int infile_fd, int pipe_index);
int		get_outfile(t_minishell *minishell, int outfile_fd, int pipe_index);
int		get_pipe_outfile(t_minishell *minishell);

// ENV FUNCTIONS //

char	*get_line_before_env(char *line, int len);
char	*get_env(char *line, int stay, int i, t_minishell *minishell);
char	*get_line_after_env(char *line, int i);
char	*get_line_after_env_change(char **substring, char *line, int i, int j);
void	ft_free_env_line_array(char **substring);

void	set_env_value(char *str, char *value, t_minishell *minishell);
char	*get_env_value(char *str, t_minishell *minishell);
void	get_list_of_env(char **environ, t_minishell *minishell);
void	sum_one_to_shlvl(t_minishell *minishell);

// BUILTIN FUNCTIONS //

void	builtin_execute(t_minishell *minishell, char **cmd_argv);
void	echo_builtin(int argc, char **argv);
void	pwd_builtin(int argc, char **argv);
void	cd_builtin(int argc, char **argv);
void	export_builtin(int argc, char **argv);
void	unset_builtin(int argc, char **argv);
void	exit_builtin(int argc, char **argv);
void	env_builtin(int argc, char **argv);


// EXECUTE FUNCTIONS //

void	init_execution(t_minishell *minishell);
void	ft_execute_command(t_minishell *minishell, int i, int total_pipes);

// INPUT FUNCTIONS //

char	*init_input(t_minishell *minishell);

// PARSING FUNCTIONS //

void	input_to_tokens(t_minishell *minishell);
int		ft_create_token(t_minishell *minishell, int type, int index, int init_of_str);

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
t_token	*ft_lstnew_token(int type, char *str);
void	ft_lstadd_token_back(t_token **token_list, t_token *new);
char	*get_first_word(t_token *list);
char	*get_after_first_word(t_token *list, char *first_word);

void	del_token(t_token *to_del, t_token **list);

// FREE FUNCTIONS //

void	ft_exit(char *str, t_minishell *minishell);
void	free_all(t_minishell *minishell);


#endif