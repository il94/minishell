/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:35:28 by ilyes             #+#    #+#             */
/*   Updated: 2022/10/05 14:20:46 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

void	ft_lstclear(t_cmd **lst)
{
	t_cmd	*temp;

	temp = *lst;
	if (lst == NULL)
		return ;
	else
	{
		while (temp != NULL)
		{
			temp = (*lst)->next;
			free(*lst);
			*lst = temp;
		}
	}
}
