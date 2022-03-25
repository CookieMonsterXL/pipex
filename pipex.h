/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:38:28 by tbouma            #+#    #+#             */
/*   Updated: 2022/03/24 18:35:09 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>

# define ERR_INFILE		"Infile"
# define ERR_OUTFILE	"Outfile"
# define ERR_INPUT		"Invallid number of arguments."
# define ERR_PIPE		"Pipe error"
# define ERR_CMD		"Command not found"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	int		infile;
	int		outfile;
	char	*command_path;
	char	**cmd_args;
	char	*cmd;
	char	**command[2];
}t_pipex;

void	parent_procces(t_pipex pipex, char **envp);

/* childs.c */
void	child_one(t_pipex pipex, char *envp[]);
void	child_two(t_pipex pipex, char *envp[]);

/* utils.c */
void	parent_free(t_pipex *pipex);
void	child_free(t_pipex *pipex);

/* utils */
char	*find_command_path(char **dubbleptr, char *command);
char	**find_path(char **envp);


#endif