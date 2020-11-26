/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 09:49:08 by vicmarti          #+#    #+#             */
/*   Updated: 2020/11/26 09:55:43 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minirt.h"

/*
**	TODO: Libft??
**	Looks for a string in a null-terminated list of strings.
*/

int				strfind(char *elem, char **list)
{
	int		pos;

	pos = 0;
	if (!list || !elem)
		return (-1);
	while (list[pos] && 0 != ft_strcmp(elem, list[pos]))
			pos++;
	return (list[pos] != NULL ? pos : -1);
}

static void		add_element(t_scene scn, char **element)
{
//	if (ft_strcmp(element[0], "R"))
//			add_resolution(scn, element);
	strfind(element[0], (char **)g_identifiers);
}

static int		check_conf(t_scene scn)
{
	return (0);
}

/*
**	Read from the given config file to set up the scene.
**	Checks for configuration errors.
*/

int				save_conf(char *conf_file, t_scene scn)
{
	char	*line;
	char	**element;
	int		fd;
	int		i;

	if (-1 == (fd = open(conf_file, O_RDONLY)))
		return (-1); //TODO: Errors
	while (0 < get_next_line(fd, &line))
	{
		if (!(element = ft_split(line, ' ')))
			return (1); //TODO:Error handling.
		//add_element(scn, element);
		i = 0;
		while (element[i])
			free(element[i++]);
		free(element);
		free(line);
	}
	if (!check_conf(scn))
		return (1); //TODO:Error handling.
	return (0);
}
