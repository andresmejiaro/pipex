/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:37:04 by amejia            #+#    #+#             */
/*   Updated: 2023/03/06 23:54:52 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path2(char *command, char **envpaths)
{
	int		ct;
	char	*path;
	char	*temp;

	ct = 0;
	while (envpaths[ct] != NULL)
	{
		path = ft_strjoin(envpaths[ct],"/");
		if (path == 0)
			exit (2);
		temp = path;
		path = ft_strjoin(path, command);
		if (path == 0)
			exit (2);
		free(temp);
		if (!access(path, F_OK))
			return (free(command), ft_free_split(envpaths), path);
		ct++;
	}
	return (free(command), ft_free_split(envpaths), NULL);
}

char	*separate_program_name(char *command)
{
	if (ft_strchr(command, ' ') != 0)
		command = ft_substr(command, 0 ,ft_strchr(command, ' ') - command);
	else
		command = ft_substr(command, 0 ,ft_strlen(command));
	return (command);
}

//this function mallocs its result
char	*find_path(char *command, char **envp)
{
	char	*path;
	char	**temp;
	char	**envpaths;
	int		c;

	command = separate_program_name(command);
	if (command == 0)
		return (0);
	if (!access(command, X_OK))
		return (command);
	path = ft_strjoin("./", command);
	if (path != 0 && !access(path, X_OK))
		return (free(command), path);
	else if (path == 0)
		return (free(command), NULL);
	free(path);
	c = -1;
	while (envp[++c] != NULL && !ft_strnstr(envp[c], "PATH", 4))
		;
	if (envp[c] == NULL)
		exit (1);
	temp = ft_split(envp[c],'=');
	envpaths = ft_split(temp[1],':');
	ft_free_split(temp);
	return (find_path2(command, envpaths));
}

//this split mallocs the result
char	**argv_generator(char *command)
{
	char	**to_return;
	char	*program[2];

	to_return = ft_split(command, ' ');
	if (to_return == 0)
		exit (2);
	program[0] = ft_strchr(command, '\\');
	program[1] = command;
	while (program[0] != NULL)
	{
		program[1] = program[0];
		program[0] = ft_strchr(program[1] + 1, '\\');
	}
	free(to_return[0]);
	to_return[0] = ft_substr(program[1], 0, ft_strlen(program[1]));
	return (to_return);
}

void	ft_execchar(char *command, char **envp)
{
	char	*path_to_exec;
	char	**new_argv;

	path_to_exec = find_path(command, envp);
	new_argv = argv_generator(command);
	if (execve(path_to_exec, new_argv, envp) == -1)
		exit(2);
}
