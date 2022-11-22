/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:10:33 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/07 15:20:56 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	concat_element(t_lex **lexer, t_bool is_prev)
{
	if (is_prev)
		(*lexer) = (*lexer)->prev;
	(*lexer)->str = ft_strjoin_free((*lexer)->str, (*lexer)->next->str);
	if (!(*lexer)->str)
		return (0);
	ft_lstdelone_lex((*lexer)->next);
	return (1);
}

int	is_token(t_lex *element)
{
	return (get_delimiter(element) || get_redi(element));
}

t_redi	get_redi(t_lex *element)
{
	if (!element || !element->str)
		return (NOTHING_R);
	if (!ft_strcmp(element->str, "<"))
		return (L_CHEVRON);
	if (!ft_strcmp(element->str, "<<"))
		return (L_DOUBLE_CHEVRON);
	if (!ft_strcmp(element->str, ">"))
		return (R_CHEVRON);
	if (!ft_strcmp(element->str, ">>"))
		return (R_DOUBLE_CHEVRON);
	if (!ft_strcmp(element->str, "|"))
		return (PIPE_R);
	return (NOTHING_R);
}

t_deli	get_delimiter(t_lex *element)
{
	if (!element || !element->str)
		return (NOTHING_D);
	if (!ft_strcmp(element->str, "|"))
		return (PIPE_D);
	if (!ft_strcmp(element->str, "&&"))
		return (AND);
	if (!ft_strcmp(element->str, "||"))
		return (OR);
	return (NOTHING_D);
}

int	search_closing_quote(t_lex *lexer, char *quote)
{
	while (lexer)
	{
		if (!ft_strcmp(lexer->str, quote))
			return (1);
		lexer = lexer->next;
	}
	return (0);
}

int	search_closing_parenthese(t_lex *lexer)
{
	int		opened;
	int		closed;

	opened = 0;
	closed = 0;
	while (lexer)
	{
		if (lexer->str[0] == '(')
			opened++;
		if (lexer->str[0] == ')')
			closed++;
		if (closed > opened)
			return (0);
		lexer = lexer->next;
	}
	return (closed == opened);
}