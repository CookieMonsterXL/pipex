/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:25:27 by tbouma            #+#    #+#             */
/*   Updated: 2022/04/21 15:16:55 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(t_p *p, char **envp)
{
	dup2(p->tube[1], STDOUT_FILENO);
	close(p->tube[0]);
	p->cmd = ft_split(p->argv[p->child_n + 1], ' ');
	if (p->cmd == NULL)
		error_msg(ERR_MALLOC, 1);
	p->cmd_path = find_cmd_path(p->root_paths, p->cmd[0]);
	execve(p->cmd_path, p->cmd, envp);
}
