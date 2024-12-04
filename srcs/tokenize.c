/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:39:40 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/11/29 16:23:02 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

void	add_token_to_list(t_token **tokens, t_token **current_token, 
	t_token *new_token)
{
	if (!*tokens)
		*tokens = new_token;
	else
		(*current_token)->next = new_token;
	*current_token = new_token;
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	t_token	*current_token;
	t_token	*new_token;
	char	*current;

	current_token = NULL;
	tokens = NULL;
	current = input;
	while (*current != '\0')
	{
		while (*current == ' ' || *current == '\t')
			current++;
		if (*current == '\0')
			break ;
		new_token = allocate_token();
		handle_cases(&current, new_token);
		add_token_to_list(&tokens, &current_token, new_token);
	}
	return (tokens);
}
