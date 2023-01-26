/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 01:45:48 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/26 17:38:36 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

static t_cmd	*init_cmd(t_cmd *prev)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
	{
		set_have_to_exit(1);
		return (NULL);
	}
	cmd->bin = NULL;
	cmd->args = NULL;
	cmd->type = TYPE_CMD;
	cmd->pid = 0;
	cmd->fd_in = STDIN_FILENO;
	cmd->is_file = 0;
	cmd->fd_out = STDOUT_FILENO;
	cmd->error_id = 0;
	cmd->redirection_id = 0;
	cmd->info = NULL;
	cmd->next = NULL;
	cmd->prev = prev;
	return (cmd);
}

static void	wait_all_pid(t_cmd *cmd)
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

static void	close_all_fd(t_cmd *cmd)
{
	cmd = get_info_first(cmd);
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

static void	get_args_cmd(t_cmd **cmd)
{
	t_args	*args;
	t_cmd	*next;

	next = (*cmd)->next;
	args = next->args;
	args = args->next;
	if (args)
		printf("Args: %s\n", get_string(args->string));
	else
		printf("Args: %p\n", NULL);
	while (((t_args *)(*cmd)->args)->next)
		(*cmd)->args = ((t_args *)(*cmd)->args)->next;
	while (args && args->next)
	{
		append_args(&(*cmd)->args, args->string);
		args = args->next;
	}
	if (args)
		append_args(&(*cmd)->args, args->string);
	while (((t_args *)(*cmd)->args)->prev)
		(*cmd)->args = ((t_args *)(*cmd)->args)->prev;
}

void	launch(t_cmd *cmd, t_env *env)
{
	t_cmd	*tmp;

	while (cmd)
	{
		if (cmd->redirection_id)
			redirect_fd(&cmd);
		tmp = cmd;
		while (cmd->redirection_id == REDIRECTION_OUTPUT || \
			cmd->redirection_id == REDIRECTION_APPEND)
		{
			get_args_cmd(&cmd);
			cmd = cmd->next;
		}
		cmd = tmp;
		if (cmd->redirection_id == REDIRECTION_OUTPUT || \
			cmd->redirection_id == REDIRECTION_APPEND)
		{
			if (cmd->next)
			{
				cmd = cmd->next;
				continue ;
			}
			else
				break ;
		}
		if (is_builtins(cmd->bin))
			exec_builtins(cmd, env);
		else
			exec_binary(cmd, env);
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	close_all_fd(cmd);
	wait_all_pid(cmd);
}

int	parse_string_separator(t_env *env, t_string **cmd, t_string *line, int *i)
{
	t_string	*extracted;

	extracted = extract_string_into(line->value, line->value[*i], i);
	if (!extracted)
		return (ERROR_MEMORY);
	if (!line->value[*i])
		return (ERROR_NOT_CLOSE_QUOTE);
	if (is_guillemet(line->value[*i]))
		replace_all_variables(env, &extracted);
	append_string(cmd, extracted);
	free_string(extracted);
	return (SUCCESS);
}

int	skip_space(t_string *line, int i)
{
	while (isspace(line->value[i]))
		i++;
	return (i);
}

void	*parse_error(int parse_string)
{
	if (parse_string == ERROR_NOT_CLOSE_QUOTE)
		ft_putstr_fd("Guillement ou apostrophe non fermé\n", STDERR_FILENO);
	return (NULL);
}

int	get_dollar(t_string *line, int i, t_string **current_arg, t_env *env)
{
	t_string	*extracted;
	t_string	*str_itoa;
	t_string	*tmp;
	char		*itoa;
	int			result;

	extracted = get_variable_name(line, i + 1);
	if (!extracted->length)
	{
		append_char(current_arg, line->value[i]);
		return (0);
	}
	tmp = get_value_env_from_key(env, extracted);
	if (equals_string_to_char(extracted, "?"))
	{
		itoa = ft_itoa(g_status);
		str_itoa = create_string(itoa);
		append_string(current_arg, str_itoa);
		return (ft_strlen(itoa));
	}
	else if (tmp)
		append_string(current_arg, tmp);
	result = get_string_length(extracted);
	return (result);
	
}

t_cmd	*create_cmd(t_cmd *prev, t_string *line, int i, t_env *env)
{
	t_cmd		*cmd;
	t_string	*current_arg;
	int			parse_string;

	cmd = init_cmd(prev);
	if (!cmd)
		return (NULL);
	current_arg = create_string("");
	if (!current_arg)
		return (free_string(current_arg));
	i = skip_space(line, i);
	while (i < line->length)
	{
		if (is_string_separator(line->value[i]))
		{
			parse_string = parse_string_separator(env, &current_arg, line, &i);
			if (parse_string != SUCCESS)
				return (parse_error(parse_string));
		}
		else if (is_redirection(line->value[i], line->value[i + 1]))
		{
			cmd->redirection_id = redirection_id(line->value[i], line->value[i + 1]);
			break ;
		}
		else if (is_dollars(line->value[i]))
			i += get_dollar(line, i, &current_arg, env);
		else
		{
			if (line->value[i] == ' ')
			{
				if (!cmd->bin)
				{
					cmd->bin = string_dup(current_arg);
					append_args(&cmd->args, current_arg);
					free_string(current_arg);
					current_arg = create_string("");
					if (!current_arg)
						return (free_string(current_arg));
				}
				else
				{
					append_args(&cmd->args, current_arg);
					free_string(current_arg);
					current_arg = create_string("");
					if (!current_arg)
						return (free_string(current_arg));
				}
				while (line->value[i] == ' ')
					i++;
				continue ;
			}
			append_char(&current_arg, line->value[i]);
		}
		i++;
	}
	if (current_arg->length)
	{
		if (!cmd->bin)
		{
			cmd->bin = string_dup(current_arg);
			append_args(&cmd->args, current_arg);
			free_string(current_arg);
		}
		else
		{
			append_args(&cmd->args, current_arg);
			free_string(current_arg);
		}
	}
	if (i < line->length && is_redirection(line->value[i + 1], 0))
		i++;
	if (i + 1 < line->length)
		cmd->next = create_cmd(cmd, line, i + 1, env);
	return (cmd);
}

void	print_info(t_info *info)
{
	(void)info;
	printf("===== Info =====\n");
	printf("Length: %d\n", info->length);
	printf("First: %p\n", info->first);
	printf("Last: %p\n", info->last);
}

void	print_cmd(t_cmd *cmd, int i)
{
	t_args	*args;

	for (int j = 0; j < i; j++)
		printf("\t");
	printf("Bin: %s\n", get_string(cmd->bin));
	args = cmd->args;
	for (int j = 0; j < i; j++)
		printf("\t");
	printf("Args:\n");
	while (args->next)
	{
		for (int j = 0; j < i; j++)
			printf("\t");
		printf("\t(%s)\n", get_string(args->string));
		args = args->next;
	}
	for (int j = 0; j < i; j++)
		printf("\t");
	printf("\t(%s)\n", get_string(args->string));
	for (int j = 0; j < i; j++)
		printf("\t");
	printf("Redirection: %d\n", cmd->redirection_id);
	if (cmd->next)
	{
		for (int j = 0; j < i; j++)
			printf("\t");
		printf("Next:\n");
		print_cmd(cmd->next, i + 1);
	}
}

void	make_info_args(t_args *arg, t_info *info_arg)
{
	if (!arg)
		return ;
	arg->info = info_arg;
	if (!arg->prev)
		info_arg->first = arg;
	if (!arg->next)
		info_arg->last = arg;
	info_arg->length += 1;
	if (arg->next)
		make_info_args(arg->next, info_arg);
}

void	make_info(t_cmd *cmd, t_info *info_cmd, t_info *info_args)
{
	cmd->info = info_cmd;
	if (!cmd->prev)
		info_cmd->first = cmd;
	if (!cmd->next)
		info_cmd->last = cmd;
	info_cmd->length += 1;
	make_info_args(cmd->args, info_args);
	if (cmd->next)
		make_info(cmd->next, info_cmd, info_args);
}

static char	*get_bin_path(char *bin, t_env *env)
{
	char	**paths;
	char	*path;
	int		i;

	if (bin[0] == '/')
	{
		if (check_access(bin) != IS_FILE)
			return (NULL);
		else
			return (bin);
	}
	paths = ft_split(get_string(get_env_from_char_key(env, "PATH", 0)->value), ':');
	i = -1;
	while (paths[++i])
	{
		path = ft_strdup(paths[i]);
		path = ft_strjoin(path, "/");
		path = ft_strjoin(path, bin);
		if (check_access(path) == IS_FILE)
			return (path);
		free(path);
	}
	return (NULL);
}

static void	exec_bin(t_cmd *cmd, t_env *env)
{
	char	*path;

	if (!is_redirection_pipe(cmd->redirection_id))
	{
		if (cmd->fd_in != STDIN_FILENO)
		{
			dup2(cmd->fd_in, STDIN_FILENO);
			close(cmd->fd_in);
		}
		if (cmd->fd_out != STDOUT_FILENO)
		{
			dup2(cmd->fd_out, STDOUT_FILENO);
			close(cmd->fd_out);
		}
	}
	else
	{
		if (cmd->prev && is_redirection_pipe(((t_cmd *)cmd->prev)->redirection_id))
		{
			dup2(cmd->fd_in, STDIN_FILENO);
		}
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
		close(cmd->fd_in);
	}
	path = get_bin_path(get_string(cmd->bin), env);
	if (!path)
	{
		ft_putstr_fd(get_string(cmd->bin), STDERR_FILENO);
		ft_putendl_fd(": Commande introuvable", STDERR_FILENO);
	}
	else
	{
		execve(path, list_to_array(cmd->args), env_to_array(env));
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putstr_fd(get_string(cmd->bin), STDERR_FILENO);
		perror(" ");
	}
	exit(127);
}

static void	back_to_first(t_cmd **cmd)
{
	while ((*cmd))
	{
		if ((*cmd)->prev)
			(*cmd) = (*cmd)->prev;
		else
			break;
	}
}

static void execute_cmd(t_cmd *cmd, t_env *env)
{
	int		pid;

	(void) env;
	(void) pid;
	while (cmd)
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
				if (cmd->fd_out != STDOUT_FILENO)
					close(cmd->fd_out);
				if (cmd->fd_in != STDIN_FILENO)
					close(cmd->fd_in);
				cmd->pid = pid;
			}
		} 
		if (cmd->next)
			cmd = cmd->next;
		else
			break;
	}
	back_to_first(&cmd);
	wait_all_pid(cmd);
}

static t_cmd *check_error(t_cmd *cmd)
{
	while (cmd)
	{
		if (is_redirection_in_or_out(cmd->redirection_id) || is_redirection_pipe(cmd->redirection_id))
		{
			if (!cmd->next)
				return (cmd);
			else if (cmd->prev && !((t_cmd *) cmd->prev)->bin)
				return (cmd);
		}
		if (cmd->next)
			cmd = cmd->next;
		else
			break;
	}
	return (NULL);
}

void	execute(void *line, void *env)
{
	t_cmd	*cmd;
	t_cmd	*configured;
	t_info	info_cmd;
	t_info	info_args;
	t_cmd	*cmd_error;
	int		success;

	cmd = create_cmd(NULL, (t_string *)line, 0, (t_env *)env);
	if (!cmd)
		return ;
	info_cmd.first = NULL;
	info_cmd.last = NULL;
	info_cmd.length = 0;
	info_args.first = NULL;
	info_args.last = NULL;
	info_args.length = 0;
	make_info(cmd, &info_cmd, &info_args);
	back_to_first(&cmd);
	cmd_error = check_error(cmd);
	back_to_first(&cmd);
	if (cmd_error)
	{
		printf("Erreur de syntaxe près du symbole inattendu: '%s'\n", get_redirection_from_id(cmd_error->redirection_id));
		return ;
	}
	success = 0;
	configured = make_redirection(NULL, cmd, &success);
	if (success)
		return (print_redirection_error(success));
	back_to_first(&configured);
	execute_cmd(configured, env);
	// printf("Start cmd: %s\n", get_string(cmd->bin));
	// printf("Start args: %s\n", get_string(((t_args *)cmd->args)->string));
	// cmd = get_info_first(cmd);
	// printf("Start cmd: %s\n", get_string(cmd->bin));
	// printf("Start args: %s\n", get_string(((t_args *)cmd->args)->string));
	// while (cmd && cmd->type != TYPE_FILE)//cmd->next != get_info_last(cmd))
	// {
	// 	printf("Get args\n");
	// 	cmd->args = get_info_first(cmd->args);
	// 	if (cmd->args)
	// 		printf("First args: %s\n", get_string(((t_args *)cmd->args)->string));
	// 	if (cmd->args)
	// 	{
	// 		cmd->args = ((t_args *)cmd->args)->next;
	// 		while (cmd->args)
	// 		{
	// 			printf("String: (%s)\n", get_string(((t_args *)cmd->args)->string));
	// 			printf("In fd: %d\n", cmd->fd_out);
	// 			ft_putstr_fd(get_string(((t_args *)cmd->args)->string), cmd->fd_out);
	// 			if (((t_args *)cmd->args)->next)
	// 				cmd->args = ((t_args *)cmd->args)->next;
	// 			else
	// 				break;
	// 		}
	// 	}
	// 	if (cmd->next)
	// 		cmd = cmd->next;
	// 	else
	// 		break;
	// }
	// if (cmd->fd_out == STDOUT_FILENO)
	// {
	// 	ft_putstr_fd(get_string(((t_args *)cmd->args)->string), cmd->fd_out);
	// }
	// printf("First bin: %s\n", get_string(((t_args *)cmd->args)->string));
	// printf("===== Cmd =====\n");
	// print_cmd(cmd, 0);
	int i = 0;
	if (i)
		launch(cmd, env);
}
