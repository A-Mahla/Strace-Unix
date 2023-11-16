/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   arch.c                                          :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/16 15:16:23 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/16 15:39:40 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


uint8_t	arch(char *filename, char *av)
{
	int			fd;
	Elf64_Ehdr	header;
	struct stat	statbuf;
	uint8_t		arch = ELFCLASSNONE;

	if (stat(filename, &statbuf) < 0) {
		free(filename);
		printf("strace: Can't stat '%s': %s\n", av, strerror(errno));
		exit(1);
	}
	if ((fd = open(filename, O_RDONLY)) < 0)
		return arch;
	if (read(fd, &header, sizeof(header)) < 0)
		return arch;
	if (header.e_ident[EI_CLASS] == ELFCLASS64)
		arch = ELFCLASS64;
	else if (header.e_ident[EI_CLASS] == ELFCLASS32)
		arch = ELFCLASS32;
	return arch;
}
