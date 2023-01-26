/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 00:19:30 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 23:05:31 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src.h"

int	check_access(char *path)
{
	struct stat	inf;
	mode_t		mode;

	stat(path, &inf);
	mode = inf.st_mode;
	if (S_ISDIR(mode))
		return (IS_DIR);
	else if (S_ISREG(mode))
		return (IS_FILE);
	return (IS_NOTHING);
}
