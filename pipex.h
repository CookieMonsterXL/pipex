/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:38:28 by tbouma            #+#    #+#             */
/*   Updated: 2022/03/24 13:03:33 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <stdio.h>

/* to write, read, close, access, pipe, dup, dup2, execve, fork */
# include <sys/types.h>
# include <sys/uio.h>

/* malloc, free, exit */
# include <stdlib.h>

/* open, unlink */
# include <fcntl.h>

/* waitpid, wait */
# include <sys/wait.h>

/* strerror */
# include <string.h>

/*to perror*/
# include <stdio.h>

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
	char	**argv_exe[2];
}t_pipex;

/* childs.c */
void	child_one(t_pipex pipex, char *envp[]);
void	child_two(t_pipex pipex, char *envp[]);

/* free.c */
void	parent_free(t_pipex *pipex);
void	child_free(t_pipex *pipex);

/* error.c */
void	msg_error(char *err);
int		msg(char *err);

/* funcions */
char	*find_command(char **dubbleptr, char *command);
char	**find_path(char **envp);
// char	*ft_strjoin(char const *s1, char const *s2);
// char	*ft_strdup(const char *src);
// char	**ft_split(char const *s, char c);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif