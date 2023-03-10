/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:54:41 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/30 16:28:25 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNSET_H
# define UNSET_H
# include "../builtins.h"

void	exec_unset(t_env **env, t_args *args);
void	print_invalid_params(t_string *param);
#endif
