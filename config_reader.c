/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 09:49:08 by vicmarti          #+#    #+#             */
/*   Updated: 2020/11/24 11:40:57 by vicmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



void	add_element(t_scene scn, char **element)
{
	


/*
**	Read from the given config file to set up the scene.
**	Checks for configuration errors.
*/

int		save_conf(int conf_fd, t_scene scn)
{
	char	*line;
	char	**element;
	int		i;

	while (0 < get_next_line(conf_fd, &line))
	{
		if (!(element = ft_split(line, ' ')))
			return (1); //TODO:Error handling.
		add_element(scn, element);
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
