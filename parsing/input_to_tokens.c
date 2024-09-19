#include "../include/minishell.h"

int	ft_create_token(t_minishell *minishell, int type, int index, int init_of_str)
{
	char	*str;
	t_token	*new_node;
	int		i;
	int		j;

	j = 0;
	i = init_of_str;
	if (!(minishell->tokens))
		minishell->tokens = ft_create_double_list();
	str = (char *)malloc(sizeof(char) * (index - init_of_str + 1));
	if (!str)
		return (-1); 
	while (i < index)
	{
		str[j] = minishell->user_input[i];
		j++;
		i++;
	}
	str[j] = '\0';
	new_node = ft_lstnew_token(type, str);
	ft_lstadd_token_back(minishell->tokens, new_node);
	return (index);
}

void	input_to_tokens(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->user_input[i])
	{
		while ((minishell->user_input[i] == ' ' || minishell->user_input[i] == '\t'
			|| minishell->user_input[i] == '\n') && minishell->user_input[i])
			i++;
		if (minishell->user_input[i] == '\0')
			return ;
		if (minishell->user_input[i] == '<' || minishell->user_input[i] == '>')
			i = redirection_token(minishell, i);
		else if (minishell->user_input[i] == '|')
			i = pipe_token(minishell, i);
		else if (minishell->user_input[i] == '\'' || minishell->user_input[i] == '"')
			i = quote_token(minishell, i);
		else
			i = text_token(minishell, i);
	}
	if (parse_tokens(minishell))
		ft_exit(PARSE_ERR, minishell);
}