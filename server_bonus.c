/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 02:47:19 by jaqribei          #+#    #+#             */
/*   Updated: 2023/10/26 21:11:43 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	receive_signal(int signal, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				index;

	(void)context;
	if (signal == SIGUSR1)
		c |= 1;
	index++;
	if (index == 8)
	{
		write(1, &c, 1);
		index = 0;
		c = 0;
	}
	c = c << 1;
	if (signal == SIGUSR1)
		kill(info->si_pid, SIGUSR1);
	else if (signal == SIGUSR2)
		kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	lead;
	sigset_t			set;

	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	lead.sa_handler = NULL;
	lead.sa_mask = set;
	lead.sa_flags = SA_SIGINFO;
	lead.sa_sigaction = receive_signal;
	sigaction(SIGUSR1, &lead, NULL);
	sigaction(SIGUSR2, &lead, NULL);
	ft_printf("%d\n", getpid());
	while (1)
		pause();
}
