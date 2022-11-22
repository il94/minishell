/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:42:47 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/22 23:07:30 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status;

void	minishell_test(t_data *data, char **av)
{
	t_lex	*new;
	t_lex	*lst;

	while (1)
	{
		data->prompt = readline("\x1b[33msalam khey> \x1b[0m");
		if (!ft_strcmp(data->prompt, "stop"))
		{
			free(data->prompt);
			data->prompt = NULL;
			break ;
		}
		if (data->prompt[0] != '\0')
		{	
			add_history(data->prompt);
			get_lexer(data);
			// ft_lstprint_lex(data->lexer);
			if (data->lexer)
			{
				lexer(data);
				parser(data, data->commands, 0);
				if (!g_exit_status)
					print_cmd(data->commands, "PARENT");
			}
			if (!ft_strncmp(data->prompt, "echo", 4))
				echo(data->commands->args);
			else if (!ft_strncmp(data->prompt, "cd", 2))
				cd(data, data->commands->args);
			else if (!ft_strncmp(data->prompt, "pwd", 3))
				pwd(data->commands->args);
			else if (!ft_strncmp(data->prompt, "env", 3))
				env(data, data->commands->args);
			else if (!ft_strncmp(data->prompt, "export", 6))
				exporc(data, data->commands->args);
			else if (!ft_strncmp(data->prompt, "unset", 5))
				unset(data, data->commands->args);
			else if (!ft_strncmp(data->prompt, "exit", 4))
				ixit(data, data->commands->args);
			g_exit_status = 0;
		}
		free_data_struct(data);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	g_exit_status = 0;
	initialize_data(&data, envp);
	// minishell(&data);
	minishell_test(&data, av);
	if (data.start_env)
		free_lexer_struct(&data.start_env);
	free_data_struct(&data);
	return (0);
}
