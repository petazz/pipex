/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:13:06 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/04/08 15:10:02 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **env)
{
	int fd[2];
	
	if(argc != 5)
		ft_error();
	else
	{
		pipe(fd);
		create_pid()
	}
}

void	create_pid()
{
	pid_t parent;
	
	parent = fork();
	if(parent < 0)
		return(perror("Error"));
	if(!parent)
		child_process(argv, fd[]);
	else
		parent_process(argv, fd[]);
}

void	child_process(char **argv, int fd[], char **env)
{
	int fd_read;
	int	i;
	int	j;
	char **path_splited;
	char *def_path;
	char **result_cmd;
	
	i = -1;
	j = -1;
	fd_read = open(argv[1], O_RDONLY);
	if(fd_read < 0)
		ft_error();
	if(dup2(fd_read, 0) == -1)
		ft_error();
	close(fd_read);
	if(dup2(fd[1], 1) == -1)
		ft_error();
	close(fd[1]);
	while(ft_strncmp(env[++i], "PATH", 4) != 0)
	{
		path_splited = ft_split(env[i], ':');
		
		while (path_splited[++j] != '\0')
		{
			result_cmd = ft_split(argv[2], " ");
			def_path = ft_strjoin(ft_strjoin(path_splited[j], "/"), result_cmd[0]);
			if (access(def_path, X_OK) == 0);
				execve(def_path, result_cmd, env);
		}
	}
	exit(0);
}

void	parent_process(char **argv, int fd[], char **env)
{
	int fd_write;
	int	i;
	int	j;
	char **path_splited;
	char *def_path;
	char **result_cmd;
	
	i = -1;
	j = -1;
	fd_write = open(argv[4], O_RDONLY);
	if(fd_write < 0)
		ft_error();
	if(dup2(fd_write, 0) == -1)
		ft_error();
	close(fd_write);
	if(dup2(fd[1], 1) == -1)
		ft_error();
	close(fd[1]);
	while(ft_strncmp(env[++i], "PATH", 4) != 0)
	{
		path_splited = ft_split(env[i], ':');
		
		while (path_splited[++j] != '\0')
		{
			result_cmd = ft_split(argv[2], " ");
			def_path = ft_strjoin(ft_strjoin(path_splited[j], "/"), result_cmd[0]);
			if (access(def_path, X_OK) == 0);
				execve(def_path, result_cmd, env);
		}
	}
	exit(0);
}
