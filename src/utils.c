/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:32:14 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/02 13:56:10 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_there(char *str, char in)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (in == str[i])
			return (str[i]);
		i++;
	}
	return (0);
}

int	is_in_quotes(char *start, char *now)
{
	int	i;
	int	quotes;

	i = -1;
	quotes = 0;
	while (start[++i] && &start[i] != now)
	{
		if (!quotes && is_there("\"\'", start[i]))
			quotes = start[i];
		else if (quotes && quotes == start[i])
			quotes = 0;
	}
	return (quotes);
}

int	is_there_wildcard(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '*' && !is_in_quotes(str, &str[i]))
			return (1);
	}
	return (0);
}
