/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:13:17 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/11/26 15:10:47 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static size_t	ft_words(const char *s, char c)
// {
// 	size_t	i;
// 	size_t	words;

// 	i = 0;
// 	words = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
// 			words++;
// 		i++;
// 	}
// 	return (words);
// }

// static int	ft_allocation(char **splits, const char *s, char c, int words)
// {
// 	int	start;
// 	int	end;

// 	start = 0;
// 	end = 0;
// 	while (s[end])
// 	{
// 		if (s[end] == c || s[end] == 0)
// 			start = end + 1;
// 		if (s[end] != c && (s[end +1] == c || s[end + 1] == 0))
// 		{
// 			splits[words] = malloc(sizeof(char) * (end - start + 2));
// 			if (!splits[words])
// 			{
// 				while (words--)
// 					free(splits[words]);
// 				return (0);
// 			}
// 			ft_strlcpy(splits[words], &s[start], (end - start + 2));
// 			words++;
// 		}
// 		end++;
// 	}
// 	splits[words] = 0;
// 	return (1);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**strings;

// 	if (!s)
// 		return (NULL);
// 	strings = malloc(sizeof(char *) * (ft_words(s, c) + 1));
// 	if (!strings)
// 		return (NULL);
// 	if (!ft_allocation(strings, s, c, 0))
// 	{
// 		free(strings);
// 		return (NULL);
// 	}
// 	return (strings);
// }

#include <stdlib.h>
#include <stdbool.h>

static bool	is_in_quotes(const char *s, int index, char quote_type)
{
	int		i;
	bool	in_quotes;

	i = 0;
	in_quotes = false;
	while (i < index)
	{
		if (s[i] == quote_type)
			in_quotes = !in_quotes;
		i++;
	}
	return (in_quotes);
}

static size_t	ft_words(const char *s, char c)
{
	size_t	i;
	size_t	words;
	bool	in_word;

	i = 0;
	words = 0;
	in_word = false;
	while (s[i])
	{
		if (s[i] != c && !in_word && !is_in_quotes(s, i, '\'') && 
			!is_in_quotes(s, i, '"'))
		{
			in_word = true;
			words++;
		}
		else if (s[i] == c && in_word && !is_in_quotes(s, i, '\'') && 
			!is_in_quotes(s, i, '"'))
			in_word = false;
		i++;
	}
	return (words);
}

static int	ft_allocate_word(char **splits, const char *s, 
	int *positions, int *words)
{
	int	start;
	int	end;

	start = positions[0];
	end = positions[1];
	splits[*words] = malloc(sizeof(char) * (end - start + 1));
	if (!splits[*words])
	{
		while (*words > 0)
			free(splits[--(*words)]);
		return (0);
	}
	ft_strlcpy(splits[*words], &s[start], (end - start + 1));
	(*words)++;
	return (1);
}

static int	ft_allocation(char **splits, const char *s, char c)
{
	int	positions[2];
	int	words;

	positions[0] = 0;
	positions[1] = 0;
	words = 0;
	while (s[positions[1]])
	{
		if (s[positions[1]] != c || is_in_quotes(s, positions[1], '\'') || 
			is_in_quotes(s, positions[1], '"'))
		{
			positions[1]++;
			continue ;
		}
		if (positions[1] > positions[0] && 
			!ft_allocate_word(splits, s, positions, &words))
			return (0);
		positions[0] = positions[1] + 1;
		positions[1]++;
	}
	if (positions[1] > positions[0] && 
		!ft_allocate_word(splits, s, positions, &words))
		return (0);
	splits[words] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = ft_words(s, c);
	strings = malloc(sizeof(char *) * (word_count + 1));
	if (!strings)
		return (NULL);
	if (!ft_allocation(strings, s, c))
	{
		free(strings);
		return (NULL);
	}
	return (strings);
}
