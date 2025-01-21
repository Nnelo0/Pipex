/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebroudic <ebroudic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:18:33 by ebroudic          #+#    #+#             */
/*   Updated: 2025/01/21 13:06:23 by ebroudic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(int files[2], char **argv)
{
	files[0] = open(argv[1], O_RDONLY);
	files[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (files[0] == -1)
		ft_printf("pipex: No such file or permission denied: %s\n", \
		argv[1]);
	if (files[1] == -1)
	{
		if (files[0] != -1)
			close(files[0]);
		exit(ft_printf("pipex: permission denied: %s\n", argv[4]));
	}
}

void	free_paths(char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
}

char	*find_command_path(char *cmd, char **envp, int i)
{
	char	**paths;
	char	*path;
	char	*part_path;

	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			free_paths(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_paths(paths);
	return (0);
}

static void	close_and_free(t_pipex *pipex, int files[2])
{
	free_cmd(pipex->cmd1);
	free_cmd(pipex->cmd2);
	close(files[1]);
	close(files[0]);
}

void	check_command(char **argv, char **envp, t_pipex *pipex, int files[2])
{
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->path1 = find_command_path(*pipex->cmd1, envp, 0);
	pipex->cmd2 = ft_split(argv[3], ' ');
	pipex->path2 = find_command_path(*pipex->cmd2, envp, 0);
	if (!pipex->path1 && !pipex->path2)
	{
		close_and_free(pipex, files);
		exit(write(2, "pipex: command not found for cmd1 and cmd2\n", 43));
	}
	if (!pipex->path1)
	{
		free(pipex->path2);
		close_and_free(pipex, files);
		exit(write(2, "pipex: command not found for cmd1\n", 34));
	}
	if (!pipex->path2)
	{
		free(pipex->path1);
		close_and_free(pipex, files);
		exit(write(2, "pipex: command not found for cmd2\n", 34));
	}
}
