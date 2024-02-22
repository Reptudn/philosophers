/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intra <intra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:40:18 by intra             #+#    #+#             */
/*   Updated: 2024/02/22 09:41:44 by intra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	input_invalid(char argc, char **argv)
{
	if (argc < 5 || argc > 6 || !is_all_numbers(argv))
	{
		printf("%sUsage: ./philo number_of_philosophers time_to_die \
		time_to_eat time_to_sleep  \
		[number_of_times_each_philosopher_must_eat%s\n",
			COLOR_RED, COLOR_RESET);
		return (1);
	}
	return (0);
}
