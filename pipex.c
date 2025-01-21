/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebroudic <ebroudic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:55:46 by nnelo             #+#    #+#             */
/*   Updated: 2025/01/21 13:04:06 by ebroudic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmd(char **cmd)
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

void	close_all(int files[2], int fd[2])
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	if (files[0] != -1)
		close(files[0]);
	if (files[1] != -1)
		close(files[1]);
}

static void	write_in_pipe(int files[2], int fd[2], t_pipex *pipex, char **envp)
{
	if (dup2(files[0], STDIN_FILENO) == -1)
	{
		close_all(files, fd);
		exit(0);
	}
	dup2(fd[1], STDOUT_FILENO);
	close_all(files, fd);
	execve(pipex->path1, pipex->cmd1, envp);
	write(2, "pipex: command not found for cmd1\n", 34);
	free_cmd(pipex->cmd1);
	free(pipex->path1);
	exit(0);
}

static void	write_in_file(int files[2], int fd[2], t_pipex *pipex, char **envp)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(files[1], STDOUT_FILENO);
	close_all(files, fd);
	execve(pipex->path2, pipex->cmd2, envp);
	write(2, "pipex: command not found for cmd2\n", 34);
	free_cmd(pipex->cmd2);
	free(pipex->path2);
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	int		files[2];
	int		fd[2];
	pid_t	pid;
	t_pipex	pipex;

	pipex.cmd1 = NULL;
	pipex.cmd2 = NULL;
	pipex.path1 = NULL;
	pipex.path2 = NULL;
	if (argc != 5)
		exit(ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile\n"));
	open_files(files, argv);
	check_command(argv, envp, &pipex, files);
	if (pipe(fd) == -1)
		exit(ft_printf("pipe error\n") - 11);
	pid = fork();
	if (pid == -1)
		exit(ft_printf("fork error\n") - 11);
	if (pid == 0)
		write_in_pipe(files, fd, &pipex, envp);
	if (fork() == 0)
		write_in_file(files, fd, &pipex, envp);
	close_all(files, fd);
	return (free_cmd(pipex.cmd1), free_cmd(pipex.cmd2), free(pipex.path1),
		free(pipex.path2), wait(NULL), wait(NULL), 0);
}
