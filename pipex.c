/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:06:42 by tbouma            #+#    #+#             */
/*   Updated: 2022/03/24 17:49:09 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_procces(t_pipex pipex, char **envp)
{
	int		status;

	pipe(pipex.tube);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		return (perror(ERR_PIPE));
	if (pipex.pid1 == 0)
		child_one(pipex, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		return (perror(ERR_PIPE));
	if (pipex.pid2 == 0)
		child_two(pipex, envp);
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	waitpid(pipex.pid1, &status, 0);
	waitpid(pipex.pid2, &status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	argc = 0;
	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.infile < 0 || pipex.outfile < 0)
	{
		exit(1);
		return (-1);
	}
	pipex.command[0] = ft_split(argv[2], ' ');
	pipex.command[1] = ft_split(argv[3], ' ');
	parent_procces(pipex, envp);
	parent_free(&pipex);
	return (0);
}


	// system("leaks pipex");
// gcc pipex.c libpipex.a && ./a.out text.txt "wc -l" "cat" text2.txt
