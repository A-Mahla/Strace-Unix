/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   child.c                                         :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/14 02:01:41 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/16 01:55:40 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


static char	*concat_file(const char *prefix, const char *filename)
{
	char *new_name = NULL;

	new_name = calloc(strlen(prefix) + strlen(filename) + 2, 1);
	if (!new_name)
		return NULL;
	strncat(new_name, prefix, strlen(prefix));
	strncat(new_name, "/", 2);
	strncat(new_name, filename, strlen(filename));
	return new_name;
}


static int8_t	get_env(char ***path, char **pwd, char **envp)
{
	for (size_t i = 0; envp[i]; i++) {
		if (strstr(envp[i], "PATH=") == envp[i]) {
			if (*path)
				free(path);
			*path = split(envp[i] + 5, ':');
			if (!*path)
				break;
		} else if (strstr(envp[i], "PWD=") == envp[i]) {
			*pwd = envp[i] + 4;
		}
	}
	if (errno == ENOMEM)
		return FAILURE;
	return SUCCESS;
}


char	*path_finding(const char *filename, char **envp)
{
	char **path = NULL;
	char *pwd = NULL;
	char *new_name = NULL;

	if (strchr(filename, '/') != NULL || !*envp)
		return strdup(filename);
	if (get_env(&path, &pwd, envp) == FAILURE)
		return NULL;
	if (!path)
		goto exit_without_path;
	for (size_t i = 0; path[i]; i++) {
		if ((new_name = concat_file(path[i], filename)) == NULL)
			goto err_free_null;
		if (access(new_name, X_OK) == 0)
			break;
		free(new_name);
		new_name = NULL;
	}
	free(path);
	if (!new_name)
		goto exit_without_path;
	return new_name;
err_free_null:
	free(path);
	return NULL;
exit_without_path:
	if (pwd)
		return concat_file(pwd, filename);
	return strdup(filename);
}
