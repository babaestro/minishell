/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:23:57 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/12/02 14:17:53 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

char	*read_input(void)
{
	char	*rl;

	rl = readline(GREEN "minishell" RESET "> ");
	if (rl == NULL)
		return (NULL);
	if (*rl == '\0')
	{
		free (rl);
		return (ft_strdup(""));
	}
	if (rl && *rl)
		add_history(rl);
	return (rl);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_shell	*shell;
	int		status;

	(void)ac;
	(void)av;
	shell = initialize_shell(envp);
	if (!shell)
		return (1);
	while (1)
	{
		initialize_signals();
		input = read_input();
		if (!input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		handle_input(input, shell);
		free(input);
	}
	status = shell->last_status;
	free_shell(shell);
	rl_clear_history();
	return (status);
}
