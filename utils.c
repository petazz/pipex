/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:41:20 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/04/22 12:01:52 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**split_cmd(char *argv)
{
	char	**cmd;
	int		num_comites;

	cmd = NULL;
	num_comites = ft_count_comites(argv, '\'');
	if (num_comites == 2)
	{
		cmd = ft_split(argv, '\'');
		cmd[0] = ft_strtrim(cmd[0], " ");
		return (cmd);
	}
	else
	{
		cmd = ft_split(argv, ' ');
		return (cmd);
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
		if (s[i] == c)
			num_comites++;
		i++;
	}
	return (num_comites);
}

char	*ft_execve(char *def_path)
{
	if (access(def_path, X_OK) == 0)
		return (def_path);
	else
	{
		free(def_path);
		return (NULL);
	}
}

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}
