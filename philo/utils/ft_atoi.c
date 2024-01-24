/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:58:41 by jkauker           #+#    #+#             */
/*   Updated: 2024/01/22 10:00:14 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\r' || c == '\f'
		|| c == '\v' || c == '\t')
		return (1);
	return (0);
}

int	get_num(const char *nptr, int i)
{
	long	num;

	num = 0;
	while (nptr[i] != 0)
	{
		if (!(nptr[i] >= '0' && nptr[i] <= '9'))
			break ;
		num += nptr[i] - '0';
		num *= 10;
		i++;
	}
	num /= 10;
	return ((int)num);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		prefix;

	i = 0;
	prefix = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			prefix = -1;
		i++;
	}
	if (!(nptr[i] >= '0' && nptr[i] <= '9'))
		return (0);
	return (get_num(nptr, i) * prefix);
}
