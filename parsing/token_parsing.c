#include "../include/minishell.h"

void	no_spaces_before_or_after_tokens(t_token **tokens)
{
	t_token	*list;
	char	*str_cpy;

	list = *tokens;
	while (list)
	{
		str_cpy = list->str;
		list->str = ft_strtrim(str_cpy, " \t\n");
		free(str_cpy);
		list = list->next;
	}
}

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
		else if (list->type == REDIR_APPEND)
			parse_redir_append(minishell, list);
		else if (list->type == REDIR_HEREDOC)
			parse_redir_heredoc(minishell, list);
		else if (list->type == PIPE)
			parse_pipe(minishell, list);
		else if (list->type == TEXT)
			parse_text(list);
		else
			parse_quotes(list);
		list = list->next;
	}
	no_spaces_before_or_after_tokens(minishell->tokens);
	while (token_list)
	{
		printf("type: %d\ntoken: %s\nheredoc: %d, append: %d, infile: %d, outfile: %d, command: %d\n\n", token_list->type, token_list->str, token_list->heredoc, token_list->append, token_list->infile, token_list->outfile, token_list->cmd);
		token_list = token_list->next;
	}
	if (minishell->error)
		return (1);
	return (0);
}