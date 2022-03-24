/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:06:42 by tbouma            #+#    #+#             */
/*   Updated: 2022/03/24 13:02:42 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_func(t_pipex pipex, char **envp)
{
	int		status;

	pipe(pipex.tube);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		return (perror("Fork: error pid1 "));
	if (pipex.pid1 == 0)
		child_one(pipex, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		return (perror("Fork: error pid2"));
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
	char	**argv_exe[2];

	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.infile < 0 || pipex.outfile < 0)
		return (-1);
	pipex.argv_exe[0] = ft_split(argv[2], ' ');
	pipex.argv_exe[1] = ft_split(argv[3], ' ');
	pipex_func(pipex, envp);
	free(argv_exe[0]);
	//free(pipex.cmd);
	return (0);
}

// gcc pipex.c libpipex.a && ./a.out text.txt "wc -l" "cat" text2.txt
