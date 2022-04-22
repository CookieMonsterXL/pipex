/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:25:27 by tbouma            #+#    #+#             */
/*   Updated: 2022/04/22 12:58:08 by tbouma           ###   ########.fr       */
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
	if (execve(p->cmd_path, p->cmd, envp) < 0)
		error_msg(ERR_EXEC, 1);
}

void	fork_child(t_p *p, char **envp)
{
	p->child_n++;
	if (p->pid_child > 0)
		p->pid_child = fork();
	if (p->pid_child < 0)
		error_msg(ERR_FORK, 1);
	if (p->pid_child == 0)
		child(p, envp);
}
