/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:27:39 by tbouma            #+#    #+#             */
/*   Updated: 2022/04/15 16:38:08 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_msg(char *msg, int err)
{
	ft_putendl_fd(msg, 2);
	exit(err);
}

void	perror_msg(char *msg, int err)
{
	perror(msg);
	exit(err);
}

void	parent_free(t_pipex *pipex)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (pipex->command[i])
	{
		free(pipex->command[i]);
		i++;
	}
}

char	*find_command_path(char **dubbleptr, char *command)
{
	char	*temp;
	int		i;

	i = 0;
	while (dubbleptr[i])
	{
		temp = ft_strjoin(dubbleptr[i], "/");
		if (temp == NULL)
			error_msg(ERR_MALLOC, 1);
		free(dubbleptr[i]);
		dubbleptr[i] = temp;
		temp = ft_strjoin(dubbleptr[i], command);
		if (temp == NULL)
			error_msg(ERR_MALLOC, 1);
		free(dubbleptr[i]);
		dubbleptr[i] = temp;
		if (access(dubbleptr[i], F_OK) == 0)
		{
			return (dubbleptr[i]);
		}
		i++;
	}
	error_msg(ERR_CMD, 127);
	return (0);
}

char	**find_path(char **envp)
{
	char	*ptr;
	char	**dubbleptr;
	int		i;

	i = 0;
	while (envp[i])
	{
		ptr = ft_strnstr(envp[i], "PATH=", strlen(envp[i]));
		if (ptr != NULL)
			break ;
		i++;
	}
	ptr += 5;
	dubbleptr = ft_split(ptr, ':');
	if (dubbleptr == NULL)
		error_msg(ERR_MALLOC, 1);
	return (dubbleptr);
}
