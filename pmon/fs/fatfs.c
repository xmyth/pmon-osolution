/* $Id: fatfs.c,v 1.1 2003/07/08 20:57:50 pefo Exp $ */

/*
 * Copyright (c) 2003 Opsycon AB (www.opsycon.se)
 * Copyright (c) 2003 Patrik Lindergren (www.lindergren.com)
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
 *	This product includes software developed by Opsycon AB, Sweden.
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

#include <stdio.h>
#include <string.h>
#include <termio.h>
#include <fcntl.h>
#include <file.h>
#include <ctype.h>
#include <ramfile.h>
#include <sys/unistd.h>
#include <stdlib.h>
#include <unistd.h>
#undef _KERNEL
#include <errno.h>

#include <pmon.h>
#include <file.h>
#include "fat.h"

extern int errno;

int   fat_open (int, const char *, int, int);
int   fat_close (int);
int   fat_read (int, void *, size_t);
int   fat_write (int, const void *, size_t);
off_t fat_lseek (int, off_t, int);


/*
 * Internal
 */
int fat_init(int , struct fat_sc *, int);
int fat_dump_fatsc(struct fat_sc *);
u_int32_t getFatEntry(struct fat_sc *, int );
int readsector(struct fat_sc *, int , int , u_int8_t *);
int parseShortFilename(struct direntry *, char *);
int fat_getChain(struct fat_sc *, int , struct fatchain *);
int getSectorIndex(struct fat_sc *, struct fatchain *, int );
int fat_getPartition(struct fat_sc *, int );
int fat_findfile(struct fat_sc *, char *);
int fat_subdirscan(struct fat_sc *, char *, struct fatchain *);
int fat_dump_fatsc(struct fat_sc *);
int fat_dump_fileentry(struct fat_sc *);
u_int8_t shortNameChkSum(u_int8_t *);
int fat_parseDirEntries(int ,struct fat_fileentry *);


/*
 * Supported paths:
 *	/dev/fat/disk@wd0/file
 *	/dev/fat/ram@address/file
 *
 */
int
fat_open(int fd, const char *path, int flags, int mode)
{
	char dpath[64];
	char dpath2[64];
	const char *opath;
	char *filename;
	struct fat_sc *fsc;
	int fd2;
	int res;
	int partition = 0, dpathlen;
	char * p;

	/*  Try to get to the physical device */
	opath = path;
	if (strncmp(opath, "/dev/", 5) == 0)
		opath += 5;
	if (strncmp(opath, "fat/", 4) == 0)
		opath += 4;

	/* There has to be at least one more component after the devicename */
	if (strchr(opath, '/') == NULL) {
		errno = ENOENT;
		return (-1);
	}

	/* Dig out the device name */
	strncpy(dpath2, opath, sizeof(dpath2));
	*(strchr(dpath2, '/')) = '\0';
	sprintf(dpath, "/dev/%s", dpath2);

	/* Set opath to point at the isolated filname path */
	filename = strchr(opath, '/') + 1;

	fsc = (struct fat_sc *)malloc(sizeof(struct fat_sc));
	if (fsc == NULL) {
		errno = ENOMEM;
		return (-1);
	}

	/*
	 * Need to mark existing fd to valid otherwise we can't
	 * open the new device.
	 */
	_file[fd].valid = 1;

	//we need to change the device name like this /dev/disk/wd0, not /dev/disk@wd0
	if(p = strchr(dpath, '@'))
		*p = '/';

	//here we see if the name is /dev/disk/wd0a or something like this
	dpathlen = strlen(dpath);
	if(dpath[dpathlen - 1] >= 'a' && dpath[dpathlen - 1] <= 'z')
	{
		partition = dpath[dpathlen - 1] - 'a';
		dpath[dpathlen - 1] = 0;
	}

	/* Try to open the physical device */
	fd2 = open(dpath, flags, mode);
	if (fd2 < 0) {
		free(fsc);
		errno = EINVAL;
		_file[fd].valid = 0;
		return (-1);
	}

	if (fat_init(fd2, fsc, partition) == 0) {
		close(fd2);
		free(fsc);
		errno = EINVAL;
		_file[fd].valid = 0;
		return (-1);
	}

	res = fat_findfile(fsc, filename);
	if (res <= 0) {
		close(fd2);
		free(fsc);
		errno = EINVAL;
		_file[fd].valid = 0;
		return (-1);
	}

	fsc->LastSector = -1;	/* No valid sector in sector buffer */

	_file[fd].posn = 0;
	_file[fd].data = (void *)fsc;
	return (fd);
}

int
fat_close(int fd)
{
	struct fat_sc *fsc;

	fsc = (struct fat_sc *)_file[fd].data;

	if (fsc->file.Chain.entries) {
		free(fsc->file.Chain.entries);
		fsc->file.Chain.entries = NULL;
	}
	fsc->file.Chain.count = 0;
	close(fsc->fd);
	free(fsc);

	return (0);
}

int
fat_read(int fd, void *buf, size_t len)
{
	struct fat_sc *fsc;
	int sectorIndex;
	int totalcopy = 0;
	int origpos;
	int copylen;
	int offset;
	int sector;
	int res = 0;

	fsc = (struct fat_sc *)_file[fd].data;

	origpos = _file[fd].posn;

	/*
	 * Check file size bounder
	 */
	if (_file[fd].posn >= fsc->file.FileSize) {
	        return (-1);
	}

	if ((_file[fd].posn + len) > fsc->file.FileSize) {
		len = fsc->file.FileSize - _file[fd].posn;
	}

	while (len) {
		offset = _file[fd].posn % SECTORSIZE;
		sectorIndex = _file[fd].posn / SECTORSIZE;
		
		sector = getSectorIndex(fsc, &fsc->file.Chain, sectorIndex);

		copylen = len;
		if (copylen > (SECTORSIZE - offset)) {
			copylen = (SECTORSIZE - offset);
		}

		if (sector != fsc->LastSector) {
			res = readsector(fsc, sector, 1, fsc->LastSectorBuffer);
			if (res < 0)
				break;
			fsc->LastSector = sector;
		}
		
		memcpy(buf, &fsc->LastSectorBuffer[offset], copylen);
		
		buf += copylen;
		_file[fd].posn += copylen;
		len -= copylen;
		totalcopy += copylen;
	}
	
	if (res < 0) {
		_file[fd].posn = origpos;
		return res;
		
	}

	return totalcopy;
}

int
fat_write(int fd, const void *start, size_t size)
{
	errno = EROFS;
	return EROFS;
}

off_t
fat_lseek(int fd, off_t offset, int whence)
{
	struct fat_sc *fsc;

	fsc = (struct fat_sc *)_file[fd].data;

	switch (whence) {
		case SEEK_SET:
			_file[fd].posn = offset;
			break;
		case SEEK_CUR:
			_file[fd].posn += offset;
			break;
		case SEEK_END:
			_file[fd].posn = fsc->file.FileSize + offset;
			break;
		default:
			errno = EINVAL;
			return (-1);
	}
	return (_file[fd].posn);
}


/*
 *  File system registration info.
 */
static FileSystem fatfs = {
        "fat", FS_FILE,
        fat_open,
        fat_read,
        fat_write,
        fat_lseek,
        fat_close,
	NULL
};

static void init_fs(void) __attribute__ ((constructor));

static void
init_fs()
{
	filefs_init(&fatfs);
}

/***************************************************************************************************
 * Internal function
 ***************************************************************************************************/

int getSectorIndex(struct fat_sc *fsc, struct fatchain * chain, int index)
{
	int clusterIndex;
	int sectorIndex;
	int sector;
	int entry;

	clusterIndex = index / fsc->SecPerClust;
	sectorIndex = index % fsc->SecPerClust;

	if (clusterIndex < chain->count)
		entry = chain->entries[clusterIndex];
	else
		entry = -1;

	sector = fsc->DataSectorBase + (entry - 2) * fsc->SecPerClust + sectorIndex;

	return (sector);
}

int fat_getPartition(struct fat_sc *fsc, int partition)
{
	u_int8_t buffer[SECTORSIZE];
	struct mbr_t *mbr;
	struct bpb_t *bpb;
	int i;
	
	fsc->PartitionStart = 0;
	if (readsector(fsc, 0, 1, buffer) == 0)
		return (0);

	/*
	 * Check if there exists a MBR
	 */
	bpb = (struct bpb_t *)buffer;
	
#if 0
	if ((bpb->bpbBytesPerSec == 512) &&
	    ((bpb->efat16.bsBootSig == BPB_SIG_VALUE1) ||
	     (bpb->efat16.bsBootSig == BPB_SIG_VALUE2))) {
		/*
		 * No MBR where found
		 */
		return (1);
	}
#endif
	
	if (bpb->bpbBytesPerSec == 512)
	{
		if(partition == 0)
			return (1);
		else
			return 0;
	}

	/*
	 * Find the active partition
	 */
	mbr = (struct mbr_t *)buffer;

	for (i = 0; i < PART_SIZE; i++) {
		if (//(mbr->partition[i].bootid == PART_BOOTID_ACTIVE) &&
				((mbr->partition[i].systid == PART_TYPE_FAT12) ||
				 (mbr->partition[i].systid == PART_TYPE_FAT16) ||
				 (mbr->partition[i].systid == PART_TYPE_FAT16BIG) ||
				 (mbr->partition[i].systid == 0x0c))) {
			if(!partition)
				break;
			else
				partition--;
		}
	}
	if (i == PART_SIZE) {
		return (0);
	}

	fsc->PartitionStart = letoh32(mbr->partition[i].relsect);

	return (1);
}

int fat_init(int fd, struct fat_sc *fsc, int partition)
{
	unsigned char bootsector[SECTORSIZE];
	struct bpb_t *bpb;

	bzero(fsc, sizeof(struct fat_sc));

	fsc->fd = fd;

	/*
	 * Check for partition
	 */
	if(!fat_getPartition(fsc, partition))
	{
		printf("get partition error: %d\n", partition);
		return 0;
	}

	/*
	 * Init BPB
	 */
	if (readsector(fsc, 0, 1, bootsector) == 0) {
		fprintf(stderr, "Can't read from %d bytes\n", SECTORSIZE);
		return (-1);
	}
	bpb = (struct bpb_t *)bootsector;
	
	/*
	 * Init Fat Software structure
	 */
	fsc->RootDirEnts = letoh16(bpb->bpbRootDirEnts);
	fsc->BytesPerSec = letoh16(bpb->bpbBytesPerSec);
	fsc->ResSectors = letoh16(bpb->bpbResSectors);
	fsc->SecPerClust = bpb->bpbSecPerClust;
	fsc->NumFATs = bpb->bpbFATs;
	fsc->FatCacheNum = -1;

	if (bpb->bpbFATsecs != 0)
		fsc->FATsecs = (u_int32_t)letoh16(bpb->bpbFATsecs);
	else
		fsc->FATsecs = letoh32(bpb->efat32.bpbFATSz32);

	if (bpb->bpbSectors != 0)
		fsc->TotalSectors = (u_int32_t)letoh16(bpb->bpbSectors);
	else
		fsc->TotalSectors = letoh32(bpb->bpbHugeSectors);

	fsc->RootDirSectors = ((fsc->RootDirEnts * 32) + (fsc->BytesPerSec - 1)) / fsc->BytesPerSec;
	fsc->DataSectors = fsc->TotalSectors - (fsc->ResSectors + (fsc->NumFATs * fsc->FATsecs) + fsc->RootDirSectors);
	fsc->DataSectorBase = fsc->ResSectors + (fsc->NumFATs * fsc->FATsecs) + fsc->RootDirSectors;
	fsc->CountOfClusters = fsc->DataSectors / fsc->SecPerClust;
	fsc->ClusterSize = fsc->BytesPerSec * fsc->SecPerClust;
	fsc->FirstRootDirSecNum = fsc->ResSectors + (fsc->NumFATs * fsc->FATsecs);

	if (fsc->CountOfClusters < 4085) {
		/* Volume is FAT12 */
		fsc->FatType = TYPE_FAT12;
	} else if (fsc->CountOfClusters < 65525) {
		/* Volume is FAT16 */
		fsc->FatType = TYPE_FAT16;
	} else {
		/* Volume is FAT32 */
		fsc->FatType = TYPE_FAT32;
	}

	return (1);
}

u_int32_t getFatEntry(struct fat_sc *fsc, int entry)
{
	u_int32_t fatsect;
	u_int32_t byteoffset;
	u_int32_t fatstart;
	u_int32_t fatoffset;
	u_int8_t b1,b2,b3,b4;
	int res;

	fatstart = fsc->ResSectors;
	
	if (fsc->FatType == TYPE_FAT12) {
		int odd;

		odd = entry & 1;
		byteoffset = ((entry & ~1) * 3) / 2;
		fatsect = byteoffset / SECTORSIZE;
		fatoffset = byteoffset % SECTORSIZE;

		if (fsc->FatCacheNum != fatsect) {
			res = readsector(fsc, fatsect + fatstart, 1, fsc->FatBuffer);
			if (res < 0) {
				return res;
			}
			fsc->FatCacheNum = fatsect;
		}
		
		b1 = fsc->FatBuffer[fatoffset];
		
		if ((fatoffset+1) >= SECTORSIZE) {
			res = readsector(fsc, fatsect + 1 + fatstart, 1, fsc->FatBuffer);
			if (res < 0) {
				return res;
			}
			fsc->FatCacheNum = fatsect+1;
			fatoffset -= SECTORSIZE;
		}
		
		b2 = fsc->FatBuffer[fatoffset+1];

		if ((fatoffset+2) >= SECTORSIZE) {
			res = readsector(fsc, fatsect + 1 + fatstart, 1, fsc->FatBuffer);
			if (res < 0) {
				return res;
			}
			fsc->FatCacheNum = fatsect + 1;
			fatoffset -= SECTORSIZE;
		}
		
		b3 = fsc->FatBuffer[fatoffset+2];
		
		if (odd) {
			return ((unsigned int) b3 << 4) + ((unsigned int) (b2 & 0xF0) >> 4);
		} else {
			return ((unsigned int) (b2 & 0x0F) << 8) + ((unsigned int) b1);
		}

	} else if (fsc->FatType == TYPE_FAT16) {
		byteoffset = entry * 2;
		fatsect = byteoffset / SECTORSIZE;
		fatoffset = byteoffset % SECTORSIZE;
		
		if (fsc->FatCacheNum != fatsect) {
			res = readsector(fsc, fatsect + fatstart, 1, fsc->FatBuffer);
			if (res < 0) {
				return res;
			}
			fsc->FatCacheNum = fatsect;
		}

		b1 = fsc->FatBuffer[fatoffset];
		b2 = fsc->FatBuffer[fatoffset+1];
		return ((unsigned int) b1) + (((unsigned int) b2) << 8);
	} else if (fsc->FatType == TYPE_FAT32) {
		byteoffset = entry * 4;
		fatsect = byteoffset / SECTORSIZE;
		fatoffset = byteoffset % SECTORSIZE;
		
		if (fsc->FatCacheNum != fatsect) {
			res = readsector(fsc, fatsect + fatstart, 1, fsc->FatBuffer);
			if (res < 0) {
				return res;
			}
			fsc->FatCacheNum = fatsect;
		}

		b1 = fsc->FatBuffer[fatoffset];
		b2 = fsc->FatBuffer[fatoffset+1];
		b3 = fsc->FatBuffer[fatoffset+2];
		b4 = fsc->FatBuffer[fatoffset+3];
		return (((unsigned int) b1) + (((unsigned int) b2) << 8) + (((unsigned int) b3) << 16) + (((unsigned int) b4) << 24));
	}
	return (0);
}

#define MAX_DIRBUF 10
struct direntry dirbuf[MAX_DIRBUF];

int fat_findfile(struct fat_sc *fsc, char *name)
{
	struct fat_fileentry filee;
	struct direntry *dire;
	char *dpath;
	int long_name = 0;
	int dir_scan = 0, dir_list = 0;
	int i;

	bzero(&filee, sizeof(filee));

	dpath = strchr(name, '/');
	if (dpath != NULL) {
		*dpath = '\0';
		dpath++;
		dir_scan = 1;
	}		
	else if(*name == 0)
		dir_list = 1;


	for (fsc->DirCacheNum = fsc->FirstRootDirSecNum; fsc->DirCacheNum < (fsc->RootDirSectors + fsc->FirstRootDirSecNum); fsc->DirCacheNum++) 
	{
		if (readsector(fsc, fsc->DirCacheNum, 1, fsc->DirBuffer) == 0) {
			return (0);
		}

		dire = (struct direntry *)fsc->DirBuffer;

		for (i = 0; (i < (SECTORSIZE / sizeof(struct direntry))); i++, dire++) {
			
			if (dire->dirName[0] == SLOT_EMPTY)
			{
				if(dir_list)
					printf("\n");
				return (0);
			}

			if (dire->dirName[0] == SLOT_DELETED)
				continue;

			if (dire->dirAttributes == ATTR_WIN95) {
				bcopy((void *)dire, (void *)&dirbuf[long_name], sizeof(struct direntry));
				long_name++;
				if (long_name > MAX_DIRBUF - 1)
					long_name = 0;
				continue;
			}

			if (dir_list == 0 && dir_scan == 0 && dire->dirAttributes == ATTR_DIRECTORY) {
				long_name = 0;
				continue;
			}

			bcopy((void *)dire, (void *)&dirbuf[long_name], sizeof(struct direntry));
			fat_parseDirEntries(long_name, &filee);

			if(dir_list)
			{		
				printf("%s    ", filee.shortName);
			}
			else if ((strcasecmp(name, filee.shortName) == 0) || (strcasecmp(name, filee.longName) == 0)) {
				if (dir_scan) {
					struct fatchain chain;
					int res;

					fat_getChain(fsc, letoh16(dire->dirStartCluster), &chain);
					res = fat_subdirscan(fsc, dpath, &chain);
					if (chain.entries) {
						free(chain.entries);
					}
					return (res);
				} else {
					strcpy(fsc->file.shortName, filee.shortName);
					fsc->file.HighClust = filee.HighClust;
					fsc->file.StartCluster = filee.StartCluster;
					fsc->file.FileSize = filee.FileSize;
					fat_getChain(fsc, fsc->file.StartCluster, &fsc->file.Chain);
					return (1);
				}
			}
		}
	}

	if(dir_list)
		printf("\n");

	return (0);
}

int fat_subdirscan(struct fat_sc *fsc, char *name, struct fatchain *chain)
{
	struct fat_fileentry filee;
	struct direntry *dire;
	char *dpath;
	int long_name = 0;
	int dir_scan = 0, dir_list = 0;
	int sector;
	int i;
	int j;
	int k;

	bzero(&filee, sizeof(filee));

	dpath = strchr(name, '/');
	if (dpath != NULL) {
		*dpath = '\0';
		dpath++;
		dir_scan = 1;
	}
	else if(*name == 0)
		dir_list = 1;

	for (i = 0; i < chain->count; i++) {
		for (j = 0; j < fsc->SecPerClust; j++) {
			sector = getSectorIndex(fsc, chain, j);
			if (readsector(fsc, sector, 1, fsc->DirBuffer) == 0) {
				return (0);
			}

			dire = (struct direntry *)fsc->DirBuffer;
			
			for (k = 0; (k < (SECTORSIZE / sizeof(struct direntry))); k++, dire++) {
				
				if (dire->dirName[0] == SLOT_EMPTY)
				{
					if(dir_list)
						printf("\n");
					return (0);
				}

				if (dire->dirName[0] == SLOT_DELETED)
					continue;
				
				if (dire->dirAttributes == ATTR_WIN95) {
					bcopy((void *)dire, (void *)&dirbuf[long_name], sizeof(struct direntry));
					long_name++;
					if (long_name > MAX_DIRBUF - 1)
						long_name = 0;
					continue;
				}
				
				if (dir_list == 0 && dir_scan == 0 && dire->dirAttributes == ATTR_DIRECTORY) {
					long_name = 0;
					continue;
				}
				
				bcopy((void *)dire, (void *)&dirbuf[long_name], sizeof(struct direntry));
				fat_parseDirEntries(long_name, &filee);

				if(dir_list)
				{
					printf("%s    ", filee.shortName);
				}
				else if ((strcasecmp(name, filee.shortName) == 0) || (strcasecmp(name, filee.longName) == 0)) {
					if (dir_scan) {
						struct fatchain chain;
						int res;
						
						fat_getChain(fsc, letoh16(dire->dirStartCluster), &chain);
						res = fat_subdirscan(fsc, dpath, &chain);
						if (chain.entries) {
							free(chain.entries);
						}
						return (res);
					} else {
						strcpy(fsc->file.shortName, filee.shortName);
						fsc->file.HighClust = filee.HighClust;
						fsc->file.StartCluster = filee.StartCluster;
						fsc->file.FileSize = filee.FileSize;
						fat_getChain(fsc, fsc->file.StartCluster, &fsc->file.Chain);
						return (1);
					}
				}
			}
		}
	}

	if(dir_list)
		printf("\n");
	return (0);
}


int fat_parseDirEntries(int dirc, struct fat_fileentry *filee)
{
	struct direntry *dire;
	struct winentry *wine;
	u_int8_t longName[290];
	u_int8_t chksum;
	int c = 0;
	int i;

	dire = &dirbuf[dirc];
	filee->HighClust = letoh16(dire->dirHighClust);
	filee->StartCluster = letoh16(dire->dirStartCluster);
	filee->FileSize = letoh32(dire->dirFileSize);
	parseShortFilename(dire, filee->shortName);
	chksum = shortNameChkSum(filee->shortName);

	if (dirc != 0) {
		u_int8_t buffer[26];
		u_int16_t *bp;
		int j = 0;
		for (i = dirc; i != 0; i--) {
			wine = (struct winentry *)&dirbuf[i-1];
			bzero(buffer, sizeof(buffer));
			bcopy(wine->wePart1, &buffer[0], sizeof(wine->wePart1));
			bcopy(wine->wePart2, &buffer[sizeof(wine->wePart1)], sizeof(wine->wePart2));
			bcopy(wine->wePart3, &buffer[sizeof(wine->wePart1) + sizeof(wine->wePart2)], sizeof(wine->wePart3));
			bp = (u_int16_t *)buffer;
			for (j = 0; j < 14; j++, c++) {
				longName[c] = (u_int8_t)letoh16(bp[j]);
				if (longName[c] == '\0')
					goto done;
			}
		}
 done:
		strcpy(filee->longName, longName);
	}
	return (1);
}

u_int8_t shortNameChkSum(u_int8_t *name)
{
	u_int16_t len;
	u_int8_t sum;

	sum = 0;

	for (len = 11; len != 0; len--) {
		sum = ((sum & 1) ? 0x80 : 0) + (sum >> 1) + *name++;
	}
	return (sum);
	
}

int fat_getChain(struct fat_sc *fsc, int start, struct fatchain *chain)
{
	u_int32_t mask;
	u_int32_t entry;
	int count;
	int i;
	
	switch (fsc->FatType) {
	case TYPE_FAT12:
		mask = FAT12_MASK;
		break;
	case TYPE_FAT16:
		mask = FAT16_MASK;
		break;
	case TYPE_FAT32:
		mask = FAT32_MASK;
		break;
	default:
		mask = 0;
	}
	     
	for (count = 0; 1; count++) {
		entry = getFatEntry(fsc, start + count);
		if (entry >= (CLUST_EOFE & mask))
			break;
	}

	chain->count = count + 1;
	chain->start = start;

	chain->entries = (u_int32_t *)malloc(sizeof(u_int32_t) * chain->count);
	if (chain->entries == NULL) {
		return (-1);
	}

	chain->entries[0] = start;

	for (i = 0; i < count; i++) {
		chain->entries[i+1] = getFatEntry(fsc, start + i);
	}
	return (1);
}

int parseShortFilename(struct direntry *dire, char *name)
{
	int j;

	for (j = 0; j < 8; j++) {
		if (dire->dirName[j] == ' ')
			break;
		*name++ = dire->dirName[j];
	}
	if (dire->dirExtension[0] != ' ')
		*name++ = '.';
	for (j = 0; j < 3; j++) {
		if (dire->dirExtension[j] == ' ')
			break;
		*name++ = dire->dirExtension[j];
	}
	*name = '\0';

	return (-1);
}

int readsector(struct fat_sc *fsc, int sector, int count, u_int8_t *buffer)
{
	int res;

	res = lseek(fsc->fd, (sector * SECTORSIZE +
	    (fsc->PartitionStart * SECTORSIZE)), SEEK_SET);
	
	res = read(fsc->fd, buffer, (SECTORSIZE * count));

	if (res == (SECTORSIZE * count)) {
		return (1);
	} else {
		return (-1);
	}
}

#ifdef FAT_DEBUG
int fat_dump_fatsc(struct fat_sc *fsc)
{
	printf("Bytes per Sector = %d\n", fsc->BytesPerSec);
	printf("Sectors Per Cluster = %d\n", fsc->SecPerClust);
	printf("Number of reserved sectors = %d\n", fsc->ResSectors);
	printf("Number of FATs = %d\n", fsc->NumFATs);
	printf("Number of Root directory entries = %d\n", fsc->RootDirEnts);
	printf("Total number of sectors = %d\n", fsc->TotalSectors);
	printf("Number of sectors per FAT = %d\n", fsc->FATsecs);
	printf("Sectors per track = %d\n", fsc->SecPerTrack);
	printf("Number of hidden sectors = %d\n", fsc->HiddenSecs);
	printf("Number of Root directory sectors = %d\n", fsc->RootDirSectors);
	printf("Count of clusters = %d\n", fsc->CountOfClusters);
	printf("Clustersize = %d\n", fsc->ClusterSize);
	printf("First Root directory sector = %d\n", fsc->FirstRootDirSecNum);
	printf("Total Data Sectors = %d\n", fsc->DataSectors);
	printf("Data Sector base = %d\n", fsc->DataSectorBase);
	return (1);
}

int fat_dump_fileentry(struct fat_sc *fsc)
{
	int i;
	
	printf("        File: %s\n", fsc->file);
	printf("   HighClust: %d\n", fsc->file.HighClust);
	printf("StartCluster: %d\n", fsc->file.StartCluster);
	printf("    FileSize: %d\n", fsc->file.FileSize);

	if (fsc->file.Chain.count) {
		printf("Cluster chain: ");
		for (i = 0; i < fsc->file.Chain.count; i++) {
			printf("0x%08x ", fsc->file.Chain.entries[i]);
		}
		printf("\n");
	}
	return (1);
}
#endif /* FAT_DEBUG */

