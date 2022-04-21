/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:06:42 by tbouma            #+#    #+#             */
/*   Updated: 2022/04/21 18:26:39 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	last_child(t_p *p, char **envp)
{
	p->child_n++;
	if (p->pid_child > 0)
		p->pid_child = fork();
	if (p->pid_child < 0)
		error_msg(ERR_FORK, 1);
	if (p->pid_child == 0)
		child(p, envp);
}

static void	parent_procces(t_p *p, char **envp)
{
	int	status;
	int	exit_status;

	p->child_n = 0;
	p->pid_child = 1;
	while (p->child_n + 1 < (p->argc - 3))
	{
		p->child_n++;
		pipe(p->tube);
		if (p->pid_child > 0)
			p->pid_child = fork();
		if (p->pid_child < 0)
			error_msg(ERR_FORK, 1);
		if (p->pid_child == 0)
			child(p, envp);
		else
		{
			dup2(p->tube[0], STDIN_FILENO);
			close(p->tube[1]);
		}
	}
	last_child(p, envp);
	waitpid(p->pid_child, &status, 0);
		if (WIFEXITED(status) > 0)
		{
			exit_status = WEXITSTATUS(status);
			exit(exit_status);
		}
}

int	main(int argc, char **argv, char **envp)
{
	t_p	p;

	if (argc < 5)
		error_msg(ERR_INPUT, 1);
	p.argc = argc;
	p.argv = argv;
	p.infile = open(argv[1], O_RDONLY);
	p.outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (p.infile < 0 || p.outfile < 0)
		error_msg(ERR_FILE, 1);
	if (dup2(p.infile, STDIN_FILENO) < 0)
		perror_msg(ERR_DUP, 1);
	if (dup2(p.outfile, STDOUT_FILENO) < 0)
		perror_msg(ERR_DUP, 1);
	p.root_paths = find_path(envp);
	if (p.root_paths == NULL)
		error_msg(ERR_MALLOC, 1);
	parent_procces(&p, envp);
	free(p.root_paths);
	return (0);
}

	// write(2, "Einde main\n", 6);
	// system("leaks pipex");
// ./pipex text.txt "grep k" "cat" text2.txt
// ./pipex text.txt "grep 5" "cat -e" "wc -l" text2.txt
//  ./pipex text.txt "grep is" "sleep 5" "grep Tiemen" text2.txt
//-fsanitize=address -g