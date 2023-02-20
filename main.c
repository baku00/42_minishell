/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:15:34 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/17 00:17:19 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

static void	void_args(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
}

static void	init_main(int argc, char **argv, char **envp)
{
	void_args(argc, argv, envp);
}

t_string	*prompt(char *display)
{
	char			*line;
	t_string		*string;
	struct termios	saved;
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &saved);
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
	line = readline(display);
	if (line && ft_strlen(line))
		add_history(line);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);
	string = create_string(line);
	free(line);
	return (string);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;
	t_info		*info;

	init_main(argc, argv, envp);
	minishell = create_minishell();
	if (!minishell)
		return (1);
	info = get_minishell_info_env(minishell);
	minishell->env = generate_env(NULL, info, envp, 0);
	while (1)
	{
		use_signal();
		minishell->line = prompt("Minishell2: ");
		if (!minishell->line)
			break ;
		else if (get_string_length(minishell->line))
		{
			execute(&minishell, minishell->line, &minishell->env);
			reset_minishell(minishell);
		}
		free_string(minishell->line);
	}
	free_minishell(minishell);
	return (0);
}

	// if (1 == 0)
	// {
	// 	t_string	*line;
	// 	t_info		*env_info;
	// 	t_env		*env;

	// 	g_status = 0;
	// 	env_info = create_info();
	// 	env = generate_env(NULL, env_info, envp, 0);
	// 	if (!env)
	// 		return (1);
	// 	create_exit_manager();
	// 	if (have_to_exit())
	// 		return (1);
	// 	env = get_info_first(env);
	// 	void_args(argc, argv, envp);
	// 	while (1)
	// 	{
	// 		env = get_info_first(env);
	// 		use_signal();
	// 		line = prompt("Minishell: ");
	// 		if (!line)
	// 			break ;
	// 		if (equals_string_to_char(line, "exit"))
	// 			break ;
	// 		else if (line->length)
	// 			execute(minishell, line, env);
	// 		free_string(line);
	// 	}
	// 	env_free_all(env);
	// 	free_all();
	// }