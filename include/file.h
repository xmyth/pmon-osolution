/*
 * Copyright (c) 2000 Opsycon AB  (www.opsycon.se)
 * Copyright (c) 2002 Patrik Lindergren (www.lindergren.com)
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by Opsycon AB.
 *	This product includes software developed by Patrik Lindergren.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */
/* $Id: file.h,v 1.1.1.1 2006/09/14 01:59:06 root Exp $ */
#ifndef __FILE_H__
#define __FILE_H__

#include <sys/queue.h>

typedef struct FileSystem {
	char	*devname;
	int	fstype;
	int	(*open) (int, const char *, int, int);
	int	(*read) (int , void *, size_t);
	int	(*write) (int , const void *, size_t);
	off_t	(*lseek) (int , off_t, int);
	int	(*close) (int);
	int	(*ioctl) (int , unsigned long , ...);
	SLIST_ENTRY(FileSystem)	i_next;
} FileSystem;

#define	FS_NULL		0	/* Null FileSystem */
#define	FS_TTY		1	/* tty://	TTY */
#define	FS_NET		2	/* tftp:// 	Network */
#define	FS_SOCK		3	/* socket://	Socket */
#define	FS_DEV		4	/* dev://	Raw device */
#define	FS_MEM		5	/* mem://	Memory */
#define	FS_FILE		6	/* file://	Structured File */

typedef struct File {
	short valid;
	unsigned long posn;
	FileSystem *fs;
	void  *data;
} File;

extern File _file[];

int filefs_init(FileSystem *fs);
const char *getFSString(void);

#endif /* __FILE_H__ */
