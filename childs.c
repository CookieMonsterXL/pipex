/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:25:27 by tbouma            #+#    #+#             */
/*   Updated: 2022/03/24 16:19:14 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_one(t_pipex pipex, char **envp)
{
	char	**root_paths;

	dup2(pipex.tube[1], STDOUT_FILENO);
	close(pipex.tube[0]);
	dup2(pipex.infile, 0);
	root_paths = find_path(envp);
	pipex.command_path = find_command_path(root_paths, pipex.command[0][0]);
	execve(pipex.command_path, pipex.command[0], envp);
}

void	child_two(t_pipex pipex, char **envp)
{
	char	**root_paths;

	dup2(pipex.tube[0], STDIN_FILENO);
	close(pipex.tube[1]);
	dup2(pipex.outfile, 1);
	root_paths = find_path(envp);
	pipex.command_path = find_command_path(root_paths, pipex.command[1][0]);
	execve(pipex.command_path, pipex.command[1], envp);
}