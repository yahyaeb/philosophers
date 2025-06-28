/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_all_digits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 08:53:01 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/06/20 09:41:17 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_all_digits(char *str)
{
	int i;

	i = 0;
	printf("Validating string: %s\n", str);
	if(str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return 0;
	while(str[i])
	{
		if(!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return 1;
}