/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 00:19:30 by my_name_          #+#    #+#             */
/*   Updated: 2023/03/06 00:54:33 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src.h"

int	check_access(char *path)
{
	struct stat	inf;

	inf.st_mode = 0;
	lstat(path, &inf);
	if (S_ISDIR(inf.st_mode))
		return (IS_DIR);
	else if (S_ISREG(inf.st_mode))
		return (IS_FILE);
	return (IS_NOTHING);
}
