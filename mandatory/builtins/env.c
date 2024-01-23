/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofilipe <jofilipe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:11:57 by bbento-e          #+#    #+#             */
/*   Updated: 2024/01/16 15:00:13 by jofilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*vai buscar o user e o lugar onde se encontra nas
variaveis de ambiente*/

void	minienv(t_list *env_amb_list)
{
	(void)env_amb_list;
	int i = -1;
	while(mini_shell()->env[i])
		printf("%s\n",mini_shell()->env[++i]);
}

void	get_prompt(t_mini_env *envp)
{
	char	*env = NULL;
    char    *user = NULL;
    char    *sesh = NULL;
	int		i;
	int		a;

    i = ft_strlen(getcwd(0, 0));
	user = ft_get_env("USER");
	a =  ft_strlen(user);
	sesh = "minishell";
    env = ft_strjoin(env, user);
    env = ft_strjoin(env, "@");
    env = ft_strjoin(env, sesh);
    env = ft_strjoin(env, ":~");
    env = ft_strjoin(env, ft_substr(ft_strnstr(getcwd(0, 0), user, i), a, i));
	//mini_shell()->prompt = ft_strjoin(env, "/$ ");
    envp->prompt = ft_strjoin(env, "/$ ");
	free(env);
    free(user);
    //free(sesh);
}

void	env_update(void)
{
	char *tmp;

	list_delete(mini_shell()->path);
	list_delete(mini_shell()->env);
	tmp = ft_get_env("PATH");
	mini_shell()->path = ft_split(tmp, ':');
	mini_shell()->env = env_to_mat(mini_shell()->env_amb_list);
	free(tmp);
}

char	**env_to_mat(t_list *env_list)
{
	t_env   *env;
	char	*tmp1;
	char	*tmp2;
	char	**matrix;

	matrix = ft_calloc(1, sizeof(char *));
	if(!matrix)
		return(NULL);
	while(env_list)
	{
		env = (t_env *)env_list->content;
		tmp1 = ft_strjoin(env->type, "=");
		tmp2 = ft_strjoin(tmp1, env->info);
		matrix = add_to_mat(matrix, ft_strdup(tmp2));
		free(tmp1);
		free(tmp2);
		env_list = env_list->next;
	}
	return (matrix);
}

char	*ft_get_env(char *type)
{
	t_env	*env_tmp;
	t_list	*current;

	//In many shell and scripting languages, environment variables are often referenced
	//with a $ symbol before the variable name.
	//For example, in a bash shell, you might access the PATH environment variable with $PATH.
	if(type[0] == '$')
		type++;
	current = mini_shell()->env_amb_list;
	while (current)
	{
		env_tmp = (t_env *)current->content;
		if (!ft_strcmp(env_tmp->type, type))
			return (ft_strdup(env_tmp->info));
		current = current->next;
	}
	return (ft_strdup(""));
}