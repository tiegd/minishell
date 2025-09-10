/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:03:53 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/10 18:32:45 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exec.h"
#include "clean.h"
#include "fd.h"

int	prompt_is_empty(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!is_ws(input[i]))
			return (0);
		i++;
	}
	return (1);
}

void	send_to_exec(t_mini *mini)
{
	if (mini->nb_pipe > 0)
		pipex(mini->cmd, mini, &mini->gmalloc);
	else
		ft_one_cmd(mini->cmd, mini, &mini->gmalloc);
}

void	tokenise_and_init_cmd_lst(char **prompt, t_mini *mini)
{
	mini->token = tab_to_lst(prompt, &mini->gmalloc);
	mini->token = handle_quote(&mini->token);
	mini->nb_pipe = count_pipe(&mini->token);
	mini->cmd = init_cmd(&mini->token, &mini->gmalloc);
}

int	ft_parsing(char *input, t_mini *mini)
{
	char	**prompt;

	if (prompt_is_empty(input))
		return (0);
	if (syntax_error(input))
		return (str_return("minishell : syntax error\n", 2, mini));
	if (ft_strchr(input, '$'))
	{
		input = handle_env_var(input, mini);
		if (!input || input[0] == '\0')
			return (0);
	}
	prompt = multi_split(input, &mini->gmalloc);
	tokenise_and_init_cmd_lst(prompt, mini);
	if (open_for_each_cmd(&mini->cmd, mini) != 0)
	{
		free_cmd(mini->cmd, &mini->gmalloc);
		return (0);
	}
	unblock_sig_quit();
	send_to_exec(mini);
	close_all_here_doc(mini->here_doc_list);
	free_cmd(mini->cmd, &mini->gmalloc);
	return (0);
}
