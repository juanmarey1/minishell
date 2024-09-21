#include "../include/minishell.h"

void	remove_redir_tokens(t_token **tokens)
{
	t_token *list;

	list = *tokens;
	while (list)
	{
		if (list->type == REDIR_APPEND || list->type == REDIR_HEREDOC
			|| list->type == REDIR_INPUT || list->type == REDIR_OUTPUT)
		{
			del_token(list, tokens);
			list = *tokens;
		}
		else
			list = list->next;
	}
}

int	check_all_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == ' '))
		i++;
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}

void	no_spaces_before_or_after_tokens(t_token **tokens)
{
	t_token	*list;
	char	*str_cpy;

	list = *tokens;
	while (list)
	{
		str_cpy = list->str;
		if (check_all_spaces(list->str))
		{
			del_token(list, tokens);
			list = *tokens;
		}
		else
		{
			list->str = ft_strtrim(str_cpy, " \t\n");
			free(str_cpy);
			list = list->next;
		}
	}
}

int	parse_tokens(t_minishell *minishell)
{
	t_token	*list;

	list = *minishell->tokens;
	// t_token *token_list;
	// token_list = *minishell->tokens;
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
	remove_redir_tokens(minishell->tokens);
	// while (token_list)
	// {
	// 	printf("type: %d\ntoken: %s\nheredoc: %d, append: %d, infile: %d, outfile: %d, command: %d\n\n", token_list->type, token_list->str, token_list->heredoc, token_list->append, token_list->infile, token_list->outfile, token_list->cmd);
	// 	token_list = token_list->next;
	// }
	if (minishell->error)
		return (1);
	return (0);
}