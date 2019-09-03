/* vi: set sw=4 ts=4: */
/*
 * Licensed under GPLv2 or later, see file LICENSE in this tarball for details.
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libbb.h"
#include "unarchive.h"

char get_header_tar_bz2(archive_handle_t *archive_handle)
{
	/* Can't lseek over pipes */
	archive_handle->seek = seek_by_read;

	archive_handle->src_fd = open_transformer(archive_handle->src_fd, uncompressStream);
	archive_handle->offset = 0;
	while (get_header_tar(archive_handle) == EXIT_SUCCESS) /**/;

	/* Can only do one file at a time */
	return EXIT_FAILURE;
}