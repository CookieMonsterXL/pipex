/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:06:42 by tbouma            #+#    #+#             */
/*   Updated: 2022/04/20 15:55:44 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// static void	dup2_4pipe(int to_stdin, int to_stdout)
// {
// 	dup2(to_stdin, STDIN_FILENO);
// 	dup2(to_stdout, STDOUT_FILENO);
// }

void	child(t_pipex *pipex, char **envp)
{
	char	**root_paths;

	dup2(pipex->tube[1], STDOUT_FILENO);
	close(pipex->tube[0]);
	pipex->command = ft_split(pipex->argv[pipex->child_n + 1], ' ');
	write(2, pipex->command[0], ft_strlen(pipex->command[0]));
	write(2, "\n", 2);
	//dprintf("string command: %s\n", pipex->command[0]);
	if (pipex->command == NULL)
		error_msg(ERR_MALLOC, 1);
	root_paths = find_path(envp);
	pipex->command_path = find_command_path(root_paths, pipex->command[0]);
	execve(pipex->command_path, pipex->command, envp);
}

static void	parent_procces(t_pipex *pipex, char **envp)
{
	int	status;

	pipex->child_n = 0;
	pipex->pid_child = 1;
	while (pipex->child_n < (pipex->argc - 3))
	{
		//close(pipex->tube[0]);
		pipex->child_n++;
		pipe(pipex->tube);
		if (pipex->pid_child > 0)
			pipex->pid_child = fork();
		if (pipex->pid_child < 0)
			error_msg(ERR_FORK, 1);
		if (pipex->pid_child == 0)
			child(pipex, envp);
		else
		{
			dup2(pipex->tube[0], STDIN_FILENO);
			close(pipex->tube[1]);
			close(pipex->tube[0]);
		}
	}
	//close(pipex->tube[0]);
	//close(pipex->tube[1]);
	// pipe(pipex->tube);
	// pipex->pid_child = fork();
	// if (pipex->pid_child < 0)
	// 	error_msg(ERR_FORK, 1);
	// if (pipex->pid_child == 0)
	// 	child_one(*pipex, envp);
	// else
	// {
	// 	pipex->pid2 = fork();
	// 	if (pipex->pid2 < 0)
	// 		error_msg(ERR_FORK, 1);
	// 	if (pipex->pid2 == 0)	
	// 		child_two(*pipex, envp);
	// }
	// close(pipex->tube[0]);
	// close(pipex->tube[1]);
	waitpid(pipex->pid_child, &status, 0);
	//waitpid(pipex->pid2, &status, 0);
	//printf("test");
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.argc = argc;
	pipex.argv = argv;
	if (argc != 5)
		error_msg(ERR_INPUT, 1);
	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.infile < 0 || pipex.outfile < 0)
		error_msg(ERR_FILE, 1);
	if (dup2(pipex.infile, STDIN_FILENO) < 0)
		perror_msg(ERR_DUP, 1);
	if (dup2(pipex.outfile, STDOUT_FILENO) < 0)
		perror_msg(ERR_DUP, 1);
	// pipex.command[0] = ft_split(argv[2], ' ');
	// if (pipex.command[0] == NULL)
	// 	error_msg(ERR_MALLOC, 1);
	// pipex.command[1] = ft_split(argv[3], ' ');
	// if (pipex.command[1] == NULL)
	// 	error_msg(ERR_MALLOC, 1);
	parent_procces(&pipex, envp);
//	parent_free(&pipex);
	write(2, "test2\n", 6);
	return (0);
}

// ./pipex text.txt "grep k" "cat" text2.txt