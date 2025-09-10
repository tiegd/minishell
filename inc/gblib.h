/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gblib.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:55:45 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/09 17:22:58 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GBLIB_H
# define GBLIB_H

# include "struct.h"
# include <stdlib.h>

/*--garbage_collector_lib--*/

char	*gb_substr(char const *s, unsigned int start,
			size_t len, t_gmalloc **head);
char	*gb_strdup(char *s, t_gmalloc **gmalloc);
char	*gb_strjoin_custom(char *s1, char *s2, t_gmalloc **head);
char	*gb_itoa(int nb, t_gmalloc **head);
char	**gb_split(char *s, char c, t_gmalloc **head);
char	*gb_strjoin(char *s1, char *s2, t_gmalloc **head);

/*--------GARBAGE_COLLECTOR----*/

void	*gb_malloc(size_t size, t_gmalloc **lst);
void	gmalloc_add_back(t_gmalloc **head, t_gmalloc *new);
void	gfree(void *ptr, t_gmalloc **head);
void	gb_free_all(t_gmalloc **head);
char	*gb_itoa(int nb, t_gmalloc **head);

#endif
