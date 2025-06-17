/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:46:13 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/17 11:56:05 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_part_to_join(char	*prompt)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(prompt[i] && prompt[i] != '$')
	{
		if (prompt[i] == '$')
			count++;
		i++;
	}
}

int	which_quote(char *prompt, char **env)
{
	int		i;
	int		type;
	int 	start;
	char	*temp;
	char	*exp;

	i = 0;
	start = 0;
	while (prompt[i] != '$')
		i++;
	temp = ft_substr(prompt, start, i);
	while(prompt[i])
	{
		start = i;
		i++;
		while (prompt[i] && exp_isalnum(prompt[i]))
			i++;
		exp = ft_substr(prompt, start, i);
		exp = expend(exp, env);
		temp = ft_strjoin_custom(temp, exp);
	}
	
	
}

char	*handle_env_var(char *prompt)
{
	int		i;
	char	*var_res;
	char	*final;
	int		total_len;

	
	
}