/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:12:13 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/12/02 17:18:04 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "memory.h"

int	check_syntax_errors(char **before_pipe, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (before_pipe[i] != NULL)
	{
		j = 0;
		while (before_pipe[i][j] != '\0')
		{
			if (before_pipe[i][j] == '<' || before_pipe[i][j] == '>')
			{
				if (check_redirection_syntax(before_pipe[i], &j) != 0)
				{
					printf("minishell: syntax error \n");
					shell->last_status = 2;
					return (1);
				}
			}
			else
				j++;
		}
		i++;
	}
	return (0);
}

void	free_string_array(char **arr)
{
	int	j;

	j = 0;
	while (arr[j] != NULL)
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}

int	cleanup_and_return(char **before_pipe, t_shell *shell)
{
	if (before_pipe)
		free_string_array(before_pipe);
	if (shell->delimiters)
		free_delimiters(shell);
	return (shell->last_status);
}

int	handle_empty_input(char **before_pipe, t_shell *shell)
{
	if (before_pipe)
		free_string_array(before_pipe);
	if (shell->delimiters)
		free_delimiters(shell);
	return (shell->last_status);
}

int	handle_input(char *input, t_shell *shell)
{
	char	**before_pipe;

	shell->full_input = input;
	shell->pipe_count = 0;
	before_pipe = ft_split(input, '|');
	if (input == NULL || *input == '\0')
		return (handle_empty_input(before_pipe, shell));
	if (check_syntax_errors(before_pipe, shell) != 0)
		return (cleanup_and_return(before_pipe, shell));
	count_pipes(before_pipe, shell);
	if (before_pipe[0])
		execute_pipeline(before_pipe, shell);
	return (cleanup_and_return(before_pipe, shell));
}
