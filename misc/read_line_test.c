/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:31:32 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/12 11:34:25 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

// void simulate_autocorrect(const char *line)
// {
// 	if (strcmp(line, "brb") == 0) {
// 		// Remplacer la ligne tapée par une phrase complète
// 		rl_replace_line("be right back", 1);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

int main() 
{
	char *line;

	// Boucle principale
	while ((line = readline(">> ")) != NULL) 
	{
		if (*line) 
		{
			add_history(line);
		}
		printf("\n");
		printf("line utilisateur : %s\n", line); // Affiche la ligne courante

		free(line);
	}
    return 0;
}
