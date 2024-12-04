/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:21:45 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/12/02 17:30:01 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "memory.h"

void	child_process(t_process_info *info)
{
	if (info->prev_fd != -1)
		close_stdin(info->prev_fd);
	if (info->command[0] != '\0')
		close_stdout(info->pipe_fd[1], info->pipe_fd[0]);
	handle_single_command(info->command, info->shell);
	exit(info->shell->last_status);
}

int	parent_process(char **commands, int i, int *prev_fd, int pipe_fd[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (commands[i + 1] != NULL)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	return (0);
}

int	setup_pipe(char **commands, int i, int pipe_fd[2], t_shell *shell)
{
	pid_t	pid;

	if (commands[i + 1] != NULL && pipe(pipe_fd) == -1)
	{
		shell->last_status = 1;
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		shell->last_status = 1;
		return (-1);
	}
	return (pid);
}

void	execute_pipeline(char **commands, t_shell *shell)
{
	int	prev_fd;
	int	i;

	prev_fd = -1;
	i = 0;
	if (shell->pipe_count == 0)
		return (handle_no_pipe(commands, shell));
	while (commands[i])
	{
		process_command(commands, &i, &prev_fd, shell);
		if (prev_fd < 0)
			return ;
	}
	wait_for_children(shell);
}

void	count_pipes(char **before_pipe, t_shell *shell)
{
	int	i;

	i = 0;
	while (before_pipe[i + 1] != NULL)
		i++;
	shell->pipe_count = i;
}
