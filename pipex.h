/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:54:00 by amejia            #+#    #+#             */
/*   Updated: 2023/03/15 22:43:04 by amejia           ###   ########.fr       */
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

int		ft_execchar(char *command, char **envp);
char	**argv_generator(char *command);
void	argv_generator_ap(char *command, t_list **argv_args);

#endif