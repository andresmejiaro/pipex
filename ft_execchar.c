/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:37:04 by amejia            #+#    #+#             */
/*   Updated: 2023/03/13 16:17:47 by amejia           ###   ########.fr       */
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
		path = ft_strjoin(envpaths[ct], "/");
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
		command = ft_substr(command, 0, ft_strchr(command, ' ') - command);
	else
		command = ft_substr(command, 0, ft_strlen(command));
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
	temp = ft_split(envp[c], '=');
	envpaths = ft_split(temp[1], ':');
	ft_free_split(temp);
	return (find_path2(command, envpaths));
}

//this mallocs the new split element AND frees the list;
char **list_to_split(t_list **list)
{
	int len;
	char **to_return;
	t_list *org;
	
	len = ft_lstsize(*list);
	to_return =(char **)ft_calloc(len + 1, sizeof(char *));
	len = 0;
	while (*list != NULL)
	{
		to_return[len] = (char *)(*list)->content;
		len++;
		org = *list;
		(*list) = (*list)->next;
		free(org);
	}
	list = NULL;
	return (to_return);
}


void argv_generator_list(char *command, t_list **argv_argsi)
{
	char *startp[2];
	
	startp[0] = ft_strchr(command, '\'');
	startp[1] = ft_strchr(command,'\"');
	if (startp[0] == 0 && startp[1] == 0)
		argv_generator_ap(command,' ', argv_argsi);
	else if ((startp[0] < startp[1] && startp[0] != 0) || startp[1] == 0)
		argv_generator_ap(command,'\'', argv_argsi);
	else
		argv_generator_ap(command,'\"', argv_argsi);
}

int argv_generator_ap(char *command, char lim, t_list **argv_args)
{
	char **split_temp[2];
	int ct[4];
	char *temp;

	ft_bzero(ct, 4 * sizeof(int));
	split_temp[0] = ft_split(command, lim);
	if (split_temp[0] == 0)
		return (0);
	if (lim == ' ')
		ct[3] = 1;
	while (split_temp[0][ct[0]] != 0)
	{
		if(ct[0] % 2 == 0 && ct[3] != 1)
		{
			argv_generator_list(split_temp[0][ct[0]], argv_args);
		}
		else
		{
			temp = ft_substr(split_temp[0][ct[0]], 0, \
				ft_strlen(split_temp[0][ct[0]]));
			if (temp == 0)
			{
				ft_free_split(split_temp[0]);
				return (0);
			}
			ft_lstadd_back(argv_args,ft_lstnew(temp));	
		}
	ct[0]++;
	}
	return (1);
}

//this split mallocs the result
char	**argv_generator(char *command)
{
	char	**to_return;
	char	*program[2];
	t_list	*params;

	params = NULL;
	argv_generator_list(command, &params);
	to_return = list_to_split(&params);
	if (to_return == 0)
		exit (2);
	program[0] = ft_strchr(to_return[0], '\\');
	program[1] = to_return[0];
	while (program[0] != NULL)
	{
		program[1] = program[0];
		program[0] = ft_strchr(program[1] + 1, '\\');
	}
	free(to_return[0]);
	to_return[0] = ft_substr(program[1], 0, ft_strlen(program[1]));
	if (to_return[0] == 0)
			return (ft_free_split(to_return), NULL);
	return (to_return);
}

int	ft_execchar(char *command, char **envp)
{
	char	*path_to_exec;
	char	**new_argv;

	path_to_exec = find_path(command, envp);
	new_argv = argv_generator(command);
	if (execve(path_to_exec, new_argv, envp) == -1)
		return(127);
	return (0);
}
