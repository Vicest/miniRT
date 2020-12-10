/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 09:49:08 by vicmarti          #+#    #+#             */
/*   Updated: 2020/12/10 11:03:40 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "minirt.h"
#include "debug.h"

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
**	Calls for a storage function based on the element identifier to store.
*/

static void			store_element(t_scene *pscn, char **elem)
{
	if (0 == ft_strcmp(elem[0], "R"))
		store_resolution(pscn, elem);
	else if (0 == ft_strcmp(elem[0], "A"))
		store_ambient(pscn, elem);
	else if (0 == ft_strcmp(elem[0], "c"))
		store_camera(pscn, elem);
	else if (0 == ft_strcmp(elem[0], "l"))
		store_light(pscn, elem);
	else if (0 == ft_strcmp(elem[0], "sp"))
		store_sphere(pscn, elem);
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

	if (!(element = ft_split(line, ' ')))
		exit(-1); //TODO:Error handling.
	if (0 != ft_strcmp(element[0], ""))
		store_element(pscn, element);
	i = 0;
	while (element[i])
		free(element[i++]);
	free(element);
}

/*
**	Checks if the last part of a string is the same as the given one.
**	Returns NULL if false. Returns the extension.
*/

static char			*file_extension_check(char *file, char *ext)
{
	int		name_length;
	int		ext_length;

	if (!file || !ext)
		exit(-1); //TODO: Errors plox
	name_length = ft_strlen(file);
	ext_length = ft_strlen(ext);
	if ((name_length - ext_length) > 0)
	{
		file += name_length - ext_length;
		if (0 == ft_strcmp(ext, file))
			return (ext);
		else
			return (NULL);
	}
	else
		return (NULL);
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
	if (!file_extension_check(conf_file, ".rt"))
		exit(-1);
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
	print_scene(*scn);
	/*if (!check_conf(*scn))
		return (1); //TODO:Error handling.*/
}