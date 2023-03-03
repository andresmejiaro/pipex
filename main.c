/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 23:59:25 by amejia            #+#    #+#             */
/*   Updated: 2023/03/03 04:00:01 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int dad_stuff(char **argv, int* pipe1)
{

    char *part;
    char *whole;
   
    wait(NULL);
    close(pipe1[1]);

    whole =ft_calloc(1,1);    
    while (part != NULL){
        part = get_next_line(pipe1[0]);
        if (part != NULL)
            whole =ft_strjoin(whole,part);
    }
    
    ft_printf("%s", whole, argv[1]);
    return (0 );
     
}

int kid_stuff(char **argv, int* pipe1)
{
    close(pipe1[0]);
  
    dup2(pipe1[1], STDOUT_FILENO);
    close(pipe1[0]);
    execve("$PATH/cat",argv,NULL);
    return (0);    
}

int main(int argc, char **argv)
{
    int id;
    int pipe1[2];

    if (pipe(pipe1) == -1)
        return(ft_printf("Error\n"), 0);
    id = fork();
    if (id == -1)
        return(ft_printf("Error\n"), 0);
    if (id != 0)
        dad_stuff(argv, pipe1);
    else
        kid_stuff(argv, pipe1);
    return (0 * argc);
}
