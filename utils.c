/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebroudic <ebroudic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:18:33 by ebroudic          #+#    #+#             */
/*   Updated: 2024/12/20 10:37:46 by ebroudic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(int files[2], char **argv, int fd[2])
{
	files[0] = open(argv[1], O_RDONLY);
	files[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (files[0] == -1 && files[1] == -1)
	{
		close_all(files, fd);
		exit(ft_printf("%s: No such file or permission denied\n\
%s: permission denied\n", argv[1], argv[4]));
	}
	if (files[0] == -1)
	{
		close_all(files, fd);
		exit(ft_printf("%s: No such file or permission denied\n", argv[1]));
	}
	if (files[1] == -1)
	{
		close_all(files, fd);
		exit(ft_printf("%s: permission denied\n", argv[4]));
	}
}

char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}
