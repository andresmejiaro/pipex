/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 23:59:25 by amejia            #+#    #+#             */
/*   Updated: 2023/03/15 23:05:25 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	kid_stuff(char *command, int *pipein, int *pipeout, char **envp)
{
	int	res;

	close(pipein[1]);
	close(pipeout[0]);
	dup2(pipein[0], STDIN_FILENO);
	dup2(pipeout[1], STDOUT_FILENO);
	close(pipein[0]);
	close(pipeout[0]);
	res = ft_execchar(command, envp);
	return (res);
}

int	**pipe_generator(int npipes)
{
	int	**to_return;
	int	ct;

	to_return = (int **)ft_calloc(npipes, sizeof(int *));
	if (to_return == 0)
		return (0);
	ct = 0;
	while (ct < npipes)
	{
		to_return[ct] = ft_calloc(2, sizeof(int));
		if (to_return[ct] == 0)
			break ;
		ct++;
	}
	if (ct == npipes)
	{
		while (ct-- > 0)
			pipe(to_return[ct]);
		return (to_return);
	}
	else
		while (ct-- > 0)
			free(to_return[ct]);
	return (free(to_return), (int **)0);
}

int	main(int argc, char **argv, char**envp)
{
	int		id;
	int		**pip;
	int		ct;

	if (argc < 5)
		exit (EXIT_FAILURE);
	pip = pipe_generator(argc - 2);
	if (pip == 0)
		exit (EXIT_FAILURE);
	pip[0][0] = open(argv[1], O_RDONLY);
	pip[argc - 3][1] = open(argv[argc -1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pip[0][0] == -1 || pip[argc - 3][1] == -1)
		exit (EXIT_FAILURE);
	ct = 2;
	while (ct <= argc - 1)
	{
		if (ct < argc - 1)
			id = fork();
		if (id == 0)
			return (kid_stuff(argv[ct], pip[ct - 2], pip [ct -1], envp));
		close(pip[ct - 2][1]);
		close(pip[ct - 2][0]);
		ct++;
	}
	return (waitpid(id, &ct, 0), ct);
}
