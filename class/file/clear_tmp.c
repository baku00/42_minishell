/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_tmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 03:13:49 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/28 20:51:19 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

int	is_valid_filename(char *filename)
{
	if (!ft_strncmp(filename, ".", ft_strlen(filename)))
		return (0);
	else if (!ft_strncmp(filename, "..", ft_strlen(filename)))
		return (0);
	return (1);
}

void	clear_tmp_dir(void)
{
	DIR				*dir;
	struct dirent	*directory;
	t_string		*tmp_dir;
	t_string		*file;

	tmp_dir = create_string(TMP_PATH);
	dir = opendir(tmp_dir->value);
	if (!dir)
		return ;
	directory = readdir(dir);
	if (!directory)
		return (free(tmp_dir));
	file = create_string(directory->d_name);
	append_front_string(&file, tmp_dir);
	while (directory)
	{
		if (is_valid_filename(directory->d_name))
			unlink(file->value);
		directory = readdir(dir);
		if (!directory)
			break ;
		free_string(file);
		file = create_string(directory->d_name);
		append_front_string(&file, tmp_dir);
	}
	free_string(file);
	free_string(tmp_dir);
	closedir(dir);
}
