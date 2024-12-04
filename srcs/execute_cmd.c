/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:01:32 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/03 16:57:54 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

static void	external_error1(void)
{
	ft_printf("error executing: %d\n", errno);
	exit(126);
}

static void	external_error2(t_command *cmd)
{
	ft_putstr_fd(cmd->args[0], 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

void	update_status(int status, t_shell *shell)
{
	if (WIFEXITED(status))
		shell->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_status = 128 + WTERMSIG(status);
	else
		shell->last_status = 1;
}

void	exec_external(t_command *cmd, t_shell *shell)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_printf("fork");
		return ;
	}
	signals_command();
	if (pid == 0)
	{
		if (cmd->cmd_path && ft_strlen(cmd->cmd) != 0)
		{
			execve(cmd->cmd_path, cmd->args, shell->env);
			external_error1();
		}
		else
			external_error2(cmd);
	}
	else
	{
		waitpid(pid, &status, 0);
		update_status(status, shell);
	}
}

int	exec_builtin(t_command *command, t_shell *shell, t_token *token)
{
	{
		if (ft_strncmp(command->cmd, "pwd", 3) == 0 && 
			ft_strlen(command->cmd) == 3)
			return (pwd_builtin(shell), 1);
		else if (ft_strncmp(command->cmd, "cd", 2) == 0 && 
			ft_strlen(command->cmd) == 2)
			return (cd_builtin(command->arg_count, command, shell), 1);
		else if (ft_strncmp(command->cmd, "echo", 4) == 0 && 
			ft_strlen(command->cmd) == 4)
			return (echo_builtin(&command->args[1], token, shell), 1);
		else if (ft_strncmp(command->cmd, "unset", 5) == 0 && 
			ft_strlen(command->cmd) == 5)
			return (unset_builtin(shell, &command->args[1]), 1);
		else if (ft_strncmp(command->cmd, "export", 6) == 0 && 
			ft_strlen(command->cmd) == 6)
			return (export_builtin(&command->args[1], shell), 1);
		else if (ft_strncmp(command->cmd, "env", 3) == 0 && 
			ft_strlen(command->cmd) == 3)
			return (env_builtin(command->arg_count, shell, command), 1);
		else if (ft_strncmp(command->cmd, "exit", 4) == 0 && 
			ft_strlen(command->cmd) == 4)
			return (exit_builtin(command->arg_count, command, shell), 1);
		else 
			return (0);
	}
}
