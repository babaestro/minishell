/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:27:44 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/12/02 14:06:05 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_multiple_redirections(t_command *cmd)
{
	int				count;
	t_redirection	*current;

	count = 0;
	current = cmd->redirections;
	while (current)
	{
		count++;
		if (count > 1)
			return (1);
		current = current->next;
	}
	return (0);
}

int	multiple_in(t_redirection *current, int fd_in, t_shell *shell)
{
	if (fd_in != -1)
		close(fd_in);
	fd_in = open(current->filename, O_RDONLY);
	if (fd_in == -1)
	{
		shell->last_status = 1;
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(current->filename, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (-1);
	}
	return (fd_in);
}

int	multiple_out(t_redirection *current, int fd_out, t_shell *shell)
{
	(void)shell;
	if (fd_out != -1)
		close(fd_out);
	fd_out = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		return (-1);
	return (fd_out);
}

int	multiple_append(t_redirection *current, int fd_out, t_shell *shell)
{
	(void)shell;
	if (fd_out != -1)
		close(fd_out);
	fd_out = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
		return (-1);
	return (fd_out);
}

void	close_multiple(t_command *cmd, int fd_in, int fd_out)
{
	if (fd_in != -1)
	{
		cmd->old_in = dup(STDIN_FILENO);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != -1)
	{
		cmd->old_out = dup(STDOUT_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	return ;
}
