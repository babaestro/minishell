/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:32:23 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/11/22 13:43:37 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <stddef.h>
# include "minishell.h"

typedef struct MemoryNode
{
	void				*ptr;
	struct MemoryNode	*next;
}	t_MemoryNode;

void		track_allocation(void *ptr);
void		*safe_malloc(size_t size);
void		free_all_memory(void);
char		*safe_strdup(const char *s);
void		cleanup_command(t_command *cmd);
void		safe_free(void *ptr);
void		free_delimiters(t_shell *shell);
void		free_command(t_command *cmd);
void		free_shell(t_shell *shell);

#endif