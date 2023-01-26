/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:15:34 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 22:44:38 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

static void	void_args(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
}

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
	rl_on_new_line();
}

void	use_signal(void)
{
	signal(SIGQUIT, pass);
	signal(SIGINT, call_prompt);
}

static t_string	*prompt(char *display)
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
	t_string	*line;
	t_info		env_info;
	t_env		*env;

	g_status = 0;
	env_info = create_info(NULL, NULL);
	env = generate_env(NULL, &env_info, envp, 0);
	if (!env)
		return (1);
	create_exit_manager();
	if (have_to_exit())
		return (1);
	env = get_info_first(env);
	void_args(argc, argv, envp);
	while (!have_to_exit())
	{
		env = get_info_first(env);
		use_signal();
		line = prompt("Minishell: ");
		if (!line)
		{
			set_have_to_exit(1);
			break ;
		}
		if (equals_string(line, g_exit_manager.string))
			set_have_to_exit(1);
		else if (line->length)
			execute(line, env);
		free_string(line);
	}
	free_all();
	return (0);
}
