/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 01:45:48 by my_name_          #+#    #+#             */
/*   Updated: 2023/03/06 00:14:42 by my_name_         ###   ########.fr       */
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
static void	execute_cmd(t_minishell *minishell, t_cmd *cmd, t_env **env)
{
	int		pid;

	cmd = get_info_first(cmd);
	while (cmd)
	{
		if (is_builtins(cmd->bin))
			exec_builtins(minishell, cmd, env);
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
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	wait_all_pid(get_info_first(cmd));
}

void	debug_cmd(t_cmd *cmd)
{
	t_args	*args;

	printf("Bin: %s\n", get_string(cmd->bin));
	printf("Heredoc file: %s\n", get_string(((t_heredoc *)cmd->heredoc)->file));
	args = cmd->args;
	if (args)
	{
		while (args->next)
		{
			printf("Args: %s\n", get_string(args->string));
			args = args->next;
		}
		printf("Args: %s\n", get_string(args->string));
	}
	if (cmd->next)
		debug_cmd(cmd->next);
}

void	execute(t_minishell **mini, t_string *line, t_env **env)
{
	t_cmd		*cmd_error;
	int			success;

	(void) line;
	success = 1;
	(*mini)->cmd = create_cmd(NULL, line, 0, *env);
	if (!(*mini)->cmd)
		return ;
	make_info((*mini)->cmd, \
	get_minf_cmd((*mini)), get_minishell_info_cmd_args((*mini)));
	cmd_error = check_error(get_minf_cmd((*mini))->first);
	if (cmd_error)
	{
		print_error_redirection(cmd_error);
		free_all_cmd(get_info_first((*mini)->cmd));
		(*mini)->cmd = NULL;
		return ;
	}
	(*mini)->configured = \
	make_redirection(NULL, get_minf_cmd((*mini))->first, &success, (*mini)->fd);
	if (success != 1 || !(*mini)->configured)
		return (print_redirection_error(success));
	make_info((*mini)->configured, get_minishell_info_configured((*mini)), \
	get_minishell_info_configured_args((*mini)));
	return (execute_cmd((*mini), (*mini)->configured, env));
}
