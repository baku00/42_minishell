/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 01:45:48 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/31 00:45:45 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

void	wait_all_pid(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->pid != 0)
		{
			waitpid(cmd->pid, &g_status, 0);
			if (WIFSIGNALED(g_status))
				g_status = 128 + g_status;
			if (WIFEXITED(g_status))
				g_status = WEXITSTATUS(g_status);
		}
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
}

void	close_all_fd(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
}

/* t_cmd	*create_cmd(t_cmd *prev, t_string *line, int i, t_env *env)
// {
// 	t_cmd		*cmd;
// 	t_string	*current_arg;
// 	int			parse_string;

// 	if (!prepare_creation(&cmd, &current_arg, prev))
// 		return (NULL);
// 	// cmd = init_cmd(prev);
// 	// if (!cmd)
// 	// 	return (NULL);
// 	// current_arg = create_string("");
// 	// if (!current_arg)
// 	// 	return (free_all_cmd(cmd));
// 	while (i < line->length)
// 	{
// 		if (is_string_separator(line->value[i]))
// 		{
// 			parse_string = parse_string_separator(env, &current_arg, line, &i);
// 			if (parse_string != SUCCESS)
// 			{
// 				free_string(current_arg);
// 				return (parse_error(parse_string));
// 			}
// 		}
// 		else if (is_redirection(line->value[i], line->value[i + 1]))
// 		{
// 			cmd->redirection_id =
// 			redirection_id(line->value[i], line->value[i + 1]);
// 			break ;
// 		}
// 		else if (is_dollars(line->value[i]))
// 			i += get_dollar(line, i, &current_arg, env);
// 		else
// 		{
// 			if (line->value[i] == ' ')
// 			{
// 				if (!cmd->bin)
// 					cmd->bin = string_dup(current_arg);
// 				if (!append_full_args(&cmd->args, &current_arg))
// 					return (NULL);
// 				i = skip_space(line, i);
// 				continue;
// 			}
// 			append_char(&current_arg, line->value[i]);
// 		}
// 		i++;
// 	}
// 	append_current_arg(&cmd, current_arg);
// 	free_string(current_arg);
// 	if (i < line->length && is_redirection(line->value[i + 1], 0))
// 		i++;
// 	if (i + 1 < line->length)
// 		cmd->next = create_cmd(cmd, line, skip_space(line, i + 1), env);
// 	return (cmd);
// }

// append_current_arg(&cmd, current_arg);
// if (current_arg->length)
// {
// 	if (!cmd->bin)
// 	{
// 		cmd->bin = string_dup(current_arg);
// 		append_args(&cmd->args, current_arg);
// 	}
// 	else
// 		append_args(&cmd->args, current_arg);
// }
/////*/
static void	execute_cmd(t_cmd *cmd, t_env **env)
{
	int		pid;

	cmd = get_info_first(cmd);
	while (cmd)
	{
		if (get_string_length(cmd->bin))
		{
			if (is_builtins(cmd->bin))
				exec_builtins(cmd, env);
			else
			{
				pid = fork();
				if (pid == 0)
					exec_bin(cmd, env);
				else
				{
					close_cmd_fd(cmd);
					cmd->pid = pid;
				}
			}
		}
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	wait_all_pid(get_info_first(cmd));
}

void	free_full(t_minishell *minishell)
{
	t_info	*cmd = get_minishell_info_cmd(minishell);
	t_info	*cmd_args = get_minishell_info_cmd_args(minishell);
	t_info	*configured = get_minishell_info_configured(minishell);
	t_info	*configured_args = get_minishell_info_configured_args(minishell);

	free_all_cmd(get_info_first(minishell->cmd));
	minishell->cmd = NULL;
	free_all_cmd(get_info_first(minishell->configured));
	minishell->configured = NULL;

	reset_info(cmd);
	reset_info(cmd_args);
	reset_info(configured);
	reset_info(configured_args);
}

void	debug_cmd(t_cmd *cmd)
{
	t_args	*args;

	printf("Bin: %s\n", get_string(cmd->bin));
	args = cmd->args;
	while (args->next)
	{
		printf("Args: %s\n", get_string(args->string));
		args = args->next;
	}
	printf("Args: %s\n", get_string(args->string));
	if (cmd->next)
		debug_cmd(cmd->next);
}

void	execute(void *minishell_ptr, void *line, void **void_env)
{
	t_minishell	*minishell;
	t_env		**env;
	t_cmd		*cmd_error;
	int			success;

	env = (t_env **) void_env;
	success = 0;
	minishell = (t_minishell *) minishell_ptr;
	minishell->cmd = create_cmd(NULL, (t_string *)line, 0, *env);
	if (!minishell->cmd)
		return ;
	make_info(minishell->cmd, \
	get_minishell_info_cmd(minishell), get_minishell_info_cmd_args(minishell));
	cmd_error = check_error(get_minishell_info_cmd(minishell)->first);
	if (cmd_error)
	{
		print_error_redirection(cmd_error);
		free_all_cmd(get_info_first(minishell->cmd));
		minishell->cmd = NULL;
		return ;
	}
	minishell->configured = \
	make_redirection(NULL, get_minishell_info_cmd(minishell)->first, &success);
	// debug_cmd(minishell->configured);
	if (success)
	{
		free_full(minishell);
		return (print_redirection_error(success));
	}
	make_info(minishell->configured, get_minishell_info_configured(minishell), \
	get_minishell_info_configured_args(minishell));
	execute_cmd(minishell->configured, env);
	free_full(minishell);
}
