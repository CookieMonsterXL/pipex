/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:38:28 by tbouma            #+#    #+#             */
/*   Updated: 2022/04/13 12:49:00 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>

# define ERR_FILE		"Infile or outfile error"
# define ERR_FORK		"Fork error"
# define ERR_INPUT		"Invallid number of arguments."
# define ERR_PIPE		"Pipe error"
# define ERR_CMD		"Command not found"
# define ERR_MALLOC		"Malloc error"

typedef struct s_pipex
{
	pid_t	pid1;
	int		tube[2];
	int		infile;
	int		outfile;
	char	*command_path;
	char	**command[2];
}t_pipex;

/* childs.c */
void	child_one(t_pipex pipex, char *envp[]);
void	child_two(t_pipex pipex, char *envp[]);

/* utils.c */
char	*find_command_path(char **dubbleptr, char *command);
char	**find_path(char **envp);
void	error_msg(char *msg);
void	parent_free(t_pipex *pipex);

#endif