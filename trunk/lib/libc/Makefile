#	$Id: Makefile,v 1.1.1.1 2006/09/14 01:59:06 root Exp $ */
#
#
# Copyright (c) 2001 Opsycon AB  (www.opsycon.se)
# Copyright (c) 2002 Patrik Lindergren  (www.lindergren.com)
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. All advertising materials mentioning features or use of this software
#    must display the following acknowledgement:
#	This product includes software developed by Opsycon AB, Sweden.
#	This product includes software developed by Patrik Lindergren.
# 4. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
# OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#
#

LIB=c
NOPIC=

MACHINE=	${XMACHINE}
MACHINE_ARCH=	${XMACHINE_ARCH}
CURDIR=$(shell pwd)

M=	${CURDIR}/arch/${MACHINE_ARCH}

CPPFLAGS=	-I$M ${CLIBCPPFLAGS} -U_KERNEL

VPATH+=	${M} ${CLIBDIR}
 
include ${M}/Makefile.inc

# Files to clean up
CLEANFILES+= ${OBJDIR}/lib${LIB}.a

include ${PMONDIR}/tools/scripts/pmon.lib.gmk

${OBJDIR}/lib${LIB}.a: ${OBJS}
	@echo building standard ${LIB} library
	@rm -f $@
	@${AR} cq $@ ${OBJS}
	${RANLIB} $@

# DO NOT DELETE

argvize.o: /user/os/svn/pmon/include/string.h
argvize.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
argvize.o: /user/os/svn/pmon/sys/sys/cdefs.h
argvize.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
atob.o: /user/os/svn/pmon/sys/arch/mips/include/types.h
atob.o: /user/os/svn/pmon/sys/sys/cdefs.h
atob.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
atob.o: /user/os/svn/pmon/include/string.h
atob.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
atob.o: /user/os/svn/pmon/include/pmon.h /user/os/svn/pmon/sys/sys/types.h
atob.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
atob.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
atob.o: /user/os/svn/pmon/sys/sys/endian.h
atob.o: /user/os/svn/pmon/sys/arch/mips/include/pmon_arch.h
atob.o: /user/os/svn/pmon/include/progress.h
atob.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/target/pmon_target.h
atob.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/target/bonito.h
atoi.o: /user/os/svn/pmon/include/string.h
atoi.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
atoi.o: /user/os/svn/pmon/sys/sys/cdefs.h
atoi.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
atoi.o: /user/os/svn/pmon/include/stdlib.h /user/os/svn/pmon/sys/sys/types.h
atoi.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
atoi.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
atoi.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/include/ctype.h
atol.o: /user/os/svn/pmon/include/string.h
atol.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
atol.o: /user/os/svn/pmon/sys/sys/cdefs.h
atol.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
atol.o: /user/os/svn/pmon/include/stdlib.h /user/os/svn/pmon/sys/sys/types.h
atol.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
atol.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
atol.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/include/ctype.h
bzero.o: /user/os/svn/pmon/include/string.h
bzero.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
bzero.o: /user/os/svn/pmon/sys/sys/cdefs.h
bzero.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
bcmp.o: /user/os/svn/pmon/include/string.h
bcmp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
bcmp.o: /user/os/svn/pmon/sys/sys/cdefs.h
bcmp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
calloc.o: /user/os/svn/pmon/include/string.h
calloc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
calloc.o: /user/os/svn/pmon/sys/sys/cdefs.h
calloc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
calloc.o: /user/os/svn/pmon/include/stdlib.h
calloc.o: /user/os/svn/pmon/sys/sys/types.h
calloc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
calloc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
calloc.o: /user/os/svn/pmon/sys/sys/endian.h
cc2str.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
cc2str.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
cc2str.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
cc2str.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
cc2str.o: /user/os/svn/pmon/sys/sys/endian.h
cc2str.o: /user/os/svn/pmon/sys/sys/cdefs.h
cc2str.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
cc2str.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
cc2str.o: /user/os/svn/pmon/include/string.h
cc2str.o: /user/os/svn/pmon/include/ctype.h
close.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
close.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
close.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
close.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
close.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
close.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
close.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
close.o: /user/os/svn/pmon/include/file.h /user/os/svn/pmon/sys/sys/queue.h
close.o: /user/os/svn/pmon/include/unistd.h
close.o: /user/os/svn/pmon/sys/sys/unistd.h /user/os/svn/pmon/sys/sys/time.h
close.o: /user/os/svn/pmon/include/time.h
ctype_.o: /user/os/svn/pmon/include/ctype.h /user/os/svn/pmon/sys/sys/cdefs.h
ctype_.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
ethers.o: /user/os/svn/pmon/sys/sys/types.h
ethers.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
ethers.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
ethers.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
ethers.o: /user/os/svn/pmon/sys/sys/endian.h
ethers.o: /user/os/svn/pmon/sys/sys/cdefs.h
ethers.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
ethers.o: /user/os/svn/pmon/sys/sys/socket.h /user/os/svn/pmon/sys/net/if.h
ethers.o: /user/os/svn/pmon/sys/sys/queue.h /user/os/svn/pmon/sys/sys/time.h
ethers.o: /user/os/svn/pmon/include/time.h /user/os/svn/pmon/sys/net/if_arp.h
ethers.o: /user/os/svn/pmon/sys/netinet/in.h
ethers.o: /user/os/svn/pmon/sys/netinet/if_ether.h
ethers.o: /user/os/svn/pmon/sys/sys/param.h
ethers.o: /user/os/svn/pmon/sys/sys/simplelock.h
ethers.o: /user/os/svn/pmon/sys/sys/syslimits.h
ethers.o: /user/os/svn/pmon/sys/sys/signal.h
ethers.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/signal.h
ethers.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cpu.h
ethers.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/psl.h
ethers.o: /user/os/svn/pmon/sys/sys/siginfo.h
ethers.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/param.h
ethers.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/limits.h
ethers.o: /user/os/svn/pmon/include/errno.h /user/os/svn/pmon/include/stdio.h
ethers.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
ethers.o: /user/os/svn/pmon/include/stdlib.h
ethers.o: /user/os/svn/pmon/include/string.h
ethers.o: /user/os/svn/pmon/include/ctype.h
exit.o: /user/os/svn/pmon/include/stdlib.h
exit.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
exit.o: /user/os/svn/pmon/sys/sys/types.h
exit.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
exit.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
exit.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
exit.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
fclose.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
fclose.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
fclose.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
fclose.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
fclose.o: /user/os/svn/pmon/sys/sys/endian.h
fclose.o: /user/os/svn/pmon/sys/sys/cdefs.h
fclose.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
fclose.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
fclose.o: /user/os/svn/pmon/include/unistd.h
fclose.o: /user/os/svn/pmon/sys/sys/unistd.h /user/os/svn/pmon/sys/sys/time.h
fclose.o: /user/os/svn/pmon/include/time.h
feof.o: /user/os/svn/pmon/include/termio.h
feof.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
feof.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
feof.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
feof.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
feof.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
feof.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
feof.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
feof.o: /user/os/svn/pmon/include/queue.h /user/os/svn/pmon/include/file.h
feof.o: /user/os/svn/pmon/sys/sys/queue.h
fflush.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
fflush.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
fflush.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
fflush.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
fflush.o: /user/os/svn/pmon/sys/sys/endian.h
fflush.o: /user/os/svn/pmon/sys/sys/cdefs.h
fflush.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
fflush.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
ffs.o: /user/os/svn/pmon/include/string.h
ffs.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
ffs.o: /user/os/svn/pmon/sys/sys/cdefs.h
ffs.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
fgetc.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
fgetc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
fgetc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
fgetc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
fgetc.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
fgetc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
fgetc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
fgetc.o: /user/os/svn/pmon/include/unistd.h
fgetc.o: /user/os/svn/pmon/sys/sys/unistd.h /user/os/svn/pmon/sys/sys/time.h
fgetc.o: /user/os/svn/pmon/include/time.h
fgets.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
fgets.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
fgets.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
fgets.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
fgets.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
fgets.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
fgets.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
fileno.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
fileno.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
fileno.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
fileno.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
fileno.o: /user/os/svn/pmon/sys/sys/endian.h
fileno.o: /user/os/svn/pmon/sys/sys/cdefs.h
fileno.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
fileno.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
fprintf.o: /user/os/svn/pmon/include/stdio.h
fprintf.o: /user/os/svn/pmon/sys/sys/types.h
fprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
fprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
fprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
fprintf.o: /user/os/svn/pmon/sys/sys/endian.h
fprintf.o: /user/os/svn/pmon/sys/sys/cdefs.h
fprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
fprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
fprintf.o: /user/os/svn/pmon/include/stdarg.h
fprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/stdarg.h
fprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/va-mips.h
fputs.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
fputs.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
fputs.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
fputs.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
fputs.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
fputs.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
fputs.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
fputs.o: /user/os/svn/pmon/include/unistd.h
fputs.o: /user/os/svn/pmon/sys/sys/unistd.h /user/os/svn/pmon/sys/sys/time.h
fputs.o: /user/os/svn/pmon/include/time.h
fread.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
fread.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
fread.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
fread.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
fread.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
fread.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
fread.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
fread.o: /user/os/svn/pmon/include/unistd.h
fread.o: /user/os/svn/pmon/sys/sys/unistd.h /user/os/svn/pmon/sys/sys/time.h
fread.o: /user/os/svn/pmon/include/time.h
fseek.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
fseek.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
fseek.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
fseek.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
fseek.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
fseek.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
fseek.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
fwrite.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
fwrite.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
fwrite.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
fwrite.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
fwrite.o: /user/os/svn/pmon/sys/sys/endian.h
fwrite.o: /user/os/svn/pmon/sys/sys/cdefs.h
fwrite.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
fwrite.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
fwrite.o: /user/os/svn/pmon/include/unistd.h
fwrite.o: /user/os/svn/pmon/sys/sys/unistd.h /user/os/svn/pmon/sys/sys/time.h
fwrite.o: /user/os/svn/pmon/include/time.h
getc.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
getc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
getc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
getc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
getc.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
getc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
getc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
getchar.o: /user/os/svn/pmon/include/stdio.h
getchar.o: /user/os/svn/pmon/sys/sys/types.h
getchar.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
getchar.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
getchar.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
getchar.o: /user/os/svn/pmon/sys/sys/endian.h
getchar.o: /user/os/svn/pmon/sys/sys/cdefs.h
getchar.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
getchar.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
gethostnamadr.o: /user/os/svn/pmon/sys/sys/param.h
gethostnamadr.o: /user/os/svn/pmon/sys/sys/types.h
gethostnamadr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
gethostnamadr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
gethostnamadr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
gethostnamadr.o: /user/os/svn/pmon/sys/sys/endian.h
gethostnamadr.o: /user/os/svn/pmon/sys/sys/cdefs.h
gethostnamadr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
gethostnamadr.o: /user/os/svn/pmon/sys/sys/simplelock.h
gethostnamadr.o: /user/os/svn/pmon/sys/sys/syslimits.h
gethostnamadr.o: /user/os/svn/pmon/sys/sys/signal.h
gethostnamadr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/signal.h
gethostnamadr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cpu.h
gethostnamadr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/psl.h
gethostnamadr.o: /user/os/svn/pmon/sys/sys/siginfo.h
gethostnamadr.o: /user/os/svn/pmon/sys/sys/time.h
gethostnamadr.o: /user/os/svn/pmon/include/time.h
gethostnamadr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/param.h
gethostnamadr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/limits.h
gethostnamadr.o: /user/os/svn/pmon/sys/sys/socket.h
gethostnamadr.o: /user/os/svn/pmon/sys/netinet/in.h
gethostnamadr.o: /user/os/svn/pmon/include/arpa/inet.h
gethostnamadr.o: /user/os/svn/pmon/include/netdb.h
gethostnamadr.o: /user/os/svn/pmon/include/stdio.h
gethostnamadr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
gethostnamadr.o: /user/os/svn/pmon/include/ctype.h
gethostnamadr.o: /user/os/svn/pmon/include/errno.h
gethostnamadr.o: /user/os/svn/pmon/include/string.h
gethostnamadr.o: /user/os/svn/pmon/include/arpa/nameser.h
gethostnamadr.o: /user/os/svn/pmon/include/resolv.h
getopt.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
getopt.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
getopt.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
getopt.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
getopt.o: /user/os/svn/pmon/sys/sys/endian.h
getopt.o: /user/os/svn/pmon/sys/sys/cdefs.h
getopt.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
getopt.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
getopt.o: /user/os/svn/pmon/include/stdlib.h
getopt.o: /user/os/svn/pmon/include/string.h
getprotoname.o: /user/os/svn/pmon/include/netdb.h
getprotoname.o: /user/os/svn/pmon/sys/sys/param.h
getprotoname.o: /user/os/svn/pmon/sys/sys/types.h
getprotoname.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
getprotoname.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
getprotoname.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
getprotoname.o: /user/os/svn/pmon/sys/sys/endian.h
getprotoname.o: /user/os/svn/pmon/sys/sys/cdefs.h
getprotoname.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
getprotoname.o: /user/os/svn/pmon/sys/sys/simplelock.h
getprotoname.o: /user/os/svn/pmon/sys/sys/syslimits.h
getprotoname.o: /user/os/svn/pmon/sys/sys/signal.h
getprotoname.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/signal.h
getprotoname.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cpu.h
getprotoname.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/psl.h
getprotoname.o: /user/os/svn/pmon/sys/sys/siginfo.h
getprotoname.o: /user/os/svn/pmon/sys/sys/time.h
getprotoname.o: /user/os/svn/pmon/include/time.h
getprotoname.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/param.h
getprotoname.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/limits.h
getprotoname.o: /user/os/svn/pmon/include/string.h
getprotoname.o: /user/os/svn/pmon/sys/netinet/in.h
gets.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
gets.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
gets.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
gets.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
gets.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
gets.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
gets.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
getservbyname.o: /user/os/svn/pmon/include/netdb.h
getservbyname.o: /user/os/svn/pmon/sys/sys/param.h
getservbyname.o: /user/os/svn/pmon/sys/sys/types.h
getservbyname.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
getservbyname.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
getservbyname.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
getservbyname.o: /user/os/svn/pmon/sys/sys/endian.h
getservbyname.o: /user/os/svn/pmon/sys/sys/cdefs.h
getservbyname.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
getservbyname.o: /user/os/svn/pmon/sys/sys/simplelock.h
getservbyname.o: /user/os/svn/pmon/sys/sys/syslimits.h
getservbyname.o: /user/os/svn/pmon/sys/sys/signal.h
getservbyname.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/signal.h
getservbyname.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cpu.h
getservbyname.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/psl.h
getservbyname.o: /user/os/svn/pmon/sys/sys/siginfo.h
getservbyname.o: /user/os/svn/pmon/sys/sys/time.h
getservbyname.o: /user/os/svn/pmon/include/time.h
getservbyname.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/param.h
getservbyname.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/limits.h
getservbyname.o: /user/os/svn/pmon/include/string.h
getservent.o: /user/os/svn/pmon/sys/sys/types.h
getservent.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
getservent.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
getservent.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
getservent.o: /user/os/svn/pmon/sys/sys/endian.h
getservent.o: /user/os/svn/pmon/sys/sys/cdefs.h
getservent.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
getservent.o: /user/os/svn/pmon/sys/sys/socket.h
getservent.o: /user/os/svn/pmon/include/netdb.h
getservent.o: /user/os/svn/pmon/sys/sys/param.h
getservent.o: /user/os/svn/pmon/sys/sys/simplelock.h
getservent.o: /user/os/svn/pmon/sys/sys/syslimits.h
getservent.o: /user/os/svn/pmon/sys/sys/signal.h
getservent.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/signal.h
getservent.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cpu.h
getservent.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/psl.h
getservent.o: /user/os/svn/pmon/sys/sys/siginfo.h
getservent.o: /user/os/svn/pmon/sys/sys/time.h
getservent.o: /user/os/svn/pmon/include/time.h
getservent.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/param.h
getservent.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/limits.h
getservent.o: /user/os/svn/pmon/include/stdio.h
getservent.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
getservent.o: /user/os/svn/pmon/include/string.h
getservent.o: /user/os/svn/pmon/include/stdlib.h
getword.o: /user/os/svn/pmon/include/string.h
getword.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
getword.o: /user/os/svn/pmon/sys/sys/cdefs.h
getword.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
getword.o: /user/os/svn/pmon/include/ctype.h
index.o: /user/os/svn/pmon/include/string.h
index.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
index.o: /user/os/svn/pmon/sys/sys/cdefs.h
index.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
inet_addr.o: /user/os/svn/pmon/sys/sys/param.h
inet_addr.o: /user/os/svn/pmon/sys/sys/types.h
inet_addr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
inet_addr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
inet_addr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
inet_addr.o: /user/os/svn/pmon/sys/sys/endian.h
inet_addr.o: /user/os/svn/pmon/sys/sys/cdefs.h
inet_addr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
inet_addr.o: /user/os/svn/pmon/sys/sys/simplelock.h
inet_addr.o: /user/os/svn/pmon/sys/sys/syslimits.h
inet_addr.o: /user/os/svn/pmon/sys/sys/signal.h
inet_addr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/signal.h
inet_addr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cpu.h
inet_addr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/psl.h
inet_addr.o: /user/os/svn/pmon/sys/sys/siginfo.h
inet_addr.o: /user/os/svn/pmon/sys/sys/time.h
inet_addr.o: /user/os/svn/pmon/include/time.h
inet_addr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/param.h
inet_addr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/limits.h
inet_addr.o: /user/os/svn/pmon/sys/netinet/in.h
inet_addr.o: /user/os/svn/pmon/include/arpa/inet.h
inet_addr.o: /user/os/svn/pmon/include/ctype.h
lseek.o: /user/os/svn/pmon/include/termio.h
lseek.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
lseek.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
lseek.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
lseek.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
lseek.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
lseek.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
lseek.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
lseek.o: /user/os/svn/pmon/include/queue.h /user/os/svn/pmon/include/errno.h
lseek.o: /user/os/svn/pmon/include/unistd.h
lseek.o: /user/os/svn/pmon/sys/sys/unistd.h /user/os/svn/pmon/sys/sys/time.h
lseek.o: /user/os/svn/pmon/include/time.h /user/os/svn/pmon/include/file.h
lseek.o: /user/os/svn/pmon/sys/sys/queue.h
malloc.o: /user/os/svn/pmon/sys/sys/types.h
malloc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
malloc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
malloc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
malloc.o: /user/os/svn/pmon/sys/sys/endian.h
malloc.o: /user/os/svn/pmon/sys/sys/cdefs.h
malloc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
malloc.o: /user/os/svn/pmon/include/stdlib.h
malloc.o: /user/os/svn/pmon/include/unistd.h
malloc.o: /user/os/svn/pmon/sys/sys/unistd.h /user/os/svn/pmon/sys/sys/time.h
malloc.o: /user/os/svn/pmon/include/time.h
memchr.o: /user/os/svn/pmon/include/string.h
memchr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
memchr.o: /user/os/svn/pmon/sys/sys/cdefs.h
memchr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
memset.o: /user/os/svn/pmon/sys/sys/cdefs.h
memset.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
memset.o: /user/os/svn/pmon/sys/sys/types.h
memset.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
memset.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
memset.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
memset.o: /user/os/svn/pmon/sys/sys/endian.h
memset.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/limits.h
misc.o: /user/os/svn/pmon/include/stddef.h
misc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
misc.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
misc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
misc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
misc.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
misc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
misc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
misc.o: /user/os/svn/pmon/include/string.h /user/os/svn/pmon/include/stdlib.h
misc.o: /user/os/svn/pmon/include/unistd.h /user/os/svn/pmon/sys/sys/unistd.h
misc.o: /user/os/svn/pmon/sys/sys/time.h /user/os/svn/pmon/include/time.h
misc.o: /user/os/svn/pmon/include/ctype.h /user/os/svn/pmon/sys/sys/errno.h
modf.o: /user/os/svn/pmon/include/math.h
open.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
open.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
open.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
open.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
open.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
open.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
open.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
open.o: /user/os/svn/pmon/include/string.h /user/os/svn/pmon/include/file.h
open.o: /user/os/svn/pmon/sys/sys/queue.h /user/os/svn/pmon/include/fcntl.h
open.o: /user/os/svn/pmon/sys/sys/fcntl.h /user/os/svn/pmon/include/errno.h
pmalloc.o: /user/os/svn/pmon/sys/sys/types.h
pmalloc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
pmalloc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
pmalloc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
pmalloc.o: /user/os/svn/pmon/sys/sys/endian.h
pmalloc.o: /user/os/svn/pmon/sys/sys/cdefs.h
pmalloc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
pmalloc.o: /user/os/svn/pmon/include/string.h
pmalloc.o: /user/os/svn/pmon/include/stdlib.h
pmalloc.o: /user/os/svn/pmon/include/unistd.h
pmalloc.o: /user/os/svn/pmon/sys/sys/unistd.h
pmalloc.o: /user/os/svn/pmon/sys/sys/time.h /user/os/svn/pmon/include/time.h
printf.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
printf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
printf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
printf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
printf.o: /user/os/svn/pmon/sys/sys/endian.h
printf.o: /user/os/svn/pmon/sys/sys/cdefs.h
printf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
printf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
printf.o: /user/os/svn/pmon/include/stdarg.h
printf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/stdarg.h
printf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/va-mips.h
putc.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
putc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
putc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
putc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
putc.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
putc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
putc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
putc.o: /user/os/svn/pmon/include/unistd.h /user/os/svn/pmon/sys/sys/unistd.h
putc.o: /user/os/svn/pmon/sys/sys/time.h /user/os/svn/pmon/include/time.h
putchar.o: /user/os/svn/pmon/include/stdio.h
putchar.o: /user/os/svn/pmon/sys/sys/types.h
putchar.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
putchar.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
putchar.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
putchar.o: /user/os/svn/pmon/sys/sys/endian.h
putchar.o: /user/os/svn/pmon/sys/sys/cdefs.h
putchar.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
putchar.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
puts.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
puts.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
puts.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
puts.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
puts.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
puts.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
puts.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
qsort.o: /user/os/svn/pmon/sys/sys/types.h
qsort.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
qsort.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
qsort.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
qsort.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
qsort.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
qsort.o: /user/os/svn/pmon/include/stdlib.h
queue.o: /user/os/svn/pmon/sys/sys/types.h
queue.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
queue.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
queue.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
queue.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
queue.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
queue.o: /user/os/svn/pmon/include/stdio.h
queue.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
queue.o: /user/os/svn/pmon/include/stdlib.h /user/os/svn/pmon/include/queue.h
rand.o: /user/os/svn/pmon/include/stdlib.h
rand.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
rand.o: /user/os/svn/pmon/sys/sys/types.h
rand.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
rand.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
rand.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
rand.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
read.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
read.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
read.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
read.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
read.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
read.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
read.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
read.o: /user/os/svn/pmon/include/file.h /user/os/svn/pmon/sys/sys/queue.h
read.o: /user/os/svn/pmon/include/unistd.h /user/os/svn/pmon/sys/sys/unistd.h
read.o: /user/os/svn/pmon/sys/sys/time.h /user/os/svn/pmon/include/time.h
realloc.o: /user/os/svn/pmon/include/string.h
realloc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
realloc.o: /user/os/svn/pmon/sys/sys/cdefs.h
realloc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
realloc.o: /user/os/svn/pmon/include/stdlib.h
realloc.o: /user/os/svn/pmon/sys/sys/types.h
realloc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
realloc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
realloc.o: /user/os/svn/pmon/sys/sys/endian.h
recv.o: /user/os/svn/pmon/sys/sys/types.h
recv.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
recv.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
recv.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
recv.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
recv.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
recv.o: /user/os/svn/pmon/sys/sys/socket.h /user/os/svn/pmon/include/stdio.h
recv.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
res_comp.o: /user/os/svn/pmon/sys/sys/types.h
res_comp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
res_comp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
res_comp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
res_comp.o: /user/os/svn/pmon/sys/sys/endian.h
res_comp.o: /user/os/svn/pmon/sys/sys/cdefs.h
res_comp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
res_comp.o: /user/os/svn/pmon/sys/sys/param.h
res_comp.o: /user/os/svn/pmon/sys/sys/simplelock.h
res_comp.o: /user/os/svn/pmon/sys/sys/syslimits.h
res_comp.o: /user/os/svn/pmon/sys/sys/signal.h
res_comp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/signal.h
res_comp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cpu.h
res_comp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/psl.h
res_comp.o: /user/os/svn/pmon/sys/sys/siginfo.h
res_comp.o: /user/os/svn/pmon/sys/sys/time.h /user/os/svn/pmon/include/time.h
res_comp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/param.h
res_comp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/limits.h
res_comp.o: /user/os/svn/pmon/sys/netinet/in.h
res_comp.o: /user/os/svn/pmon/include/arpa/nameser.h
res_comp.o: /user/os/svn/pmon/include/stdio.h
res_comp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
res_comp.o: /user/os/svn/pmon/include/resolv.h
res_comp.o: /user/os/svn/pmon/include/ctype.h
res_comp.o: /user/os/svn/pmon/include/unistd.h
res_comp.o: /user/os/svn/pmon/sys/sys/unistd.h
res_comp.o: /user/os/svn/pmon/include/string.h
res_init.o: /user/os/svn/pmon/sys/sys/types.h
res_init.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
res_init.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
res_init.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
res_init.o: /user/os/svn/pmon/sys/sys/endian.h
res_init.o: /user/os/svn/pmon/sys/sys/cdefs.h
res_init.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
res_init.o: /user/os/svn/pmon/sys/sys/param.h
res_init.o: /user/os/svn/pmon/sys/sys/simplelock.h
res_init.o: /user/os/svn/pmon/sys/sys/syslimits.h
res_init.o: /user/os/svn/pmon/sys/sys/signal.h
res_init.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/signal.h
res_init.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cpu.h
res_init.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/psl.h
res_init.o: /user/os/svn/pmon/sys/sys/siginfo.h
res_init.o: /user/os/svn/pmon/sys/sys/time.h /user/os/svn/pmon/include/time.h
res_init.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/param.h
res_init.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/limits.h
res_init.o: /user/os/svn/pmon/sys/sys/socket.h
res_init.o: /user/os/svn/pmon/sys/netinet/in.h
res_init.o: /user/os/svn/pmon/include/arpa/inet.h
res_init.o: /user/os/svn/pmon/include/arpa/nameser.h
res_init.o: /user/os/svn/pmon/include/stdio.h
res_init.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
res_init.o: /user/os/svn/pmon/include/ctype.h
res_init.o: /user/os/svn/pmon/include/resolv.h
res_init.o: /user/os/svn/pmon/include/unistd.h
res_init.o: /user/os/svn/pmon/sys/sys/unistd.h
res_init.o: /user/os/svn/pmon/include/stdlib.h
res_init.o: /user/os/svn/pmon/include/string.h
res_mkquery.o: /user/os/svn/pmon/sys/sys/types.h
res_mkquery.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
res_mkquery.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
res_mkquery.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
res_mkquery.o: /user/os/svn/pmon/sys/sys/endian.h
res_mkquery.o: /user/os/svn/pmon/sys/sys/cdefs.h
res_mkquery.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
res_mkquery.o: /user/os/svn/pmon/sys/sys/param.h
res_mkquery.o: /user/os/svn/pmon/sys/sys/simplelock.h
res_mkquery.o: /user/os/svn/pmon/sys/sys/syslimits.h
res_mkquery.o: /user/os/svn/pmon/sys/sys/signal.h
res_mkquery.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/signal.h
res_mkquery.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cpu.h
res_mkquery.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/psl.h
res_mkquery.o: /user/os/svn/pmon/sys/sys/siginfo.h
res_mkquery.o: /user/os/svn/pmon/sys/sys/time.h
res_mkquery.o: /user/os/svn/pmon/include/time.h
res_mkquery.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/param.h
res_mkquery.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/limits.h
res_mkquery.o: /user/os/svn/pmon/sys/netinet/in.h
res_mkquery.o: /user/os/svn/pmon/include/arpa/nameser.h
res_mkquery.o: /user/os/svn/pmon/include/stdio.h
res_mkquery.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
res_mkquery.o: /user/os/svn/pmon/include/netdb.h
res_mkquery.o: /user/os/svn/pmon/include/resolv.h
res_mkquery.o: /user/os/svn/pmon/include/string.h
res_query.o: /user/os/svn/pmon/sys/sys/types.h
res_query.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
res_query.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
res_query.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
res_query.o: /user/os/svn/pmon/sys/sys/endian.h
res_query.o: /user/os/svn/pmon/sys/sys/cdefs.h
res_query.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
res_query.o: /user/os/svn/pmon/sys/sys/param.h
res_query.o: /user/os/svn/pmon/sys/sys/simplelock.h
res_query.o: /user/os/svn/pmon/sys/sys/syslimits.h
res_query.o: /user/os/svn/pmon/sys/sys/signal.h
res_query.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/signal.h
res_query.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cpu.h
res_query.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/psl.h
res_query.o: /user/os/svn/pmon/sys/sys/siginfo.h
res_query.o: /user/os/svn/pmon/sys/sys/time.h
res_query.o: /user/os/svn/pmon/include/time.h
res_query.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/param.h
res_query.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/limits.h
res_query.o: /user/os/svn/pmon/sys/netinet/in.h
res_query.o: /user/os/svn/pmon/include/arpa/inet.h
res_query.o: /user/os/svn/pmon/include/arpa/nameser.h
res_query.o: /user/os/svn/pmon/include/stdio.h
res_query.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
res_query.o: /user/os/svn/pmon/include/netdb.h
res_query.o: /user/os/svn/pmon/include/resolv.h
res_query.o: /user/os/svn/pmon/include/ctype.h
res_query.o: /user/os/svn/pmon/include/errno.h
res_query.o: /user/os/svn/pmon/include/stdlib.h
res_query.o: /user/os/svn/pmon/include/string.h
res_query.o: /user/os/svn/pmon/include/unistd.h
res_query.o: /user/os/svn/pmon/sys/sys/unistd.h
res_send.o: /user/os/svn/pmon/sys/sys/types.h
res_send.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
res_send.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
res_send.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
res_send.o: /user/os/svn/pmon/sys/sys/endian.h
res_send.o: /user/os/svn/pmon/sys/sys/cdefs.h
res_send.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
res_send.o: /user/os/svn/pmon/sys/sys/param.h
res_send.o: /user/os/svn/pmon/sys/sys/simplelock.h
res_send.o: /user/os/svn/pmon/sys/sys/syslimits.h
res_send.o: /user/os/svn/pmon/sys/sys/signal.h
res_send.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/signal.h
res_send.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cpu.h
res_send.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/psl.h
res_send.o: /user/os/svn/pmon/sys/sys/siginfo.h
res_send.o: /user/os/svn/pmon/sys/sys/time.h /user/os/svn/pmon/include/time.h
res_send.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/param.h
res_send.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/limits.h
res_send.o: /user/os/svn/pmon/sys/sys/socket.h
res_send.o: /user/os/svn/pmon/sys/sys/uio.h
res_send.o: /user/os/svn/pmon/sys/netinet/in.h
res_send.o: /user/os/svn/pmon/include/arpa/nameser.h
res_send.o: /user/os/svn/pmon/include/arpa/inet.h
res_send.o: /user/os/svn/pmon/include/stdio.h
res_send.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
res_send.o: /user/os/svn/pmon/include/netdb.h
res_send.o: /user/os/svn/pmon/include/errno.h
res_send.o: /user/os/svn/pmon/include/resolv.h
res_send.o: /user/os/svn/pmon/include/stdlib.h
res_send.o: /user/os/svn/pmon/include/string.h
res_send.o: /user/os/svn/pmon/include/unistd.h
res_send.o: /user/os/svn/pmon/sys/sys/unistd.h
rindex.o: /user/os/svn/pmon/include/string.h
rindex.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
rindex.o: /user/os/svn/pmon/sys/sys/cdefs.h
rindex.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
sbrk.o: /user/os/svn/pmon/sys/sys/types.h
sbrk.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
sbrk.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
sbrk.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
sbrk.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
sbrk.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
sbrk.o: /user/os/svn/pmon/include/unistd.h /user/os/svn/pmon/sys/sys/unistd.h
sbrk.o: /user/os/svn/pmon/sys/sys/time.h /user/os/svn/pmon/include/time.h
scanf.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
scanf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
scanf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
scanf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
scanf.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
scanf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
scanf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
scanf.o: /user/os/svn/pmon/include/stdarg.h
scanf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/stdarg.h
scanf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/va-mips.h
scanf.o: /user/os/svn/pmon/include/string.h /user/os/svn/pmon/include/ctype.h
scanf.o: /user/os/svn/pmon/include/pmon.h
scanf.o: /user/os/svn/pmon/sys/arch/mips/include/pmon_arch.h
scanf.o: /user/os/svn/pmon/include/progress.h
scanf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/target/pmon_target.h
scanf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/target/bonito.h
send.o: /user/os/svn/pmon/sys/sys/types.h
send.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
send.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
send.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
send.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
send.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
send.o: /user/os/svn/pmon/sys/sys/socket.h /user/os/svn/pmon/include/stdio.h
send.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
signal.o: /user/os/svn/pmon/include/termio.h
signal.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
signal.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
signal.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
signal.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
signal.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
signal.o: /user/os/svn/pmon/sys/sys/endian.h
signal.o: /user/os/svn/pmon/sys/sys/cdefs.h
signal.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
signal.o: /user/os/svn/pmon/include/queue.h /user/os/svn/pmon/include/errno.h
signal.o: /user/os/svn/pmon/include/setjmp.h
signal.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/setjmp.h
signal.o: /user/os/svn/pmon/include/signal.h
signal.o: /user/os/svn/pmon/sys/sys/signal.h
signal.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/signal.h
signal.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cpu.h
signal.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/psl.h
signal.o: /user/os/svn/pmon/sys/sys/siginfo.h
signal.o: /user/os/svn/pmon/sys/sys/time.h /user/os/svn/pmon/include/time.h
signal.o: /user/os/svn/pmon/sys/sys/ioctl.h
signal.o: /user/os/svn/pmon/sys/sys/ttycom.h
signal.o: /user/os/svn/pmon/sys/sys/ioccom.h /user/os/svn/pmon/sys/sys/dkio.h
signal.o: /user/os/svn/pmon/sys/sys/filio.h
signal.o: /user/os/svn/pmon/sys/sys/sockio.h
sigsetops.o: /user/os/svn/pmon/sys/sys/types.h
sigsetops.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
sigsetops.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
sigsetops.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
sigsetops.o: /user/os/svn/pmon/sys/sys/endian.h
sigsetops.o: /user/os/svn/pmon/sys/sys/cdefs.h
sigsetops.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
sigsetops.o: /user/os/svn/pmon/include/errno.h
sigsetops.o: /user/os/svn/pmon/include/signal.h
sigsetops.o: /user/os/svn/pmon/sys/sys/signal.h
sigsetops.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/signal.h
sigsetops.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cpu.h
sigsetops.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/psl.h
sigsetops.o: /user/os/svn/pmon/sys/sys/siginfo.h
sigsetops.o: /user/os/svn/pmon/sys/sys/time.h
sigsetops.o: /user/os/svn/pmon/include/time.h
sprintf.o: /user/os/svn/pmon/include/stdio.h
sprintf.o: /user/os/svn/pmon/sys/sys/types.h
sprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
sprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
sprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
sprintf.o: /user/os/svn/pmon/sys/sys/endian.h
sprintf.o: /user/os/svn/pmon/sys/sys/cdefs.h
sprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
sprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
sprintf.o: /user/os/svn/pmon/include/stdarg.h
sprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/stdarg.h
sprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/va-mips.h
stdio.o: /user/os/svn/pmon/include/string.h
stdio.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
stdio.o: /user/os/svn/pmon/sys/sys/cdefs.h
stdio.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
stdio.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
stdio.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
stdio.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
stdio.o: /user/os/svn/pmon/sys/sys/endian.h
stdio.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
stdio.o: /user/os/svn/pmon/include/fcntl.h /user/os/svn/pmon/sys/sys/fcntl.h
str2cc.o: /user/os/svn/pmon/include/string.h
str2cc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
str2cc.o: /user/os/svn/pmon/sys/sys/cdefs.h
str2cc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
str_fmt.o: /user/os/svn/pmon/include/string.h
str_fmt.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
str_fmt.o: /user/os/svn/pmon/sys/sys/cdefs.h
str_fmt.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strbalp.o: /user/os/svn/pmon/include/string.h
strbalp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strbalp.o: /user/os/svn/pmon/sys/sys/cdefs.h
strbalp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strbequ.o: /user/os/svn/pmon/include/string.h
strbequ.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strbequ.o: /user/os/svn/pmon/sys/sys/cdefs.h
strbequ.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strcasecmp.o: /user/os/svn/pmon/include/string.h
strcasecmp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strcasecmp.o: /user/os/svn/pmon/sys/sys/cdefs.h
strcasecmp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strcasecmp.o: /user/os/svn/pmon/include/ctype.h
strcat.o: /user/os/svn/pmon/include/string.h
strcat.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strcat.o: /user/os/svn/pmon/sys/sys/cdefs.h
strcat.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strccat.o: /user/os/svn/pmon/include/string.h
strccat.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strccat.o: /user/os/svn/pmon/sys/sys/cdefs.h
strccat.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strchr.o: /user/os/svn/pmon/include/string.h
strchr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strchr.o: /user/os/svn/pmon/sys/sys/cdefs.h
strchr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strcmp.o: /user/os/svn/pmon/sys/sys/types.h
strcmp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
strcmp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strcmp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
strcmp.o: /user/os/svn/pmon/sys/sys/endian.h
strcmp.o: /user/os/svn/pmon/sys/sys/cdefs.h
strcmp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strcmp.o: /user/os/svn/pmon/include/string.h
strcpy.o: /user/os/svn/pmon/include/string.h
strcpy.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strcpy.o: /user/os/svn/pmon/sys/sys/cdefs.h
strcpy.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strcspn.o: /user/os/svn/pmon/include/string.h
strcspn.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strcspn.o: /user/os/svn/pmon/sys/sys/cdefs.h
strcspn.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strdchr.o: /user/os/svn/pmon/include/string.h
strdchr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strdchr.o: /user/os/svn/pmon/sys/sys/cdefs.h
strdchr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strempty.o: /user/os/svn/pmon/include/string.h
strempty.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strempty.o: /user/os/svn/pmon/sys/sys/cdefs.h
strempty.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strempty.o: /user/os/svn/pmon/include/ctype.h
strichr.o: /user/os/svn/pmon/include/string.h
strichr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strichr.o: /user/os/svn/pmon/sys/sys/cdefs.h
strichr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
striequ.o: /user/os/svn/pmon/include/string.h
striequ.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
striequ.o: /user/os/svn/pmon/sys/sys/cdefs.h
striequ.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
striequ.o: /user/os/svn/pmon/include/ctype.h
stristr.o: /user/os/svn/pmon/include/string.h
stristr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
stristr.o: /user/os/svn/pmon/sys/sys/cdefs.h
stristr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strlen.o: /user/os/svn/pmon/include/string.h
strlen.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strlen.o: /user/os/svn/pmon/sys/sys/cdefs.h
strlen.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strmerge.o: /user/os/svn/pmon/include/string.h
strmerge.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strmerge.o: /user/os/svn/pmon/sys/sys/cdefs.h
strmerge.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strncat.o: /user/os/svn/pmon/include/string.h
strncat.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strncat.o: /user/os/svn/pmon/sys/sys/cdefs.h
strncat.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strnchr.o: /user/os/svn/pmon/include/string.h
strnchr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strnchr.o: /user/os/svn/pmon/sys/sys/cdefs.h
strnchr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strncmp.o: /user/os/svn/pmon/include/string.h
strncmp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strncmp.o: /user/os/svn/pmon/sys/sys/cdefs.h
strncmp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strncpy.o: /user/os/svn/pmon/include/string.h
strncpy.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strncpy.o: /user/os/svn/pmon/sys/sys/cdefs.h
strncpy.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strnwrd.o: /user/os/svn/pmon/include/string.h
strnwrd.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strnwrd.o: /user/os/svn/pmon/sys/sys/cdefs.h
strnwrd.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strnwrd.o: /user/os/svn/pmon/include/ctype.h
strpat.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
strpat.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
strpat.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strpat.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
strpat.o: /user/os/svn/pmon/sys/sys/endian.h
strpat.o: /user/os/svn/pmon/sys/sys/cdefs.h
strpat.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strpat.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
strpat.o: /user/os/svn/pmon/include/string.h
strpbrk.o: /user/os/svn/pmon/include/string.h
strpbrk.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strpbrk.o: /user/os/svn/pmon/sys/sys/cdefs.h
strpbrk.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strposn.o: /user/os/svn/pmon/include/string.h
strposn.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strposn.o: /user/os/svn/pmon/sys/sys/cdefs.h
strposn.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strrchr.o: /user/os/svn/pmon/include/string.h
strrchr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strrchr.o: /user/os/svn/pmon/sys/sys/cdefs.h
strrchr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strrpset.o: /user/os/svn/pmon/include/string.h
strrpset.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strrpset.o: /user/os/svn/pmon/sys/sys/cdefs.h
strrpset.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strrrot.o: /user/os/svn/pmon/include/string.h
strrrot.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strrrot.o: /user/os/svn/pmon/sys/sys/cdefs.h
strrrot.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strrset.o: /user/os/svn/pmon/include/string.h
strrset.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strrset.o: /user/os/svn/pmon/sys/sys/cdefs.h
strrset.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strset.o: /user/os/svn/pmon/include/string.h
strset.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strset.o: /user/os/svn/pmon/sys/sys/cdefs.h
strset.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strsort.o: /user/os/svn/pmon/include/string.h
strsort.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strsort.o: /user/os/svn/pmon/sys/sys/cdefs.h
strsort.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strspn.o: /user/os/svn/pmon/include/string.h
strspn.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strspn.o: /user/os/svn/pmon/sys/sys/cdefs.h
strspn.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strstr.o: /user/os/svn/pmon/include/string.h
strstr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strstr.o: /user/os/svn/pmon/sys/sys/cdefs.h
strstr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strtok.o: /user/os/svn/pmon/include/string.h
strtok.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strtok.o: /user/os/svn/pmon/sys/sys/cdefs.h
strtok.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strtoupp.o: /user/os/svn/pmon/include/string.h
strtoupp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
strtoupp.o: /user/os/svn/pmon/sys/sys/cdefs.h
strtoupp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
strtoupp.o: /user/os/svn/pmon/include/ctype.h
terms.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
terms.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
terms.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
terms.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
terms.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
terms.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
terms.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
terms.o: /user/os/svn/pmon/include/termio.h /user/os/svn/pmon/include/queue.h
tolower_.o: /user/os/svn/pmon/include/stdio.h
tolower_.o: /user/os/svn/pmon/sys/sys/types.h
tolower_.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
tolower_.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
tolower_.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
tolower_.o: /user/os/svn/pmon/sys/sys/endian.h
tolower_.o: /user/os/svn/pmon/sys/sys/cdefs.h
tolower_.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
tolower_.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
tolower_.o: /user/os/svn/pmon/include/ctype.h
toupper_.o: /user/os/svn/pmon/include/stdio.h
toupper_.o: /user/os/svn/pmon/sys/sys/types.h
toupper_.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
toupper_.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
toupper_.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
toupper_.o: /user/os/svn/pmon/sys/sys/endian.h
toupper_.o: /user/os/svn/pmon/sys/sys/cdefs.h
toupper_.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
toupper_.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
toupper_.o: /user/os/svn/pmon/include/ctype.h
ungetc.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
ungetc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
ungetc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
ungetc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
ungetc.o: /user/os/svn/pmon/sys/sys/endian.h
ungetc.o: /user/os/svn/pmon/sys/sys/cdefs.h
ungetc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
ungetc.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
vfprintf.o: /user/os/svn/pmon/include/stdio.h
vfprintf.o: /user/os/svn/pmon/sys/sys/types.h
vfprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
vfprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
vfprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
vfprintf.o: /user/os/svn/pmon/sys/sys/endian.h
vfprintf.o: /user/os/svn/pmon/sys/sys/cdefs.h
vfprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
vfprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
vfprintf.o: /user/os/svn/pmon/include/stdarg.h
vfprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/stdarg.h
vfprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/va-mips.h
vfprintf.o: /user/os/svn/pmon/include/string.h
vfprintf.o: /user/os/svn/pmon/include/stdlib.h
vsprintf.o: /user/os/svn/pmon/include/stdio.h
vsprintf.o: /user/os/svn/pmon/sys/sys/types.h
vsprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
vsprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
vsprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
vsprintf.o: /user/os/svn/pmon/sys/sys/endian.h
vsprintf.o: /user/os/svn/pmon/sys/sys/cdefs.h
vsprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
vsprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
vsprintf.o: /user/os/svn/pmon/include/stdarg.h
vsprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/stdarg.h
vsprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/va-mips.h
vsprintf.o: /user/os/svn/pmon/include/string.h
vsprintf.o: /user/os/svn/pmon/include/ctype.h
vsprintf.o: /user/os/svn/pmon/include/pmon.h
vsprintf.o: /user/os/svn/pmon/sys/arch/mips/include/pmon_arch.h
vsprintf.o: /user/os/svn/pmon/include/progress.h
vsprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/target/pmon_target.h
vsprintf.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/target/bonito.h
write.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
write.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
write.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
write.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
write.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
write.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
write.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
write.o: /user/os/svn/pmon/include/file.h /user/os/svn/pmon/sys/sys/queue.h
write.o: /user/os/svn/pmon/include/unistd.h
write.o: /user/os/svn/pmon/sys/sys/unistd.h /user/os/svn/pmon/sys/sys/time.h
write.o: /user/os/svn/pmon/include/time.h
getbaud.o: /user/os/svn/pmon/include/stdio.h
getbaud.o: /user/os/svn/pmon/sys/sys/types.h
getbaud.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
getbaud.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
getbaud.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
getbaud.o: /user/os/svn/pmon/sys/sys/endian.h
getbaud.o: /user/os/svn/pmon/sys/sys/cdefs.h
getbaud.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
getbaud.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
getbaud.o: /user/os/svn/pmon/include/stdlib.h
getbaud.o: /user/os/svn/pmon/include/string.h
tcdrain.o: /user/os/svn/pmon/sys/sys/types.h
tcdrain.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
tcdrain.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
tcdrain.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
tcdrain.o: /user/os/svn/pmon/sys/sys/endian.h
tcdrain.o: /user/os/svn/pmon/sys/sys/cdefs.h
tcdrain.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
tcdrain.o: /user/os/svn/pmon/sys/sys/ioctl.h
tcdrain.o: /user/os/svn/pmon/sys/sys/ttycom.h
tcdrain.o: /user/os/svn/pmon/sys/sys/ioccom.h
tcdrain.o: /user/os/svn/pmon/sys/sys/dkio.h /user/os/svn/pmon/sys/sys/filio.h
tcdrain.o: /user/os/svn/pmon/sys/sys/sockio.h
tcdrain.o: /user/os/svn/pmon/sys/sys/termios.h
tcdrain.o: /user/os/svn/pmon/sys/sys/ttydefaults.h
tcflow.o: /user/os/svn/pmon/sys/sys/types.h
tcflow.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
tcflow.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
tcflow.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
tcflow.o: /user/os/svn/pmon/sys/sys/endian.h
tcflow.o: /user/os/svn/pmon/sys/sys/cdefs.h
tcflow.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
tcflow.o: /user/os/svn/pmon/sys/sys/ioctl.h
tcflow.o: /user/os/svn/pmon/sys/sys/ttycom.h
tcflow.o: /user/os/svn/pmon/sys/sys/ioccom.h /user/os/svn/pmon/sys/sys/dkio.h
tcflow.o: /user/os/svn/pmon/sys/sys/filio.h
tcflow.o: /user/os/svn/pmon/sys/sys/sockio.h
tcflow.o: /user/os/svn/pmon/sys/sys/termios.h
tcflow.o: /user/os/svn/pmon/sys/sys/ttydefaults.h
tcflow.o: /user/os/svn/pmon/include/unistd.h
tcflow.o: /user/os/svn/pmon/sys/sys/unistd.h /user/os/svn/pmon/sys/sys/time.h
tcflow.o: /user/os/svn/pmon/include/time.h /user/os/svn/pmon/include/errno.h
tcflush.o: /user/os/svn/pmon/sys/sys/types.h
tcflush.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
tcflush.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
tcflush.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
tcflush.o: /user/os/svn/pmon/sys/sys/endian.h
tcflush.o: /user/os/svn/pmon/sys/sys/cdefs.h
tcflush.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
tcflush.o: /user/os/svn/pmon/sys/sys/ioctl.h
tcflush.o: /user/os/svn/pmon/sys/sys/ttycom.h
tcflush.o: /user/os/svn/pmon/sys/sys/ioccom.h
tcflush.o: /user/os/svn/pmon/sys/sys/dkio.h /user/os/svn/pmon/sys/sys/filio.h
tcflush.o: /user/os/svn/pmon/sys/sys/sockio.h
tcflush.o: /user/os/svn/pmon/sys/sys/fcntl.h
tcflush.o: /user/os/svn/pmon/sys/sys/termios.h
tcflush.o: /user/os/svn/pmon/sys/sys/ttydefaults.h
tcflush.o: /user/os/svn/pmon/include/errno.h
tcgetattr.o: /user/os/svn/pmon/sys/sys/types.h
tcgetattr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
tcgetattr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
tcgetattr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
tcgetattr.o: /user/os/svn/pmon/sys/sys/endian.h
tcgetattr.o: /user/os/svn/pmon/sys/sys/cdefs.h
tcgetattr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
tcgetattr.o: /user/os/svn/pmon/sys/sys/ioctl.h
tcgetattr.o: /user/os/svn/pmon/sys/sys/ttycom.h
tcgetattr.o: /user/os/svn/pmon/sys/sys/ioccom.h
tcgetattr.o: /user/os/svn/pmon/sys/sys/dkio.h
tcgetattr.o: /user/os/svn/pmon/sys/sys/filio.h
tcgetattr.o: /user/os/svn/pmon/sys/sys/sockio.h
tcgetattr.o: /user/os/svn/pmon/sys/sys/termios.h
tcgetattr.o: /user/os/svn/pmon/sys/sys/ttydefaults.h
tcgetpgrp.o: /user/os/svn/pmon/sys/sys/types.h
tcgetpgrp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
tcgetpgrp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
tcgetpgrp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
tcgetpgrp.o: /user/os/svn/pmon/sys/sys/endian.h
tcgetpgrp.o: /user/os/svn/pmon/sys/sys/cdefs.h
tcgetpgrp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
tcgetpgrp.o: /user/os/svn/pmon/sys/sys/ioctl.h
tcgetpgrp.o: /user/os/svn/pmon/sys/sys/ttycom.h
tcgetpgrp.o: /user/os/svn/pmon/sys/sys/ioccom.h
tcgetpgrp.o: /user/os/svn/pmon/sys/sys/dkio.h
tcgetpgrp.o: /user/os/svn/pmon/sys/sys/filio.h
tcgetpgrp.o: /user/os/svn/pmon/sys/sys/sockio.h
tcgetpgrp.o: /user/os/svn/pmon/sys/sys/termios.h
tcgetpgrp.o: /user/os/svn/pmon/sys/sys/ttydefaults.h
tcsendbreak.o: /user/os/svn/pmon/sys/sys/types.h
tcsendbreak.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
tcsendbreak.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
tcsendbreak.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
tcsendbreak.o: /user/os/svn/pmon/sys/sys/endian.h
tcsendbreak.o: /user/os/svn/pmon/sys/sys/cdefs.h
tcsendbreak.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
tcsendbreak.o: /user/os/svn/pmon/sys/sys/ioctl.h
tcsendbreak.o: /user/os/svn/pmon/sys/sys/ttycom.h
tcsendbreak.o: /user/os/svn/pmon/sys/sys/ioccom.h
tcsendbreak.o: /user/os/svn/pmon/sys/sys/dkio.h
tcsendbreak.o: /user/os/svn/pmon/sys/sys/filio.h
tcsendbreak.o: /user/os/svn/pmon/sys/sys/sockio.h
tcsendbreak.o: /user/os/svn/pmon/sys/sys/tty.h
tcsendbreak.o: /user/os/svn/pmon/sys/sys/termios.h
tcsendbreak.o: /user/os/svn/pmon/sys/sys/ttydefaults.h
tcsendbreak.o: /user/os/svn/pmon/sys/sys/select.h
tcsendbreak.o: /user/os/svn/pmon/sys/sys/queue.h
tcsendbreak.o: /user/os/svn/pmon/sys/sys/time.h
tcsendbreak.o: /user/os/svn/pmon/include/time.h
tcsendbreak.o: /user/os/svn/pmon/sys/sys/fcntl.h
tcsendbreak.o: /user/os/svn/pmon/include/errno.h
tcsendbreak.o: /user/os/svn/pmon/include/stdio.h
tcsendbreak.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
tcsendbreak.o: /user/os/svn/pmon/include/unistd.h
tcsendbreak.o: /user/os/svn/pmon/sys/sys/unistd.h
tcsetattr.o: /user/os/svn/pmon/sys/sys/types.h
tcsetattr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
tcsetattr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
tcsetattr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
tcsetattr.o: /user/os/svn/pmon/sys/sys/endian.h
tcsetattr.o: /user/os/svn/pmon/sys/sys/cdefs.h
tcsetattr.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
tcsetattr.o: /user/os/svn/pmon/sys/sys/ioctl.h
tcsetattr.o: /user/os/svn/pmon/sys/sys/ttycom.h
tcsetattr.o: /user/os/svn/pmon/sys/sys/ioccom.h
tcsetattr.o: /user/os/svn/pmon/sys/sys/dkio.h
tcsetattr.o: /user/os/svn/pmon/sys/sys/filio.h
tcsetattr.o: /user/os/svn/pmon/sys/sys/sockio.h
tcsetattr.o: /user/os/svn/pmon/sys/sys/termios.h
tcsetattr.o: /user/os/svn/pmon/sys/sys/ttydefaults.h
tcsetattr.o: /user/os/svn/pmon/include/errno.h
tcsetpgrp.o: /user/os/svn/pmon/sys/sys/types.h
tcsetpgrp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
tcsetpgrp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
tcsetpgrp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
tcsetpgrp.o: /user/os/svn/pmon/sys/sys/endian.h
tcsetpgrp.o: /user/os/svn/pmon/sys/sys/cdefs.h
tcsetpgrp.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
tcsetpgrp.o: /user/os/svn/pmon/sys/sys/ioctl.h
tcsetpgrp.o: /user/os/svn/pmon/sys/sys/ttycom.h
tcsetpgrp.o: /user/os/svn/pmon/sys/sys/ioccom.h
tcsetpgrp.o: /user/os/svn/pmon/sys/sys/dkio.h
tcsetpgrp.o: /user/os/svn/pmon/sys/sys/filio.h
tcsetpgrp.o: /user/os/svn/pmon/sys/sys/sockio.h
tcsetpgrp.o: /user/os/svn/pmon/sys/sys/termios.h
tcsetpgrp.o: /user/os/svn/pmon/sys/sys/ttydefaults.h
cfgetispeed.o: /user/os/svn/pmon/sys/sys/types.h
cfgetispeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
cfgetispeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
cfgetispeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
cfgetispeed.o: /user/os/svn/pmon/sys/sys/endian.h
cfgetispeed.o: /user/os/svn/pmon/sys/sys/cdefs.h
cfgetispeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
cfgetispeed.o: /user/os/svn/pmon/sys/sys/ioctl.h
cfgetispeed.o: /user/os/svn/pmon/sys/sys/ttycom.h
cfgetispeed.o: /user/os/svn/pmon/sys/sys/ioccom.h
cfgetispeed.o: /user/os/svn/pmon/sys/sys/dkio.h
cfgetispeed.o: /user/os/svn/pmon/sys/sys/filio.h
cfgetispeed.o: /user/os/svn/pmon/sys/sys/sockio.h
cfgetispeed.o: /user/os/svn/pmon/sys/sys/termios.h
cfgetispeed.o: /user/os/svn/pmon/sys/sys/ttydefaults.h
cfgetospeed.o: /user/os/svn/pmon/sys/sys/types.h
cfgetospeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
cfgetospeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
cfgetospeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
cfgetospeed.o: /user/os/svn/pmon/sys/sys/endian.h
cfgetospeed.o: /user/os/svn/pmon/sys/sys/cdefs.h
cfgetospeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
cfgetospeed.o: /user/os/svn/pmon/sys/sys/ioctl.h
cfgetospeed.o: /user/os/svn/pmon/sys/sys/ttycom.h
cfgetospeed.o: /user/os/svn/pmon/sys/sys/ioccom.h
cfgetospeed.o: /user/os/svn/pmon/sys/sys/dkio.h
cfgetospeed.o: /user/os/svn/pmon/sys/sys/filio.h
cfgetospeed.o: /user/os/svn/pmon/sys/sys/sockio.h
cfgetospeed.o: /user/os/svn/pmon/sys/sys/termios.h
cfgetospeed.o: /user/os/svn/pmon/sys/sys/ttydefaults.h
cfmakeraw.o: /user/os/svn/pmon/sys/sys/types.h
cfmakeraw.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
cfmakeraw.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
cfmakeraw.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
cfmakeraw.o: /user/os/svn/pmon/sys/sys/endian.h
cfmakeraw.o: /user/os/svn/pmon/sys/sys/cdefs.h
cfmakeraw.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
cfmakeraw.o: /user/os/svn/pmon/sys/sys/ioctl.h
cfmakeraw.o: /user/os/svn/pmon/sys/sys/ttycom.h
cfmakeraw.o: /user/os/svn/pmon/sys/sys/ioccom.h
cfmakeraw.o: /user/os/svn/pmon/sys/sys/dkio.h
cfmakeraw.o: /user/os/svn/pmon/sys/sys/filio.h
cfmakeraw.o: /user/os/svn/pmon/sys/sys/sockio.h
cfmakeraw.o: /user/os/svn/pmon/sys/sys/termios.h
cfmakeraw.o: /user/os/svn/pmon/sys/sys/ttydefaults.h
cfsetispeed.o: /user/os/svn/pmon/sys/sys/types.h
cfsetispeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
cfsetispeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
cfsetispeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
cfsetispeed.o: /user/os/svn/pmon/sys/sys/endian.h
cfsetispeed.o: /user/os/svn/pmon/sys/sys/cdefs.h
cfsetispeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
cfsetispeed.o: /user/os/svn/pmon/sys/sys/ioctl.h
cfsetispeed.o: /user/os/svn/pmon/sys/sys/ttycom.h
cfsetispeed.o: /user/os/svn/pmon/sys/sys/ioccom.h
cfsetispeed.o: /user/os/svn/pmon/sys/sys/dkio.h
cfsetispeed.o: /user/os/svn/pmon/sys/sys/filio.h
cfsetispeed.o: /user/os/svn/pmon/sys/sys/sockio.h
cfsetispeed.o: /user/os/svn/pmon/sys/sys/termios.h
cfsetispeed.o: /user/os/svn/pmon/sys/sys/ttydefaults.h
cfsetospeed.o: /user/os/svn/pmon/sys/sys/types.h
cfsetospeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
cfsetospeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
cfsetospeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
cfsetospeed.o: /user/os/svn/pmon/sys/sys/endian.h
cfsetospeed.o: /user/os/svn/pmon/sys/sys/cdefs.h
cfsetospeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
cfsetospeed.o: /user/os/svn/pmon/sys/sys/ioctl.h
cfsetospeed.o: /user/os/svn/pmon/sys/sys/ttycom.h
cfsetospeed.o: /user/os/svn/pmon/sys/sys/ioccom.h
cfsetospeed.o: /user/os/svn/pmon/sys/sys/dkio.h
cfsetospeed.o: /user/os/svn/pmon/sys/sys/filio.h
cfsetospeed.o: /user/os/svn/pmon/sys/sys/sockio.h
cfsetospeed.o: /user/os/svn/pmon/sys/sys/termios.h
cfsetospeed.o: /user/os/svn/pmon/sys/sys/ttydefaults.h
cfsetspeed.o: /user/os/svn/pmon/sys/sys/types.h
cfsetspeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
cfsetspeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
cfsetspeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
cfsetspeed.o: /user/os/svn/pmon/sys/sys/endian.h
cfsetspeed.o: /user/os/svn/pmon/sys/sys/cdefs.h
cfsetspeed.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
cfsetspeed.o: /user/os/svn/pmon/sys/sys/ioctl.h
cfsetspeed.o: /user/os/svn/pmon/sys/sys/ttycom.h
cfsetspeed.o: /user/os/svn/pmon/sys/sys/ioccom.h
cfsetspeed.o: /user/os/svn/pmon/sys/sys/dkio.h
cfsetspeed.o: /user/os/svn/pmon/sys/sys/filio.h
cfsetspeed.o: /user/os/svn/pmon/sys/sys/sockio.h
cfsetspeed.o: /user/os/svn/pmon/sys/sys/termios.h
cfsetspeed.o: /user/os/svn/pmon/sys/sys/ttydefaults.h
ulmin.o: /user/os/svn/pmon/include/pmon.h /user/os/svn/pmon/sys/sys/types.h
ulmin.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
ulmin.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
ulmin.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
ulmin.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
ulmin.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
ulmin.o: /user/os/svn/pmon/sys/arch/mips/include/pmon_arch.h
ulmin.o: /user/os/svn/pmon/include/progress.h
ulmin.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/target/pmon_target.h
ulmin.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/target/bonito.h
lmin.o: /user/os/svn/pmon/include/pmon.h /user/os/svn/pmon/sys/sys/types.h
lmin.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
lmin.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
lmin.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
lmin.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
lmin.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
lmin.o: /user/os/svn/pmon/sys/arch/mips/include/pmon_arch.h
lmin.o: /user/os/svn/pmon/include/progress.h
lmin.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/target/pmon_target.h
lmin.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/target/bonito.h
ioctl.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
ioctl.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
ioctl.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
ioctl.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
ioctl.o: /user/os/svn/pmon/sys/sys/endian.h /user/os/svn/pmon/sys/sys/cdefs.h
ioctl.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
ioctl.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
ioctl.o: /user/os/svn/pmon/include/stdarg.h
ioctl.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/stdarg.h
ioctl.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/va-mips.h
ioctl.o: /user/os/svn/pmon/include/file.h /user/os/svn/pmon/sys/sys/queue.h
ioctl.o: /user/os/svn/pmon/include/fcntl.h /user/os/svn/pmon/sys/sys/fcntl.h
filefs.o: /user/os/svn/pmon/include/stdio.h /user/os/svn/pmon/sys/sys/types.h
filefs.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
filefs.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
filefs.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
filefs.o: /user/os/svn/pmon/sys/sys/endian.h
filefs.o: /user/os/svn/pmon/sys/sys/cdefs.h
filefs.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
filefs.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
filefs.o: /user/os/svn/pmon/include/string.h /user/os/svn/pmon/include/file.h
filefs.o: /user/os/svn/pmon/sys/sys/queue.h
parseurl.o: /user/os/svn/pmon/include/stdio.h
parseurl.o: /user/os/svn/pmon/sys/sys/types.h
parseurl.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/types.h
parseurl.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/ansi.h
parseurl.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/endian.h
parseurl.o: /user/os/svn/pmon/sys/sys/endian.h
parseurl.o: /user/os/svn/pmon/sys/sys/cdefs.h
parseurl.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/machine/cdefs.h
parseurl.o: /user/os/svn/pmon/Targets/Bonito2fdev/compile/Bonito/mod_usb_kbd.h
parseurl.o: /user/os/svn/pmon/include/stdlib.h
parseurl.o: /user/os/svn/pmon/include/string.h
parseurl.o: /user/os/svn/pmon/include/url.h
