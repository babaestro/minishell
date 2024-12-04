/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:59:41 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/11/27 16:08:56 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

void	exit_biltin2(t_command *cmd, t_shell *shell)
{
	if (cmd->args[1] && !ft_isnumber(cmd->args[1]))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		if (cmd->args[1])
			ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(2);
	}
	else
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		shell->last_status = EXIT_FAILURE;
	}
}

void	exit_builtin(int nr_args, t_command *command, t_shell *shell)
{
	write(1, "exit\n", 6);
	if (nr_args == 1)
		exit(0);
	else if (nr_args == 2)
	{
		if (command->args[1] && ft_isnumber(command->args[1]))
			exit(ft_atoi(command->args[1]));
		else
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(command->args[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			exit(2);
		}
	}
	else if (nr_args > 2)
		exit_biltin2(command, shell);
}
