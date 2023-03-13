/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 23:59:25 by amejia            #+#    #+#             */
/*   Updated: 2023/03/13 14:03:21 by amejia           ###   ########.fr       */
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

int	kid_stuff(char *command, int *pipein, int *pipeout, char **envp)
{
	int res;
	
	close(pipein[1]);
	close(pipeout[0]);
	dup2(pipein[0], STDIN_FILENO);
	dup2(pipeout[1], STDOUT_FILENO);
	close(pipein[0]);
	close(pipeout[0]);
	res = ft_execchar(command, envp);
	return(res);
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


int **pipe_generator(int npipes)
{
	int **to_return;
	int ct;

	to_return = (int **)ft_calloc(npipes,sizeof(int *));
	if (to_return == 0)
		return (0);
	ct = 0;
	while (ct < npipes)
	{
		to_return[ct] = ft_calloc(2, sizeof(int));
		if (to_return[ct] == 0)
			break;
		ct++;
	}
	if (ct == npipes)
	{
		while (ct-- > 0)
			pipe(to_return[ct]);
		return(to_return);
	}
	else
		while (ct-- > 0)
			free(to_return[ct]);
	return (free(to_return),(int **)0);
}

# if 0
int	main(int argc, char **argv, char**envp)
{
	int		id;
	int		**pipes;
	int		ct;

	if (argc < 5)
		return (1);
	pipes = pipe_generator(argc - 2);
	ct = 0;
	while (ct < argc - 2)
	{
		pipe(pipes[ct]);
		ct++;
	}
	dup2(open(argv[1], O_RDONLY), pipes[0][1]);
	dup2(open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC , 0777), pipes[argc - 3][0]);
	if (pipes[0][1] == -1 || pipes[argc - 3][0] == -1)
	{
		return (2);
	}
	ct = 2;
	while (ct < argc - 1)
	{
		id = fork();
		if (id == 0)
			kid_stuff(argv[ct], pipes[ct-2], pipes[ct-1], envp);
		ct++;
	}
	waitpid(id, &ct, 0);
	return (ct);
}

#endif 

#if 0

int	main(int argc, char **argv, char**envp)
{
	int		id;
	int		pipes[2];
	int		ct;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	pipe(pipes);
	dup2(fd, pipes[0]);
	ct = 2;
	id = fork();
	if (id == 0)
	{
		close(pipes[1]);
		dup2(pipes[0],STDIN_FILENO);
		close(pipes[0]);
		ft_execchar("cat", envp);
	};
	ct++;
	waitpid(id, &ct, 0);
	return (ct + 0 * argc * (int)argv[0][0]);
}
#endif





# if 1
int	main(int argc, char **argv, char**envp)
{
	int		id;
	int		**pipes;
	int		ct;
	int 	a;
	int b;

	//char **test = argv_generator("esto es una prueba 'para ver como' funciona 'esta manda'");

	

	if (argc < 5)
		return (1);
	pipes = pipe_generator(3);
	a = open(argv[1], O_RDONLY);
	b = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC , 0644);
	if (a == -1 || b == -1)
		return 2;
	dup2(a, pipes[0][0]);
	dup2(b, pipes[2][1]);
	if (pipes[0][1] == -1 )
	{
		return (2);
	}
	ct = 2;
	while (ct < 4)
	{
		id = fork();
		if (id == 0)
			exit(kid_stuff(argv[ct],pipes[ct - 2], pipes [ct -1], envp));
		ct++;
	}
	ct = 0;
	while (ct < 3)
	{
		close(pipes[ct][1]);
		close(pipes[ct][0]);
		ct++;
	}
	close(a);
	close(b);
	waitpid(id,&ct,0);
	return (ct);
}

#endif 
