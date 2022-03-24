/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:06:42 by tbouma            #+#    #+#             */
/*   Updated: 2022/03/24 09:23:42 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include "pipex.h"
#include "libft/libft.h"

char	*find_command(char **dubbleptr, char *command)
{
	char	*temp;
	int		i;

	i = 0;
	while (dubbleptr[i])
	{
		temp = ft_strjoin(dubbleptr[i], "/");
		free(dubbleptr[i]);
		dubbleptr[i] = temp;
		temp = ft_strjoin(dubbleptr[i], command);
		free(dubbleptr[i]);
		dubbleptr[i] = temp;
		if (access(dubbleptr[i], F_OK) == 0)
		{
			return (dubbleptr[i]);
			//printf("%s", dubbleptr[i]);
		}
		i++;
	}
	return (NULL);
}

char	**find_path(char **envp)
{
	char	*ptr;
	char	**dubbleptr;
	int		i;

	i = 0;
	while (!strstr(envp[i], "PATH="))
		i++;
	ptr = strstr(envp[i], "PATH=");
	ptr += 5;
	dubbleptr = ft_split(ptr, ':');
	return (dubbleptr);
}

void	child_two(t_pipex pipex, char **argv_exe, char **envp)
{
	char	**root_paths;
	//char	*command_path;
	//char	**argv_exe;

	//argv_exe = ft_split(argv[2], ' ');
	dup2(pipex.tube[0], STDIN_FILENO);
	root_paths = find_path(envp);
	pipex.command_path = find_command(root_paths, argv_exe[0]);
	dup2(pipex.outfile, 1);
	execve(pipex.command_path, argv_exe, envp);
}

void	child_one(t_pipex pipex, char **argv_exe, char **envp)
{
	char	**root_paths;
	//char	*command_path;
	//char	**argv_exe;

	//argv_exe = ft_split(argv[2], ' ');
	dup2(pipex.tube[1], STDOUT_FILENO);
	root_paths = find_path(envp);
	pipex.command_path = find_command(root_paths, argv_exe[0]);
	dup2(pipex.infile, 0);
	execve(pipex.command_path, argv_exe, envp);
}

void	pipex_func(t_pipex pipex, char **argv_exe[], char **envp)
{
	// int		pipe_fd[2];
	int		status;
	// pid_t	child1;
	// pid_t	child2;
	//t_pipex	pipex;

	pipe(pipex.tube);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		return (perror("Fork: error pid1 "));
	if (pipex.pid1 == 0)
		child_one(pipex, argv_exe[0], envp);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		return (perror("Fork: error pid2"));
	if (pipex.pid2 == 0)
		child_two(pipex, argv_exe[1], envp);
	close(pipex.tube[0]);         // this is the parent
	close(pipex.tube[1]);         // doing nothing
	waitpid(pipex.pid1, &status, 0);  // supervising the children
	waitpid(pipex.pid2, &status, 0);  // while they finish their tasks
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	//int		fd[2];
//	int		f2;
	char	**argv_exe[2];
	//char	**argv_exe_two;

	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.infile < 0 || pipex.outfile < 0)
		return (-1);
	argv_exe[0] = ft_split(argv[2], ' ');
	argv_exe[1] = ft_split(argv[3], ' ');
	pipex_func(pipex, argv_exe, envp);
	return (0);
}
