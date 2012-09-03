/*
 * Copyright 2007-2012 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
 
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef HAVE_ERRNO_H
# include <errno.h>
#endif
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif
#ifdef HAVE_SYS_STAT_H
# include <sys/stat.h>
#endif
#ifdef HAVE_LOCALE_H
# include <locale.h>
#endif
#ifdef HAVE_NL_TYPES_H
# include <nl_types.h>
#endif

static const char *short_program_name = "mesg";

#ifdef ENABLE_NLS
static nl_catd msgcat;
#endif

#undef _
#ifdef ENABLE_NLS
# define _(i,x)                         catgets(msgcat, NL_SETD, i, x)
#else
# define _(i,x)                         (x)
#endif

static void
usage(void)
{
	fprintf(stderr, _(1, "Usage: %s [y|n]"), short_program_name);
	fputc('\n', stderr);
}

int
main(int argc, char **argv)
{	
	int opt;
	const char *t, *tty;
	struct stat sbuf;

#ifdef ENABLE_NLS
	setlocale(LC_ALL, "");
	msgcat = catopen("UXmesg", NL_CAT_LOCALE);
#endif
	if(argv[0])
	{
		if(NULL != (t = strrchr(argv[0], '/')))
		{
			short_program_name = t + 1;
		}
		else
		{
			short_program_name = argv[0];
		}
		argv[0] = (char *) short_program_name;
	}
	opt = -1;
	if(argc > 2)
	{
		usage();
		exit(2);
	}	
	if(argc == 2)
	{
		switch(argv[1][0])
		{
		case 'y':
			opt = 0;
			break;
		case 'n':
			opt = 1;
			break;
		default:
			usage();
			exit(2);
		}
	}
	if((NULL == (tty = ttyname(STDIN_FILENO))) &&
	   (NULL == (tty = ttyname(STDOUT_FILENO))) &&
	   (NULL == (tty = ttyname(STDERR_FILENO))))
	{
		fprintf(stderr, "%s: %s\n", short_program_name, _(2, "cannot determine terminal name"));
		exit(2);
	}	
	if(-1 == stat(tty, &sbuf))
	{
		fprintf(stderr, "%s: %s: %s\n", short_program_name, tty, strerror(errno));
		exit(2);
	}
	if(opt == -1)
	{
		if(sbuf.st_mode & S_IWGRP)
		{
			puts(_(3, "is y"));
			return 0;
		}
		puts(_(4, "is n"));
		return 1;
	}
	if(0 == opt)
	{
		sbuf.st_mode |= S_IWGRP;
	}
	else
	{
		sbuf.st_mode &= ~S_IWGRP;
	}
	if(chmod(tty, sbuf.st_mode))
	{
		fprintf(stderr, "%s: %s: %s\n", short_program_name, tty, strerror(errno));
		exit(2);
	}
#ifdef ENABLE_NLS
	if(msgcat)
	{
		catclose(msgcat);
	}
#endif
	return opt;
}
