/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 09:49:08 by vicmarti          #+#    #+#             */
/*   Updated: 2020/11/30 13:50:32 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
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
/*
static void		add_element(t_scene scn, char **element)
{
//	if (ft_strcmp(element[0], "R"))
//			add_resolution(scn, element);
	strfind(element[0], (char **)g_identifiers);
}*/
/*
static int		check_conf(t_scene scn)
{
	return (0);
}*/
/*
**	
*/

static void			store_element(t_scene *pscn, char **elem)
{
	if (ft_strcmp(elem[0], "R"))
		store_resolution(pscn, elem);
		/*
	else if (ft_strcmp(elem[0], "A")
		store_ambient(elem);*/
	else
		return ; //TODO: Error management.
}


/*
**	Dissects a config line's element in its parts.
**	Stores the element.
*/

static void			line_store(t_scene *pscn, char *line)
{
	char	**element;
	int		i;

	printf("FULL|%s|\n", line);
	if (!(element = ft_split(line, ' ')))
		return ; //TODO:Error handling.
	i = 0;
	while (element[i])
		printf("SPLIT|%s|\n", element[i++]);
	if (!(ft_strcmp(element[0], "")))
		store_element(pscn, element);
	i = 0;
	while (element[i])
		free(element[i++]);
	free(element);
}


/*
**	Read from the given config file to set up the scene.
**	Stores scene information.
**	Checks for configuration errors.
*/

void				save_conf(char *conf_file, t_scene *scn)
{
	char	*line;
	int		fd;
	int		gnl_out;

	line = NULL;
	gnl_out = 0;
	fd = open(conf_file, O_RDONLY);
	while (gnl_out != -1)
	{
		gnl_out = get_next_line(fd, &line);
		if (gnl_out == 0)
			close(fd);
		else if (line[0] != '\0')
			line_store(scn, line);
		free(line);
	}
	/*if (!check_conf(*scn))
		return (1); //TODO:Error handling.*/
}
