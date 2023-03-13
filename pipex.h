/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:54:00 by amejia            #+#    #+#             */
/*   Updated: 2023/03/13 16:12:27 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <sys/wait.h>
# include <stdio.h>
# include "libft/libft.h"
# include <string.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

int 	ft_execchar(char *command, char **envp);
char	**argv_generator(char *command);
int argv_generator_ap(char *command, char lim, t_list **argv_args);


#endif