/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 02:47:12 by jaqribei          #+#    #+#             */
/*   Updated: 2023/11/16 20:27:11 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_confirmation_received;

void	send_signal(int pid, unsigned char c)
{
	unsigned char	bit;
	int				index;

	index = 8;
	while (index > 0)
	{
		g_confirmation_received = 0;
		index--;
		bit = c >> index;
		if (bit % 2 == 1)
		{
			kill(pid, SIGUSR1);
			while (g_confirmation_received == 0)
				;
		}
		else
		{
			kill(pid, SIGUSR2);
			while (g_confirmation_received == 0)
				;
		}
	}
}

void	receive_signal(int signal, siginfo_t *info, void *context)
{
	int	pid;

	(void)context;
	pid = info->si_pid;
	if (signal == SIGUSR1 || signal == SIGUSR2)
		g_confirmation_received = 1;
	else
		exit(ft_printf("Error: Invalid signal received\n"));
}

int	main(int argc, char *argv[])
{
	struct sigaction	action;
	sigset_t			set;
	int					pid;
	int					index;

	ft_check_parameters(argc, argv[1], argv[2]);
	sigemptyset(&set);
	action.sa_handler = NULL;
	action.sa_mask = set;
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = receive_signal;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	pid = ft_atoi(argv[1]);
	index = 0;
	while (argv[2][index] != '\0')
	{
		send_signal(pid, argv[2][index]);
		index++;
	}
	g_confirmation_received = 0;
}

void	ft_check_parameters(int argc, char argv1[], char argv2[])
{
	int	index;

	if (argc != 3)
		exit(ft_printf("Error: Wrong number of arguments\n"));
	index = 0;
	while (argv1[index] != '\0')
	{
		if (!ft_isdigit(argv1[index]))
			exit(ft_printf("Error: Invalid PID\n"));
		index++;
	}
	if (ft_atoi(argv1) < 0)
		exit(ft_printf("Error: Invalid PID\n"));
	else if (!argv2)
		exit(ft_printf("Error: Empty string\n"));
}
