/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 20:59:51 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 02:29:12 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "../builtins.h"

t_env		*generate_env(t_env *prev, t_info *info, char **envp, int i);
t_string	*get_env_key(t_env *env);
t_string	*get_env_value(t_env *env);
t_env		*get_env_from_key(t_env *env, t_string *key, int have_to_free);
t_string	*get_value_env_from_key(t_env *env, t_string *key);
void		set_env_value(t_env **env, t_string *value);
t_env		*init_env(t_string *key, t_string *value);
void		*free_env(t_env *env);
t_string	*get(char *envp, int i, int length);
void		print_env(t_cmd *cmd, t_env *env);
void		exec_env(t_cmd *cmd, t_env *env);
void		sort_env(t_env **env, t_env *src, int last);
t_env		*env_dup(t_env *env);
void		replace_env_value(t_env **env, t_string *value);
void		remove_env(t_env **env);
void		append_env_last(t_env **env, t_env *new);
void		append_env_first(t_env **env, t_env *new);
t_string	*get_entry(t_env *env);
char		**env_to_array(t_env *env);
t_string	*get_home(t_env *env);
t_env		*get_env_from_char_key(t_env *env, char *key_char, int htf);
void		*free_all_env(t_env *env);
t_string	*get_env_value(t_env *env);
t_string	*get_value_env_from_key(t_env *env, t_string *key);
#endif
