/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:04:09 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/12/03 15:33:29 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

static int	check_no_newline(char **arg)
{
	int	i;
	int	j;

	i = 0;
	while (arg[i] && arg[i][0] == '-' && arg[i][1] == 'n')
	{
		j = 2;
		while (arg[i][j] == 'n')
			j++;
		if (arg[i][j] != '\0')
			return (i);
		i++;
	}
	return (i);
}

static void	print_arguments(char **arg, int start_index)
{
	int	first_arg;
	int	i;
	int	k;

	first_arg = 1;
	i = start_index;
	while (arg[i])
	{
		if (!first_arg)
			write(1, " ", 1);
		k = 0;
		while (arg[i][k])
		{
			write(1, &arg[i][k], 1);
			k++;
		}
		first_arg = 0;
		i++;
	}
}

void	echo_builtin(char **arg, t_token *token, t_shell *shell)
{
	int	no_newline_index;
	int	no_newline;

	no_newline_index = check_no_newline(arg);
	no_newline = (no_newline_index > 0);
	print_arguments(arg, no_newline_index);
	if (!no_newline && token->type != TOKEN_REDIRECT_APPEND)
		write(1, "\n", 1);
	shell->last_status = EXIT_SUCCESS;
}
