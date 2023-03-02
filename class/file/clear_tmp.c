/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_tmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 03:13:49 by my_name_          #+#    #+#             */
/*   Updated: 2023/03/02 20:16:28 by my_name_         ###   ########.fr       */
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

void	create_tmp_path_file(t_string **file, char *name, t_string *tmp_dir)
{
	t_string	*path;

	*file = create_string(name);
	path = string_dup(tmp_dir);
	append_front_string(file, path);
	free_string(path);
}

int	clear_directory(DIR *dir, t_string *tmp_dir)
{
	struct dirent	*current_file;
	t_string		*file;

	current_file = readdir(dir);
	if (!current_file)
		return (0);
	create_tmp_path_file(&file, current_file->d_name, tmp_dir);
	while (current_file)
	{
		if (is_valid_filename(current_file->d_name))
			unlink(file->value);
		current_file = readdir(dir);
		if (!current_file)
			break ;
		free_string(file);
		file = NULL;
		create_tmp_path_file(&file, current_file->d_name, tmp_dir);
	}
	free_string(file);
	return (0);
}

void	clear_tmp_dir(void)
{
	DIR				*dir;
	t_string		*tmp_dir;

	tmp_dir = create_string(TMP_PATH);
	dir = opendir(tmp_dir->value);
	clear_directory(dir, tmp_dir);
	free_string(tmp_dir);
	closedir(dir);
}
