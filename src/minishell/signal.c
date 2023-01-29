/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:25:57 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 22:20:45 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

/**
 * rl_replace_line(content, start):
 * 		Replace le contenu de la ligne par le content à l'index start
 * 
 * 	rl_on_new_line:
 * 		rewrite a prompt
 * 
 * rl_redisplay:
 * 		redisplay automaticly the prompt
*/
void	call_prompt(int key)
{
	(void)key;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

void	pass(int key)
{
	(void)key;
	call_prompt(key);
}

void	use_signal(void)
{
	signal(EOF, pass);
	signal(SIGINT, call_prompt);
}
