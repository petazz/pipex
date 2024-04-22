/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:13:06 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/04/22 12:01:02 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int	fd[2];

	if (argc != 5)
		ft_error("No tiene 5 argumentos");
	else
	{
		pipe(fd);
		create_fork_pid(argv, fd, env);
	}
}

void	create_fork_pid(char **argv, int *fd, char **env)
{
	pid_t	pid;
	pid_t	pid2;

	pid = fork();
	if (pid < 0)
		ft_error("Error en el primer fork");
	if (pid == 0)
		child_process(argv, fd, env);
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		pid2 = fork();
		if (pid2 < 0)
			ft_error("Error en el segundo fork");
		if (pid2 == 0)
			second_child_process(argv, fd, env);
		else
		{
			close(fd[0]);
			waitpid(pid2, NULL, 0);
		}
	}
}

char	*split_path(char **env, char **argv)
{
	char	**path_splited;
	char	**result_cmd;
	int		i;
	int		j;
	char	*def_path;

	i = 0;
	j = -1;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_splited = ft_split(&env[i][5], ':');
			while (path_splited[++j] != NULL)
			{
				result_cmd = ft_split(*argv, ' ');
				def_path = ft_strjoin(path_splited[j], "/");
				def_path = ft_strjoin(def_path, result_cmd[0]);
				if (ft_execve(def_path))
					return (def_path);
			}
		}
		i++;
	}
	return (NULL);
}

void	child_process(char **argv, int fd[], char **env)
{
	int		infile_fd;
	char	*def_path;

	close(fd[0]);
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd < 0)
		ft_error("Error abriendo infile");
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		ft_error("Error en la redireccion de la entrada a STDIN");
	close(infile_fd);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_error("Error en la redireccion de escritura del pipe");
	close(fd[1]);
	def_path = split_path(env, &argv[2]);
	if (!def_path)
		ft_error("Error de comandos");
	execve(def_path, split_cmd(argv[2]), env);
	exit(0);
}

void	second_child_process(char **argv, int fd[], char **env)
{
	int		outfile_fd;
	char	*def_path;

	close(fd[1]);
	outfile_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile_fd < 0)
		ft_error("Error creando outfile");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_error("Error en la redireccion de lectura del pipe");
	close(fd[0]);
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		ft_error("Error en la redireccion de salida a STDOUT");
	close(outfile_fd);
	def_path = split_path(env, &argv[3]);
	if (!def_path)
		ft_error("Error de comandos");
	execve(def_path, split_cmd(argv[3]), env);
	exit(0);
}
