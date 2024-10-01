/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:05:40 by jacha             #+#    #+#             */
/*   Updated: 2024/05/21 17:06:23 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int	in_file;

	in_file = open(argv[1], O_RDONLY, 0777);
	if (in_file == -1)
		error();
	dup2(fd[1], 1);
	dup2(in_file, 0);
	close(fd[0]);
	execution(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	out_file;

	out_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out_file == -1)
		error();
	dup2(fd[0], 0);
	dup2(out_file, 1);
	close(fd[1]);
	execution(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error();
		pid = fork();
		if (pid == -1)
			error();
		if (pid == 0)
			child_process(argv, envp, fd);
		waitpid(pid, NULL, 0);
		parent_process(argv, envp, fd);
	}
	else
	{
		ft_putstr_fd("RETRY!!!", 1);
	}
	return (0);
}
