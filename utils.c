/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:27:39 by tbouma            #+#    #+#             */
/*   Updated: 2022/04/22 12:50:44 by tbouma           ###   ########.fr       */
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

char	*find_cmd_path(char **root_paths, char *cmd)
{
	char	*temp;
	int		i;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (root_paths[i])
	{
		temp = ft_strjoin(root_paths[i], "/");
		if (temp == NULL)
			error_msg(ERR_MALLOC, 1);
		free(root_paths[i]);
		root_paths[i] = temp;
		temp = ft_strjoin(root_paths[i], cmd);
		if (temp == NULL)
			error_msg(ERR_MALLOC, 1);
		free(root_paths[i]);
		root_paths[i] = temp;
		if (access(root_paths[i], F_OK) == 0)
			return (root_paths[i]);
		i++;
	}
	error_msg(ERR_CMD, 127);
	return (0);
}

char	**find_path(char **envp)
{
	char	*ptr;
	char	**root_paths;
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
	root_paths = ft_split(ptr, ':');
	if (root_paths == NULL)
		error_msg(ERR_MALLOC, 1);
	return (root_paths);
}
