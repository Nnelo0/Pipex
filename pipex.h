/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebroudic <ebroudic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:53:43 by nnelo             #+#    #+#             */
/*   Updated: 2025/01/21 13:04:01 by ebroudic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft/libft.h"
# include "libft/printf/ft_printf.h"
# include <sys/wait.h>

typedef struct s_pipex
{
	char	**cmd1;
	char	**cmd2;
	char	*path1;
	char	*path2;
}					t_pipex;

void	open_files(int files[2], char **argv);
char	*find_command_path(char *cmd, char **envp, int i);
void	close_all(int files[2], int fd[2]);
void	check_command(char **argv, char **envp, t_pipex *pipex, int files[2]);
void	free_cmd(char **cmd);
void	check_arg(char **argv);

#endif