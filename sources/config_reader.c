/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 09:49:08 by vicmarti          #+#    #+#             */
/*   Updated: 2021/02/28 18:47:01 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "minirt.h"
#include "debug.h"

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
	else if (0 == ft_strcmp(elem[0], "pl"))
		store_plane(pscn, elem);
	else if (0 == ft_strcmp(elem[0], "cy"))
		store_cylinder(pscn, elem);
	else if (0 == ft_strcmp(elem[0], "tr"))
		store_triangle(pscn, elem);
//	else if (0 == ft_strcmp(elem[0], "sq"))
//		store_square(pscn, elem);
	else
		config_err("Invalid item identifier found.\n");
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
		config_err("Could not split.\n");
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

static char			*file_extension_check(char *path, char *ext)
{
	//TODO: Filter out directories to only evaluate the file name.
	int		name_length;
	int		ext_length;

	name_length = ft_strlen(path);
	ext_length = ft_strlen(ext);
	if ((name_length - ext_length) > 0)
	{
		path += name_length - ext_length;
		if (0 == ft_strcmp(ext, path))
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
		config_err("Invalid configuration file extension.\n");
	fd = open(conf_file, O_RDONLY);
	if (fd < 0)
		config_err("Could not open file\n");
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
