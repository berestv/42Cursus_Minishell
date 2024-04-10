/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofilipe <jofilipe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:46:06 by jofilipe          #+#    #+#             */
/*   Updated: 2024/04/10 18:20:16 by bbento-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_built_in(char *command, char *arg)
{
	(void)arg;
	return((!ft_strcmp(command, "echo")) || (!ft_strcmp(command, "cd"))
		|| (!ft_strcmp(command, "pwd")) || (!ft_strcmp(command, "export"))
		|| (!ft_strcmp(command, "unset")) || (!ft_strcmp(command, "env"))
		|| (!ft_strcmp(command, "exit")));
}

bool	is_last_command(int command_numbers)
{
	return (command_numbers == mini_shell()->cmd_num - 1);
}

void	fd_duplicate(void)
{
	if (mini_shell()->fd_in >= STDIN_FILENO)
		dup2(mini_shell()->fd_in, STDIN_FILENO);
	if (mini_shell()->fd_out >= STDOUT_FILENO)
		dup2(mini_shell()->fd_out, STDOUT_FILENO);
}

void	fd_close(int command_index)
{
	if (mini_shell()->fd_in > STDIN_FILENO)
		close(mini_shell()->fd_in);
	if (mini_shell()->fd_out > STDOUT_FILENO)
		close(mini_shell()->fd_out);
	if (command_index > 0)
		close(mini_shell()->pipes[command_index - 1][READ_PI]);
	if (!is_last_command(command_index))
		close(mini_shell()->pipes[command_index][WRITE_PI]);
	mini_shell()->fd_in = STDIN_FILENO;
	mini_shell()->fd_out = STDOUT_FILENO;
}

int	lst_size(t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	free(tmp);
	return (i);
}

int	arr_size(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}