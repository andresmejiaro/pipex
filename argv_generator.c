/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_generator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:21:59 by amejia            #+#    #+#             */
/*   Updated: 2023/03/15 23:07:23 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//this mallocs the new split element AND frees the list;
char	**list_to_split(t_list **list)
{
	int		len;
	char	**to_return;
	t_list	*org;

	len = ft_lstsize(*list);
	to_return = (char **)ft_calloc(len + 1, sizeof(char *));
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

void	remove_escaped(char *str, char esc)
{
	char	*find;

	find = ft_strchr(str, esc);
	while (find != 0)
	{
		if (find > str && *(find - 1) == '\\')
		{
			ft_delete_char(find - 1);
			find = ft_strchr(find, esc);
		}
		else
			find = ft_strchr(find + 1, esc);
	}
}

void	argv_generator_v(char **sep, char **command, t_list **argv_args)
{		
	char	*temp;

	if (sep[0] > *command)
	{
		temp = ft_substr(*command, 0, (unsigned int)(sep[0] - *command));
		ft_lstadd_back(argv_args, ft_lstnew(temp));
		*command += (unsigned int)(sep[0] - *command);
	}
	else if (sep[0] == 0)
	{
		temp = ft_substr(*command, 0, ft_strlen(*command));
		ft_lstadd_back(argv_args, ft_lstnew(temp));
		(*command) += ft_strlen(*command);
	}
	else if (**command == ' ')
		(*command)++;
	else if (**command == '\'' || **command == '\"')
	{
		sep[0] = ft_strchr_esc(*command + 1, **command);
		temp = ft_substr(*command, 1, (unsigned int)(sep[0] - *command) - 1);
		remove_escaped(temp, **command);
		ft_lstadd_back(argv_args, ft_lstnew(temp));
		*command += (unsigned int)(sep[0] - *command) + 1;
	}
}

void	argv_generator_ap(char *command, t_list **argv_args)
{
	char	*sep[3];

	while (ft_strlen(command) > 0)
	{	
		sep[0] = ft_strchr(command, ' ');
		sep[1] = ft_strchr(command, '\'');
		sep[2] = ft_strchr(command, '\"');
		sep[0] = ft_min_str(ft_min_str(sep[0], sep[1]), sep[2]);
		argv_generator_v(sep, &command, argv_args);
	}
}

//this split mallocs the result
char	**argv_generator(char *command)
{
	char	**to_return;
	char	*program[2];
	t_list	*params;

	params = NULL;
	argv_generator_ap(command, &params);
	to_return = list_to_split(&params);
	if (to_return == 0)
		exit (EXIT_FAILURE);
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
