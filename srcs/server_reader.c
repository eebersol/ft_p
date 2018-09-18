/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/18 17:31:47 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_p.h>


void	read_file(char *file, int cs)
{
	t_env 	*env;
	char 	buf[1024];
	int 	r;


	env = recover_env();
	printf("read_file 1\n");
	env->file_fd = open(file, O_CREAT|O_WRONLY, 0777);
	while((r = read(cs, &buf, 1023)) > 0)
	{
		printf("read_file 2 %s\n", buf);
		write(env->file_fd, buf, r);
		ft_bzero(&buf, 1024);
	}
	close(env->file_fd);
	printf("read_file 3\n");
}

void create_file(t_env *env, char *file)
{
	env->file_fd = open(file, O_CREAT|O_WRONLY, 0777);
	return;
}

int 	reader(int cs)
{
	t_env 	*env;
	char 	buf[1024];
	char 	**cmd;
	int 	r;
	int 	puts;

	env = recover_env();
	cmd = NULL;
	puts = 0;
	printf("begin\n");
	while((r = read(cs, &buf, 1023)) > 0)
	{
		buf[r] = '\0';
		cmd = ft_strsplit(buf, ' ');
		printf("cmd : %s %s %s\n", cmd[0], cmd[1], cmd[2]);
		if (ft_strcmp(cmd[0], "put") == 0)
		{	
			printf("puts\n");
			puts = 1;
			break;
		}
		else
		{
			printf("other\n");
			find_cmd(cmd, cs);
		}
		ft_bzero(&buf, 1024);
	}
	if (puts == 1)
	{
		read_file(cmd[1], cs);
		reader(cs);
	}
	printf("ICI\n");
	return (r);
}