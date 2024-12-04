/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:59:10 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/11/27 16:09:42 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

void	env_builtin(int nr_args, t_shell *shell, t_command *cmd)
{
	int		i;

	i = 0;
	if (cmd->new_out == 0 || nr_args > 1)
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		shell->last_status = 127;
		return ;
	}
	else
	{
		while (shell->env[i] != NULL)
		{
			printf("%s\n", shell->env[i]);
			i++;
		}
	}
	shell->last_status = EXIT_SUCCESS;
}
