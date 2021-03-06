/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binfuncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatiush <mmatiush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 15:38:47 by vmorguno          #+#    #+#             */
/*   Updated: 2018/11/13 22:48:01 by mmatiush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

short				ft_binvalidator(int fd)
{
	unsigned int	mgc_sz;
	int				res;

	res = read(fd, &mgc_sz, 4);
	mgc_sz = ft_swapuint(mgc_sz);
	if ((mgc_sz == COREWAR_EXEC_MAGIC) && res > 0)
	{
		if (lseek(fd, 136, SEEK_SET) == 136)
		{
			res += read(fd, &mgc_sz, 4);
			mgc_sz = ft_swapuint(mgc_sz);
			return (ft_validchamp(fd, mgc_sz, res));
		}
		return (-4);
	}
	return (-3);
}

short				ft_validchamp(int fd, unsigned int mgc_sz, int res)
{
	union u_chmp_exec	chmpexec;
	int					a;

	a = 0;
	if (mgc_sz <= CHAMP_MAX_SIZE && lseek(fd, 2052, SEEK_CUR) == 2192 & res > 4)
	{
		while ((a = read(fd, &chmpexec, 4)))
			res += a;
		if (res - 8 == (int)mgc_sz)
		{
			lseek(fd, 4, SEEK_SET);
			return (0);
		}
	}
	return (-5);
}

void				ft_binreader(int fd, t_champ *champs)
{
	if (lseek(fd, 0, SEEK_CUR) != 4)
		lseek(fd, 4, SEEK_SET);
	read(fd, champs->name, PROG_NAME_LENGTH + 4);
	read(fd, &(champs->execsize), 4);
	champs->execsize = ft_swapuint(champs->execsize);
	read(fd, champs->comm, COMMENT_LENGTH + 4);
	read(fd, champs->exec.obts, champs->execsize);
	close(fd);
}

int					ft_get_champ_num(t_prog *p, int num)
{
	int	i;

	i = 0;
	while (i < p->players)
	{
		if (p->player_nbr[i] == num)
			return (i);
		i++;
	}
	return (-1);
}
