#include "../include/minishell.h"

int	parse_tokens(t_minishell *minishell)
{
	t_token	*list;

	list = *minishell->tokens;
	t_token *token_list;
	token_list = *minishell->tokens;
	while (list)
	{
		if (list->type == REDIR_INPUT)
			parse_redir_input(minishell, list);
		else if (list->type == REDIR_OUTPUT)
			parse_redir_output(minishell, list);
		// else if (list->type == REDIR_APPEND)
		// 	parse_redir_append(minishell, list);
		// else if (list->type == REDIR_HEREDOC)
		// 	parse_redir_heredoc(minishell, list);
		else if (list->type == PIPE)
			parse_pipe(minishell, list);
		else if (list->type == TEXT)
			parse_text(list);
		else
			parse_quotes(list);
		list = list->next;
	}
	while (token_list)
	{
		printf("type: %d\ntoken: %s\ninput: %d, output %d\n\n", token_list->type, token_list->str, token_list->infile, token_list->outfile);
		token_list = token_list->next;
	}
	if (minishell->error)
		return (1);
	return (0);
}