/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:03:51 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/11/21 18:22:22 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

t_token	*allocate_token(void)
{
	t_token	*new_token;

	new_token = safe_malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = NULL;
	new_token->type = 0;
	new_token->next = NULL;
	return (new_token);
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		safe_free (temp->value);
		safe_free (temp);
	}
}
