/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-e <bbento-e@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:15:25 by bbento-e          #+#    #+#             */
/*   Updated: 2024/05/02 16:42:42 by bbento-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*dollar_finder(char *args)
{
	int		i;
	int		size;
	int		last;
	char	*str;
	char	*tmp1;

	str = NULL;
	size = (int)ft_strlen(args);
	i = 0;
	last = 0;
	while (i < size)
	{
		tmp1 = NULL;
		if (args[i] == '$')
		{
			if (args[i + 1] == '?')
				tmp1 = ft_itoa(mini_shell()->exit_status);
			else
			{
				last = i;
				while (args[++i] && ft_isalpha(args[i]) == 1);
				tmp1 = ft_get_env(ft_substr(args, last, i));
			}
			str = ft_strjoin(str, tmp1);
		}
		else
		{
			tmp1 = ft_strjoin(tmp1, &args[i]);
			if (i == 0)
				str = ft_strdup(tmp1);
			else
				ft_strlcat(str, tmp1, ft_strlen(tmp1));
		}
		free(tmp1);
		i++;
	}
	return (str);
}

char	*hexpand(char *args)
{
	char	*str;

	str = ft_strdup(dollar_finder(args));
	free(args);
	return (str);
}

void	hreader(char *args)
{
	int		fd;
	char	*input;

	fd = open("heredoc", O_WRONLY | O_CREAT | O_APPEND, 0666);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			printf("\n");
			break ;
		}
		else if (ft_strcmp(input, args) == 0)
		{
			free(input);
			break ;
		}
		input = hexpand(input);
		ft_putendl_fd(input, fd);
		free(input);
	}
	close(fd);
}

int	heredoc(char *args)
{
	heredoc_signals();
	if (mini_shell()->fd_in > STDIN_FILENO)
		close(mini_shell()->fd_in);
	if (!fork())
		hreader(args);
	ignore_signals();
	waitpid(0, NULL, 0);
	signals();
	return (open("heredoc", O_RDONLY));
}
