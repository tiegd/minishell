/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcwd_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:06:55 by jpiquet           #+#    #+#             */
/*   Updated: 2025/05/20 10:46:50 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <dirent.h>

// int main(void)
// {
// 	char *buf;

// 	if (chdir("/home/jpiquet/bin/") == -1)
// 	{
// 		printf("error chdir\n");
// 	}
// 	buf = getcwd(NULL, 0);

// 	printf("directory path = %s\n", buf);
// 	free(buf);

// 	return 0;
// }

int main(void)
{
	DIR *directory;
	struct dirent *res;

	directory = opendir("../misc");
	if (!directory)
		printf("error opendir");
	while (res != NULL)
	{
		res = readdir(directory);
		if (!res)
			printf("error readdir");
		printf("files names : %s\n", res->d_name);
	}

	return 0;
}

// int main(void)
// {
	
// 	char *pathname;

// 	pathname = ttyname(5);
// 	// for (int i = 0; i < 5; i++)
// 	printf("%s\n", pathname);

// 	return 0;
// }

// int main(void)
// {
//     char *pwd;
    
//     pwd = getcwd(NULL, 0);
//     printf("pwd before chdir: %s\n", pwd);
//     chdir("/Users/saeby/Documents/42/minishell");
//     pwd = getcwd(NULL, 0);
//     printf("pwd after chdir: %s\n", pwd);
//     return (0);
// }