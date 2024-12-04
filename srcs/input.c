/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:39:38 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/12/03 17:15:22 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "memory.h"

void	handle_cases(char **current, t_token *new_token)
{
	if (**current == '"' || **current == '\'')
		handle_quotations(current, new_token);
	else if (ft_strchr("><|&", **current))
		handle_operators(current, new_token);
	else
		handle_words(current, new_token);
}

// void	handle_words(char **current, t_token *new_token)
// {
// 	char	*start;
// 	char	*word;
// 	char	*quoted_part;
// 	char	*combined;
// 	t_token	temp_token;

// 	start = *current;
// 	while ((**current != ' ' && **current != '\t') && 
// 		!ft_strchr("><|&\"'", **current) && **current != '\0')
// 		(*current)++; 
// 	word = ft_strndup(start, ((size_t)(*current - start)));
// 	if (**current == '"' || **current == '\'')
// 	{
// 		handle_quotations(current, &temp_token);
// 		quoted_part = temp_token.value;
// 		combined = ft_strjoin2(word, quoted_part);
// 		new_token->value = combined;
// 	}
// 	else
// 		new_token->value = word;
// 	new_token->type = 0;
// }

void	handle_words(char **current, t_token *new_token)
{
	char	*start;
	char	*word;
	char	*quoted_part;
	char	*combined;
	t_token	temp_token;

	start = *current;
	while ((**current != ' ' && **current != '\t') && 
		!ft_strchr("><|&\"'", **current) && **current != '\0')
		(*current)++;
	word = ft_strndup(start, ((size_t)(*current - start)));
	if (**current == '"' || **current == '\'')
	{
		handle_quotations(current, &temp_token);
		quoted_part = temp_token.value;
		combined = ft_strjoin2(word, quoted_part);
		new_token->value = combined;
	}
	else
		new_token->value = word;
	new_token->type = 0;
}

void	check_operators(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current != NULL)
	{
		if (ft_strncmp(current->value, "|", 1) == 0 && 
			current->type != 8)
			current->type = TOKEN_PIPE;
		else if (ft_strncmp(current->value, "<<", 2) == 0 && 
			current->type != 8)
			current->type = TOKEN_HERE_DOC;
		else if (ft_strncmp(current->value, "<", 1) == 0 && 
			current->type != 8)
			current->type = TOKEN_REDIRECT_IN;
		else if (ft_strncmp(current->value, ">>", 2) == 0 && 
			current->type != 8)
			current->type = TOKEN_REDIRECT_APPEND;
		else if (ft_strncmp(current->value, ">", 1) == 0 && 
			current->type != 8)
			current->type = TOKEN_REDIRECT_OUT;
		current = current->next;
	}
}

void	handle_operators(char **current, t_token *new_token)
{
	char	*start;
	size_t	len;

	start = *current;
	len = 1;
	if ((**current == '>' && *(*current + 1) == '>') || (**current == '<' && \
	*(*current + 1) == '<') || (**current == '&' && *(*current + 1) == '&') \
	|| (**current == '|' && *(*current + 1) == '|'))
		len = 2;
	new_token->value = ft_strndup(start, len);
	*current += len;
}
