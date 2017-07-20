/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sromanet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 21:59:10 by sromanet          #+#    #+#             */
/*   Updated: 2017/02/03 23:08:42 by sromanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "bus_errrror.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

typedef struct s_point
{
	int z; //zatrimka ^)
	int n; //n cache
	int **cache;

} t_point;

typedef struct s_req
{
	int video;
	int video_size;
	int req;
	int point;
	int all_bed;

} t_req;

typedef struct s_cash
{
	int size;
	int *video;
} t_cash;

void	ft_out(struct s_cash *cash, char *name, int *info)
{
	int z;
	char *new_n;

	//type file change == .in >> .out
	z = ft_strlen(name);
	new_n = ft_strnew(z);
	ft_strcpy(new_n, name);
	new_n[z] = 't';
	new_n[z - 1] = 'u';
	new_n[z - 2] = 'o';

	FILE *fd = fopen(new_n, "w");
	int a = 0;
	int b = 0;
	int c = 0;
	for (int i = 0; i < info[3]; ++i)
	{
		b = 0;
		for (int f = 0; f < info[0]; ++f)
		{
			if (cash[i].video[f] == 1)
				b++;
		}
		//printf("b == %d\n", b);
		if (b != 0)
			c++;
	}
	//printf("c == %d\n", c);
		// example -> fprintf(fd, "%s\n", data);
	fprintf(fd, "%d\n", c);

	for (int i = 0; i < c; ++i)
	{
		fprintf(fd, "%d", i);
		for (int q = 0; q < info[0]; ++q)
		{
			if (cash[i].video[q] == 1)
				fprintf(fd, " %d", q);
		}
		fprintf(fd, "\n");
	}
	fclose(fd);
	printf("finish%s\nAll fine, write next version\n", new_n);
}


int		**make_memory(int y, int x)
{
	int **re; //maybe another data type

	if (!(re = (int**)malloc(sizeof(int*) * y)))
		return (0);
	for (int len = 0; len < y; len++)
	{
		if (!(re[len] = (int*)malloc(sizeof(int) * x)))
			return (0);
	}
	return (re);
}

int compare (const void *a, const void *b)
{
  const t_req *orderA = (t_req *)a;
  const t_req *orderB = (t_req *)b;
  int aa = orderA->all_bed;
  int bb = orderB->all_bed;
  // return ( orderB->all_bed - orderA->all_bed );
  return (bb - aa);
}

int	ft_read_first_line(int fd, char *name) //read first line and get digital for working
{
	char *buf;
	char *str;
	char **new;
	int *info;

	buf = ft_strnew(1);
	str = ft_strnew(1);
	while (read(fd, buf, 1) && buf[0] != '\n')
		str = ft_strjoin(str, buf); //this line have memory leak :(
	new = ft_strsplit(str, ' ');
	info = (int *)malloc(sizeof(int) * 5);
	for (int n = 0; n < 5; n++)
	{
		info[n] = atoi(new[n]);
		//printf("info[%d] == %d\n\n", n, info[n]);
	}

	int video[info[0]];
	free(buf);
	free(str);
	buf = ft_strnew(1);
	str = ft_strnew(1);
	while (read(fd, buf, 1) && buf[0] != '\n')
		str = ft_strjoin(str, buf); //this line have memory leak :(
	new = ft_strsplit(str, ' ');
	for (int i = 0; i < info[0]; i++)
	{	
		video[i] = atoi(new[i]);
		//printf("video = %d\n", video[i]);
	}

	t_point *points = (t_point *)malloc(sizeof(t_point) * info[1]);
	int i = 0;

	while (i < info[1])
	{
		free(buf);
		free(str);
		buf = ft_strnew(1);
		str = ft_strnew(1);
		while (read(fd, buf, 1) && buf[0] != '\n')
			str = ft_strjoin(str, buf); //this line have memory leak :(
		new = ft_strsplit(str, ' ');

		points[i].z = atoi(new[0]);
		points[i].n = atoi(new[1]);
		points[i].cache = make_memory(points[i].n, 2);
		for (int f = 0; f < points[i].n; ++f)
		{
			free(buf);
			free(str);
			buf = ft_strnew(1);
			str = ft_strnew(1);

			while (read(fd, buf, 1) && buf[0] != '\n')
				str = ft_strjoin(str, buf); //this line have memory leak :(
			new = ft_strsplit(str, ' ');
			points[i].cache[f][0] = atoi(new[0]);
			points[i].cache[f][1] = atoi(new[1]);
		}
		i++;
	}

	t_req *req = (t_req *)malloc(sizeof(t_req) * info[2]);
	i = -1;
	while(++i < info[2])
	{
		free(buf);
		free(str);
		buf = ft_strnew(1);
		str = ft_strnew(1);
		while (read(fd, buf, 1) && buf[0] != '\n')
			str = ft_strjoin(str, buf); //this line have memory leak :(
		new = ft_strsplit(str, ' ');
		req[i].video = atoi(new[0]);
		req[i].req = atoi(new[2]);
		req[i].point = atoi(new[1]);
		req[i].video_size = video[req[i].video];
		req[i].all_bed = req[i].req * points[req[i].point].z;
	}
	qsort ((void*)req, info[2], sizeof(req[0]), compare);

	int min;
	int zz;
	t_cash *cash = (t_cash *)malloc(sizeof(t_cash) * info[3]);
	for (int i = 0; i < info[3]; ++i)
	{
		cash[i].size = info[4];
		cash[i].video = (int *)malloc(sizeof(int) * info[0] + 1);
		ft_bzero(cash[i].video, info[0] + 1);
	}

	for (int i = 0; i < info[2]; ++i)
    {
        int MYPIONT = req[i].point;
        int nVideo = req[i].video;
        int rozmirVideo = req[i].video_size;

        //printf("points = %d\n", points[MYPIONT].n);
       int **chasi = points[MYPIONT].cache;
        for (int j = 0; j < points[MYPIONT].n ; ++j) {
            int nKesha = chasi[j][0];// номер кеша
            if (cash[nKesha].size >= rozmirVideo && cash[nKesha].video[nVideo] != 1) {
                cash[nKesha].size -= rozmirVideo;
                cash[nKesha].video[nVideo] = 1;
                break;
            }
        }
	}
	ft_out(cash, name, info);
	return (0);
}

int	main(int c, char **v)
{
	int fd;
	int n;
	int f = 1;

	while (f < c)
	{
		if ((fd = open(v[f], O_RDONLY, 0)) == -1)
		{
			printf("error: You can not open file >%s<\n", v[f]);
			return (0);
		}
		n = ft_read_first_line(fd, v[f]);
		close(fd);
		f++;
	}
	return (0);
}
