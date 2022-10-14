/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:34:48 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/14 17:35:16 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	search_closing_quote(t_lex *lexer, char *quote)
{
	while (lexer)
	{
		if (!ft_strcmp(lexer->content, quote))
			return (1);
		lexer = lexer->next;
	}
	return (0);
}

int	concat_quotes(t_lex **lexer)
{
	char	quote[2];

	ft_strlcpy(quote, (*lexer)->content, 2);
	if (!search_closing_quote((*lexer)->next, quote))
	{
		printf("ERROR\n");		
		return (0);
	}
	while (ft_strcmp((*lexer)->next->content, quote))
	{
		(*lexer)->content = ft_strjoin_free((*lexer)->content, (*lexer)->next->content);
		if (!(*lexer)->content)
			return (-1);
		ft_lstdelone_lex((*lexer)->next);
	}
	(*lexer)->content = ft_strjoin_free((*lexer)->content, (*lexer)->next->content);
	if (!(*lexer)->content)
		return (-1);
	ft_lstdelone_lex((*lexer)->next);
	return (1);
}

int	concat_lexer(t_data *data)
{
	int		return_value;
	
	while (data->lexer)
	{
		if (!ft_strcmp(data->lexer->content, "\'")
			|| !ft_strcmp(data->lexer->content, "\""))
		{
			return_value = concat_quotes(&(data->lexer));
			if (return_value == -1)
				free_all_and_exit(data, "malloc");
			else if (return_value == 0)
				return (0);
		}
		else if (!ft_strcmp(data->lexer->content, "&")
					||!ft_strcmp(data->lexer->content, "|")
					||!ft_strcmp(data->lexer->content, "<")
					||!ft_strcmp(data->lexer->content, ">"))
		{
			return_value = concat_quotes(&(data->lexer));
			if (return_value == -1)
				free_all_and_exit(data, "malloc");
			else if (return_value == 0)
				return (0);
		}
		// else if (ENV)
		data->lexer = (data->lexer)->next;
	}
	return (1);
}

void	get_lexer(t_data *data)
{
	data->lexer = NULL;
	data->lexer = ft_lstsplit_charset_lex(data->prompt, "><&|() \t$\'\"");
	if (!data->lexer)
		free_all_and_exit(data, "malloc");
	data->start_lex = data->lexer;
	if (!concat_lexer(data))
		free_lexer_struct(&(data->start_lex));
	data->lexer = data->start_lex;
}
