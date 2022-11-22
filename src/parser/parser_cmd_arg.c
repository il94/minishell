/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 04:21:02 by auzun             #+#    #+#             */
/*   Updated: 2022/11/22 14:31:09 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lex	*parsing_cmd(t_data *data, t_cmd *command, char *cmd)
{
	t_lex	*lst;
	t_lex	*tmp;

	lst = NULL;
	if (!cmd)
		return (NULL);
	if (cmd && (ft_strchr(cmd, '\"') || ft_strchr(cmd, '\'')
			|| ft_strchr(cmd, '$') || ft_strchr(cmd, '*')))
		lst = check_str(data, cmd);
	if (!lst)
		return (NULL);
	free(command->command);
	command->command = ft_strdup(lst->str);
	if (!command->command)
	{
		ft_lstclear_lex(&lst);
		free_all_and_exit(data, "malloc");
	}
	tmp = lst->next;
	ft_lstdelone_lex(lst);
	lst = tmp;
	return (lst);
}

static void	add_el_to_arg(t_lex **el, t_lex **cur, t_lex **args)
{
	t_lex	*tmp;

	if ((*cur)->prev)
		(*cur)->prev->next = (*first_el(el));
	if ((*cur)->next)
		(*cur)->next->prev = (*last_el(el));
	(*first_el(el))->prev = (*cur)->prev;
	(*last_el(el))->next = (*cur)->next;
	if ((*cur)->next)
		*args = *first_el(&(*cur)->next);
	else if ((*cur)->prev)
		*args = *first_el(&(*cur)->prev);
	else
		*args = *el;
	tmp = (*cur)->next;
	if ((*cur)->str)
		free((*cur)->str);
	free(*cur);
	*cur = tmp;
}

static void	add_before_to_args(t_lex *before, t_lex **args, t_lex **lst)
{
	(*args)->prev = (*last_el(&before));
	(*last_el(&before))->next = *args;
	*lst = *args;
	*args = before;
}

static t_lex	*parsing_args(t_data *data, t_cmd *command, \
	t_lex *args, t_lex *before)
{
	t_lex	*lst;
	t_lex	*tmp;
	t_lex	*tmp_arg;

	if (!args && before)
		return (before);
	if (before && args)
		add_before_to_args(before, &args, &lst);
	else
		lst = args;
	tmp_arg = NULL;
	while (lst)
	{
		if (lst && lst->str && (ft_strchr(lst->str, '\"')
				|| ft_strchr(lst->str, '\'') || ft_strchr(lst->str, '$')
				|| ft_strchr(lst->str, '*')))
		{
			tmp_arg = check_str(data, lst->str);
			if (tmp_arg)
				add_el_to_arg(&tmp_arg, &lst, &args);
		}
		else
			lst = lst->next;
	}
	return (args);
}

void	parser_cmd_arg(t_data *data, t_cmd *cmd)
{
	t_lex	*lst_cmd_arg;

	lst_cmd_arg = NULL;
	lst_cmd_arg = parsing_cmd(data, cmd, cmd->command);
	get_all_paths(data);
	if (cmd->args || lst_cmd_arg)
		cmd->args = parsing_args(data, cmd, cmd->args, lst_cmd_arg);
}