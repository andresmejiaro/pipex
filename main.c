/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 23:59:25 by amejia            #+#    #+#             */
/*   Updated: 2023/03/07 17:15:17 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*fd_read(int fd)
{
	char	*to_return;
	char	*line;
	char	*old;

	to_return = (char *)ft_calloc(1, 1);
	if (to_return == 0)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		old = to_return;
		to_return = ft_strjoin(to_return, line);
		if (to_return == 0)
			return (free(old), free(line), NULL);
		free(old);
		free(line);
		line = get_next_line(fd);
	}
	return (to_return);
}

//pipein and out are from the POV of the child so these are reversed
void	dad_stuff(char **holdout, int *pipein, int *pipeout)
{
	close(pipein[0]);
	close(pipeout[1]);
	write(pipein[1], *holdout, ft_strlen(*holdout));
	close(pipein[1]);
	free(*holdout);
	wait(NULL);
	*holdout = fd_read(pipeout[0]);
	close(pipeout[0]);
}

void	kid_stuff(char *command, int *pipein, int *pipeout, char **envp)
{
	close(pipein[1]);
	close(pipeout[0]);
	dup2(pipein[0], STDIN_FILENO);
	dup2(pipeout[1], STDOUT_FILENO);
	close(pipein[0]);
	close(pipeout[0]);
	ft_execchar(command, envp);
	return ;
}

char	*ft_read_file(char *path)
{
	int		fd;
	char	*to_return;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	to_return = fd_read(fd);
	close(fd);
	return (to_return);
}

int	main(int argc, char **argv, char**envp)
{
	int		id;
	int		pipein[2];
	int		pipeout[2];
	char	*holdout;
	int		ct;

	if (argc < 5)
		return (1);
	holdout = ft_read_file(argv[1]);
	if (holdout == 0)
		return (2);
	ct = 2;
	while (ct < argc -1)
	{
		pipe(pipein);
		pipe(pipeout);
		id = fork();
		if (id == 0)
			kid_stuff(argv[ct], pipein, pipeout, envp);
		else
			dad_stuff(&holdout, pipein, pipeout);
		ct++;
	}
	ct = open(argv[ct], O_WRONLY | O_CREAT | O_TRUNC , 0644);
	write(ct, holdout, ft_strlen(holdout));
	close(ct);
	return (0);
}
