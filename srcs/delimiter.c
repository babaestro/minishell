/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:05:05 by anschmit          #+#    #+#             */
/*   Updated: 2024/11/27 14:49:40 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	max_delimiter(char *input, t_shell *shell)
{
	int	i;
	int	max_delimiters;

	i = 0;
	max_delimiters = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '<' && input[i + 1] == '<')
			max_delimiters++;
		i++;
	}
	if (max_delimiters == 0)
		return ;
	shell->delimiters = malloc (sizeof (char *) * max_delimiters);
	if (!shell->delimiters)
	{
		printf("Error: Memory allocation failed for delimiters array\n");
		return ;
	}
}

void	get_length(t_shell *shell, char *input, int i, int start)
{
	int	l;

	l = i - start + 1;
	if (l > 0)
	{
		shell->delimiters[shell->num_delimiters] = malloc(l + 1);
		if (!shell->delimiters[shell->num_delimiters])
		{
			printf("Error: Malloc failed");
			free_delimiters(shell);
			return ;
		}
		ft_strlcpy(shell->delimiters[shell->num_delimiters], &input[start], l);
		shell->delimiters[shell->num_delimiters][l] = '\0';
		shell->num_delimiters++;
	}
}

void	get_delimiter(char *input, t_shell *shell)
{
	int	i;
	int	start;

	shell->num_delimiters = 0;
	i = 0;
	start = 0;
	max_delimiter(input, shell);
	while (input[i] != '\0')
	{
		if (input[i] == '<' && input[i + 1] == '<')
		{
			i += 2;
			while (ft_isalnum(input[i]) == 0 && input[i] != '\0')
				i++;
			start = i;
			while (input[i] != '\0' && ft_isalnum(input[i]) == 1 && 
				input[i] != '<')
				i++;
			get_length(shell, input, i, start);
		}
		else
			i++;
	}
}
