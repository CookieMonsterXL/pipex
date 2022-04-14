/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:06:42 by tbouma            #+#    #+#             */
/*   Updated: 2022/04/14 12:29:14 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	parent_procces(t_pipex pipex, char **envp)
{
	int		status;

	pipe(pipex.tube);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		error_msg(ERR_FORK);
	if (pipex.pid1 == 0)
		child_one(pipex, envp);
	else
		child_two(pipex, envp);
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	waitpid(pipex.pid1, &status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		error_msg(ERR_INPUT);
	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.infile < 0 || pipex.outfile < 0)
		error_msg(ERR_FILE);
	pipex.command[0] = ft_split(argv[2], ' ');
	if (pipex.command[0] == NULL)
		error_msg(ERR_MALLOC);
	pipex.command[1] = ft_split(argv[3], ' ');
	if (pipex.command[1] == NULL)
		error_msg(ERR_MALLOC);
	parent_procces(pipex, envp);
	parent_free(&pipex);
	return (0);
}

// ./pipex text.txt "grep k" "cat" text2.txt