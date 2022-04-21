/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:38:28 by tbouma            #+#    #+#             */
/*   Updated: 2022/04/21 16:01:16 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>

# define ERR_FILE		"Infile or outfile error"
# define ERR_FORK		"Fork error"
# define ERR_INPUT		"Invalid number of arguments"
# define ERR_PIPE		"Pipe error"
# define ERR_CMD		"command not found"
# define ERR_MALLOC		"Malloc error"
# define ERR_DUP		"Dup2 error"
# define ERR_PROCCES	"Procces error"

typedef struct s_p
{
	pid_t	pid_child;
	pid_t	wait;
	int		tube[2];
	int		infile;
	int		outfile;
	char	*cmd_path;
	char	**cmd;
	int		argc;
	char	**argv;
	int		child_n;
	char	**root_paths;
}t_p;

/* childs.c */
void	child(t_p *p, char **envp);
// void	child_one(t_p p, char *envp[]);
// void	child_two(t_p p, char *envp[]);

/* utils.c */
char	*find_cmd_path(char **dubbleptr, char *cmd);
char	**find_path(char **envp);
void	error_msg(char *msg, int err);
void	perror_msg(char *msg, int err);

#endif