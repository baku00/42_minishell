/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:41:17 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 22:50:02 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H
# include "../class.h"

void		*free_string(t_string *string);
t_string	*create_string(char *str);
int			get_string_length(t_string *str);
char		*get_string(t_string *str);
int			equals_string(t_string *str1, t_string *str2);
int			compare_string(t_string *str1, t_string *str2);
int			is_string_separator(char c);
int			is_apostrophe(char c);
int			is_guillemet(char c);
int			append_char(t_string **string, char c);
void		print_string(t_string *str);
t_string	*extract_string_into(char *str, char c, int *i);
int			append_string(t_string **string, t_string *append);
t_string	*string_dup(t_string *string);
int			str_replace(char **str, char *needed, char *handle);
int			append_front_char(t_string **string, char c);
void		replace_variable_name(t_string **s, t_string *h, t_string *r);
int			equals_string_to_char(t_string *str, char *c);
int			append_front_string(t_string **string, t_string *append);
int			remove_char(t_string **string, int i);
#endif
