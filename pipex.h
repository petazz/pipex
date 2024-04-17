/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:28:20 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/04/16 17:35:20 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"

void	create_fork_pid(char **argv, int *fd, char **env);
void	child_process(char **argv, int fd[], char **env);
void	parent_process(char **argv, int fd[], char **env);
void	split_path(char **env, char **argv);
void	second_child_process(char **argv, int fd[], char **env);
void	ft_error(char *str);
char	**split_cmd(char *argv);
int		ft_count_comites(char const *s, char c);


#endif