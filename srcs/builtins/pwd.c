/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:53:07 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/11/27 16:10:10 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

void	pwd_builtin(t_shell *shell)
{
	char	*path;

	if (shell->path == 1)
	{
		shell->last_status = EXIT_FAILURE;
		return ;
	}
	path = get_env_value("PWD", shell->env);
	if (path)
		printf("%s\n", path);
	else
	{
		shell->last_status = EXIT_FAILURE;
		return (perror("pwd"));
	}
	shell->last_status = EXIT_SUCCESS;
}
