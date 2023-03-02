/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:05:56 by my_name_          #+#    #+#             */
/*   Updated: 2023/03/02 20:29:13 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H
# include "header.h"
# define IS_DIR -10
# define IS_FILE -11
# define IS_NOTHING -12
# define ERROR_NOT_CLOSE_QUOTE -1
# define ERROR_MEMORY -2
# define SUCCESS 1
# define PREMISSION_NOT_FOUND -126
# ifndef TMP_PATH
#  define TMP_PATH "/"
# endif
#endif
