/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   split.c                                         :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/14 02:14:31 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/16 15:58:15 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

static int	count_wd(char const *s, char c)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	if (!s || !*s)
		return (0);
	while (*(s + i))
	{
		while (*(s + i) && *(s + i) == c)
			i++;
		if (*(s + i))
			count++;
		while (*(s + i) && *(s + i) != c)
			i++;
	}
	return (count);
}

static size_t	slen_wd(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*(s + i) && *(s + i) != c)
		i++;
	return (i);
}

static void	strscpy(char **split, char const *s, char c)
{
	size_t	y;
	size_t	x;
	size_t	i;

	i = 0;
	y = 0;
	while (s && *(s + i))
	{
		x = 0;
		while (*(s + i) && *(s + i) == c)
			i++;
		while (*(s + i) && *(s + i) != c)
		{
			*(split[y] + x) = *(s + i);
			x++;
			i++;
		}
		y++;
	}
}

char	**split(char const *s, char c)
{
	size_t	i;
	int		y;
	char	**strs;

	y = -1;
	i = 0;
	strs = calloc((count_wd(s, c) + 1), sizeof(char *));
	if (!strs)
		return (NULL);
	while (++y < count_wd(s, c) && s)
	{
		while (*(s + i) && *(s + i) == c)
			i++;
		strs[y] = calloc((slen_wd(s + i, c) + 1), sizeof(char));
		if (!strs[y])
		{
			free_split(strs);
			return (NULL);
		}
		while (*(s + i) && *(s + i) != c)
			i++;
	}
	strscpy(strs, s, c);
	strs[y] = NULL;
	return (strs);
}
