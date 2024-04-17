/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:13:06 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/04/17 12:19:46 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv, char **env)
{
	int fd[2];
	
	if(argc != 5)
		ft_error("No tiene 5 argumentos");
	else
	{
		pipe(fd);
		create_fork_pid(argv, fd, env);
	}
}

void	create_fork_pid(char **argv, int *fd, char **env)
{
	pid_t pid;
	pid_t pid2;

	pid = fork();
	if(pid < 0)
		ft_error("Error en el primer fork");
	if(pid == 0)
		child_process(argv, fd, env);
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		pid2 = fork();
		if(pid2 < 0)
			ft_error("Error en el segundo fork");
		if(pid2 == 0)
			second_child_process(argv, fd, env);
		else
		{		
			close(fd[0]);
			waitpid(pid2, NULL, 0);
		}
	}
}

void	split_path(char **env, char **argv)
{
	char **path_splited;
	char **result_cmd;
	int	i;
	int	j;
	char *def_path;
	
	i = 0;
	j = -1;
	while(env[i])
	{
		if(ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_splited = ft_split(&env[i][5], ':');
			while (path_splited[++j] != NULL)
			{
				result_cmd = ft_split(*argv, ' ');
				def_path = ft_strjoin(path_splited[j], "/");
				def_path = ft_strjoin(def_path, result_cmd[0]);
				ft_putstr_fd(def_path, 2);
				if (access(def_path, X_OK) != 0)
					ft_execve(def_path, split_cmd(*argv), env);
				else
				{
					free(def_path);
					ft_error("Command not found\n");
				}
			}
		}
		i++;
	}
}

int	ft_count_comites(char const *s, char c)
{
	int	num_comites;
	int	i;

	i = 0;
	num_comites = 0;
	while (s[i] != '\0')
	{
		if(s[i] == c)
			num_comites++;
		i++;
	}
	return (num_comites);
}

char	**split_cmd(char *argv)
{
	char **cmd;
	int num_comites;

	cmd = NULL;
	num_comites = ft_count_comites(argv, '\'');
	if(num_comites == 2)
	{	
		cmd = ft_split(argv, '\'');
		cmd[0] = ft_strtrim(cmd[0], " ");
		return (cmd);
	}	
	else if(num_comites == 4)
	{
		cmd = ft_split(argv, ' ');
		return (cmd);
	}
	else
		ft_error("error de comandos");
	return (cmd);
}

void	child_process(char **argv, int fd[], char **env)
{
	int infile_fd;

	close(fd[0]);
	infile_fd = open(argv[1], O_RDONLY);
	if(infile_fd < 0)
		ft_error("Error abriendo infile");
	if(dup2(infile_fd, STDIN_FILENO) == -1)
		ft_error("Error en la redireccion de la entrada a STDIN");
	close(infile_fd);
	if(dup2(fd[1], STDOUT_FILENO) == -1)
		ft_error("Error en la redireccion de escritura del pipe");
	close(fd[1]);
	split_path(env, &argv[2]);
	exit(0);
}

void	second_child_process(char **argv, int fd[], char **env)
{
	int outfile_fd;
	
	close(fd[1]);
	outfile_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(outfile_fd < 0)
		ft_error("Error creando outfile");
	if(dup2(fd[0], STDIN_FILENO) == -1)
		ft_error("Error en la redireccion de lectura del pipe");
	close(fd[0]);
	if(dup2(outfile_fd, STDOUT_FILENO) == -1)
		ft_error("Error en la redireccion de salida a STDOUT");
	close(outfile_fd);
	split_path(env, &argv[3]);
	exit(0);
}
