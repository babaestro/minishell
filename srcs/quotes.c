/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:43:15 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/03 17:37:50 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

char	*join(char *l_limit, char *str, char *buff)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (l_limit[i] != '\0')
	{
		str[i] = l_limit[i];
		i++;
	}
	while (buff[j] != '\0')
	{
		str[i++] = buff[j++];
	}
	str[i] = '\0';
	safe_free(l_limit);
	return (str);
}

char	*ft_strjoin2(char *l_limit, char *buff)
{
	char	*str;

	if (!l_limit)
	{
		l_limit = (char *)safe_malloc(1 * sizeof(char));
		if (!l_limit)
			return (NULL);
		l_limit[0] = '\0';
	}
	if (!l_limit || !buff)
		return (NULL);
	str = safe_malloc(sizeof(char) * 
			((ft_strlen(l_limit) + ft_strlen(buff)) + 1));
	join(l_limit, str, buff);
	return (str);
}

char	*process_quote(char **current, char quote)
{
	const char	*start;
	char		*temp;

	start = *current + 1;
	(*current)++;
	while (**current != quote && **current != '\0')
		(*current)++;
	if (**current == quote)
	{
		temp = ft_strndup(start, ((size_t)(*current - start)));
		(*current)++;
		return (temp);
	}
	return (NULL);
}

static char	*process_word_part(char **current)
{
	char	*temp;
	char	*start;

	if (**current == '\'' || **current == '"')
		temp = process_quote(current, **current);
	else
	{
		start = *current;
		while (**current != '\0' && **current != ' ' && 
			**current != '\t' && !ft_strchr("><|&\"'", **current))
			(*current)++;
		temp = ft_strndup(start, (size_t)(*current - start));
	}
	return (temp);
}

void	handle_quotations(char **current, t_token *new_token)
{
	char	*combined_value;
	char	*temp;
	char	*new_combined;

	combined_value = safe_strdup("");
	if (!combined_value)
		return ;
	while (**current != '\0' && **current != ' ' && 
		**current != '\t' && !ft_strchr("><|&", **current))
	{
		temp = process_word_part(current);
		if (!temp)
			return (free(combined_value));
		new_combined = ft_strjoin2(combined_value, temp);
		if (!new_combined)
			return (free(combined_value));
		safe_free(combined_value);
		combined_value = new_combined;
	}
	new_token->value = combined_value;
	new_token->type = 0;
}
