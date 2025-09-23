/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:54:17 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/23 12:03:01 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "struct.h"

/*--------BUILT-IN--------*/

void	ft_echo(t_cmd *cmd, t_gmalloc **head);
void	ft_env(char **env, int fd, t_mini *mini);
char	**ft_export(char **old_env, char *str, t_mini *mini, t_gmalloc **head);
void	pwd(int fd, t_mini *mini);
void	cd(char	**args, t_gmalloc **head, t_mini *mini);
char	**unset(char *var, char **env, t_gmalloc **head);
char	**loop_unset(char **env, char **args, t_mini *mini, t_gmalloc **head);
char	*expend(char *arg, char **env, t_gmalloc **head, t_mini *mini);
char	**loop_export(char **env, char **args, t_mini *mini, t_gmalloc **head);
void	ft_exit(char **args, t_mini *mini, t_gmalloc **head);
void	print_export(char **env, t_mini *mini, t_gmalloc **head);
void	exit_wrong_arg(char *args, t_gmalloc **head);

/*--------BUILT-IN_UTILS--------*/

/*expend utils*/

int		strcmp_until_char(char *s1, char *s2, char c);
char	*add_double_quote(char *res, t_gmalloc **head);
char	*add_single_quote(char *res, t_gmalloc **head);
int		has_single_quote(char *str);
int		has_double_quote(char *str);
int		has_special(char *str);
char	*env_result(char *env, t_gmalloc **head);
int		count_size(int n);
int		which_quote(char *prompt, int *index);
char	**split_parts(char *prompt, t_gmalloc **head);

/*export utils*/

int		env_var_cmp(char *s1, char *s2);
int		is_valid_identifier(char *variable, t_mini *mini);
int		is_empty_var(char *variable);
void	replace_same_var(char *new_var, char **new_env,
			int i, t_gmalloc **head);
int		handle_same_var(char *new_var, char **new_env, int i, t_gmalloc **head);

/*echo utils*/

void	print_with_new_line(char *s, t_gmalloc **head);
void	print_with_space(char *s, t_gmalloc **head);

/*cd utils*/

void	update_pwd(t_mini *mini, t_gmalloc **head);
void	update_oldpwd(char *old_path, t_mini *mini, t_gmalloc **head);

#endif
