/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:17:47 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/12/02 17:30:07 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "memory.h"

int	is_inside_quotes(const char *str, const char *substr)
{
	int	in_single_quotes;
	int	in_double_quotes;

	in_single_quotes = 0;
	in_double_quotes = 0;
	while (*str)
	{
		if (*str == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (*str == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (str == substr && !in_single_quotes && !in_double_quotes)
			return (0);
		str++;
	}
	return (1);
}

void	close_stdin(int prev_fd)
{
	if (prev_fd >= 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
}

void	close_stdout(int pipe_fd_1, int pipe_fd_0)
{
	if (pipe_fd_1 >= 0)
	{
		dup2(pipe_fd_1, STDOUT_FILENO);
		close(pipe_fd_1);
	}
	if (pipe_fd_0 >= 0)
		close(pipe_fd_0);
}

void	wait_status(int status, t_shell *shell)
{
	if (WIFEXITED(status))
		shell->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_status = 128 + WTERMSIG(status);
}

void	wait_for_children(t_shell *shell)
{
	int	status;

	while (wait(&status) > 0)
		wait_status(status, shell);
	unlink("temporary.tmp");
}
