/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnelo <nnelo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:55:46 by nnelo             #+#    #+#             */
/*   Updated: 2024/12/19 21:43:57 by nnelo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

static void	close_all(int files[2], int fd[2])
{
	close(fd[0]);
	close(fd[1]);
	close(files[0]);
	close(files[1]);
}

static void	write_in_pipe(int files[2], int fd[2], char **argv, char **envp)
{
	char	**cmd1;
	char	*path;

	dup2(files[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close_all(files, fd);
	cmd1 = ft_split(argv[2], ' ');
	if (!cmd1)
		exit(1);
	path = ft_strjoin("/bin/", cmd1[0]);
	if (!path)
	{
		free_cmd(cmd1);
		exit(1);
	}
	execve(path, cmd1, envp);
	write(2, "Execve failed for cmd1\n", 23);
	free_cmd(cmd1);
	free(path);
	exit(1);
}

static void	write_in_file(int files[2], int fd[2], char **argv, char **envp)
{
	char	**cmd2;
	char	*path;

	dup2(fd[0], STDIN_FILENO);
	dup2(files[1], STDOUT_FILENO);
	close_all(files, fd);
	cmd2 = ft_split(argv[3], ' ');
	if (!cmd2)
		exit(1);
	path = ft_strjoin("/bin/", cmd2[0]);
	if (!path)
	{
		free_cmd(cmd2);
		exit(1);
	}
	execve(path, cmd2, envp);
	write(2, "Execve failed for cmd2\n", 23);
	free_cmd(cmd2);
	free(path);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	int		files[2];
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		exit(ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile\n"));
	if (pipe(fd) == -1)
		exit(ft_printf("pipe error\n"));
	if (access(argv[1], F_OK) == -1)
		exit(ft_printf("%s: No such file\n", argv[1]));
	if (access(argv[1], R_OK) == -1)
		exit(ft_printf("%s: permission denied\n", argv[1]));
	pid = fork();
	files[0] = open(argv[1], O_RDONLY);
	files[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (files[0] == -1 || files[1] == -1 || pid == -1)
		exit(ft_printf("failed open file or fork error\n"));
	if (pid == 0)
		write_in_pipe(files, fd, argv, envp);
	if (fork() == 0)
		write_in_file(files, fd, argv, envp);
	close_all(files, fd);
	wait(NULL);
	wait(NULL);
	return (0);
}
