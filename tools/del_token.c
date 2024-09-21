#include "../include/minishell.h"

void	del_token(t_token *to_del, t_token **list)
{
	t_token *list_cpy;

	list_cpy = *list;
	while (list_cpy->next && (list_cpy->next != to_del))
		list_cpy = list_cpy->next;
	if (!list_cpy->next)
		return ;
	list_cpy->next = to_del->next;
	to_del->next = NULL;
	free(to_del->str);
	free(to_del);
}