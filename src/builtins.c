/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:59:18 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/10 16:03:57 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Les char **args sont les tableaux d'arguments des structures de commande,
en ayant pour case[0] le premier argument. Donc pour "ls -a", args[0] == -a.*/

/* Faire gaffe au code d'erreur, a bien retourner dans le parent si on est dans
un child et aussi si on retourne 1 ou 0*/

int	echo(t_lex *args) //cas d'erreurs : syntax error donc a gerer avant
{
	t_lex	*start;

	start = args;
	if (args && !ft_strcmp(args->str, "-n"))
		args = args->next;
	while (args && args->str)
	{
		ft_printf("%s", args->str);
		if (args->next)
			ft_printf(" ");
		args = args->next;
	}
	if (!start || (start && ft_strcmp(start->str, "-n")))
		ft_printf("\n");
	return (0);		
}


int	cd(t_lex *args)
{
	if (!args)
	{
		g_exit_status = 1; //code d'erreur a definir
		ft_printf("ERROR : need path in argument\n"); //a paufiner
		return (1);
	}
	if (args->next)
	{
		g_exit_status = 1;
		ft_printf("ERROR : to many arguments\n");	//paufined
		return (1);
	}
	if (!chdir(args->str))
		return (0);
	g_exit_status = 1;
	perror("chdir");
	return (1);
}
/* Cd doit fonctionner qu'avec un chemin relatif ou absolu, donc pas de cd seul
*/

int	pwd(t_lex *args)
{
	ft_printf("%s\n", getcwd(NULL, 0));
	return (0);
}

int	env(t_data *data)
{
	ft_lstprint_lex(data->env);
	return (0);
}

int	exporc(t_data *data, t_lex *args)
{
	t_lex	*element;

	element = ft_lstnew_lex(ft_strdup(args->str));
	if (!element || !element->str)
	{
		// g_exit_status = ?; //code d'erreur a definir
		return (0);
	}
	// ft_lstprint_lex(data->env);
	// printf("==================================================\n");
	ft_lstadd_back_lex(&data->env, ft_lstnew_lex(ft_strdup(args->str)));
	// env(data);
	// env(data);
	// ft_lstadd_back_lex(&data->start_env, NULL);
	return (1);
}