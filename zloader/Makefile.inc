CC=mips-elf-gcc
GZROMSTARTADDR=0xffffffff81000000
ROMSTARTADDR=0xffffffff80010000
RAMSTARTADDR=0xffffffff80200000
export CC += ${MYCC}

ifdef obj
export CC += -g3
pwd=$(shell pwd)
gcc_E:
	cd ../Targets/${TARGET}/compile/${TARGETEL};${pwd}/mymake  ${obj} > /tmp/tmp.c
endif

ifndef tgt
help:
	@echo use make tgt=sim for sim in linux
	@echo use make tgt=rom for generate romfile gzrom.bin
	@echo use make tgt=ram for generate ramfile gzram
	@echo use make cfg     for config
	@echo use make recfg   for change config
	@echo use make tgt=rom MYCC="'"-g3 -DMYDBG='"printf(\"debug:%s,%d\\n\",__FILE__,__LINE__);"'"'" to support MYDBG macro. 
else
all: ${tgt}
sim: clean pmon.bin.c
	gcc -o zloader  -DSIM zloader.c
rom: clean ${START} zloader.o 
	gcc -DSTARTADDR=${GZROMSTARTADDR} -E -P ld.script.S > ld.script
	mips-elf-ld -T ld.script -e start -o gzrom ${START} zloader.o 
	mips-elf-objcopy -O binary gzrom gzrom.bin
#	sync
ram: clean startram.o zloader.o 
	gcc -DSTARTADDR=${GZROMSTARTADDR} -E -P ld.script.S > ld.script
	mips-elf-ld -T ld.script -e start -o gzram startram.o zloader.o 
	cp gzram /tftpboot
#	sync

zlib_rom: clean ${START} zlib_loader.o 
	gcc -DSTARTADDR=${GZROMSTARTADDR} -E -P ld.script.S > ld.script
	mips-elf-ld -T ld.script -e start -o zlib_gzrom ${START} zlib_loader.o  zlib_inflate/*.o
	mips-elf-objcopy -O binary zlib_gzrom zlib_gzrom.bin
	sync
zlib_ram: clean startram.o zlib_loader.o 
	gcc -DSTARTADDR=${GZROMSTARTADDR} -E -P ld.script.S > ld.script
	mips-elf-ld -T ld.script -e start -o zlib_gzram startram.o zlib_loader.o zlib_inflate/*.o
	cp zlib_gzram /tftpboot
	sync



${START}:
	rm -f ../Targets/${TARGET}/compile/${TARGETEL}/${START}
	gcc -DSTARTADDR=${ROMSTARTADDR} -E -P ld.script.S > ../Targets/${TARGET}/conf/ld.script
	make -C ../Targets/${TARGET}/compile/${TARGETEL}/
	cp ../Targets/${TARGET}/compile/${TARGETEL}/${START} .

startram.o:
	gcc -DSTARTADDR=${RAMSTARTADDR} -E -P ld.script.S > ../Targets/${TARGET}/conf/ld.script
	make -C ../Targets/${TARGET}/compile/${TARGETEL}/ DEBUG='-g -DMYDBG="printf(\"debug:%s,%d\\n\",__FILE__,__LINE__);"'
	$(CC) -D_LOCORE -G 0  -nostdinc   -DMIPS  -DCONS_BAUD="B115200"  -DCONFIG_CACHE_64K_4WAY  -D_KERNEL -D__OpenBSD__ -DPMON -D__PMON__ -EL -mno-abicalls -mips3 -mcpu=r4000 -c startram.S -D MEMSIZE=${MEMSIZE}
zloader.o: zloader.c inflate.c  malloc.c  memop.c  pmon.bin.c initmips.c
	$(CC) -EL -mips3 -mcpu=r4000 -c zloader.c ${ZLOADER_OPTIONS}

zlib_loader.o: zlib_loader.c  ./zlib_gzip zlib_pmon.bin.c initmips.c
	cd zlib_inflate;$(CC) -I ../../include -EL -mips3 -mcpu=r4000 -c *.c
	$(CC) -I ../include -EL -mips3 -mcpu=r4000 -c zlib_loader.c 

initmips.c:  ../Targets/${TARGET}/compile/${TARGETEL}/pmon
	${gencode} $< > initmips.c

zlib_pmon.bin.c:  ../Targets/${TARGET}/compile/${TARGETEL}/pmon.bin
	./zlib_gzip $<  zlib_pmon.bin.gz
	./bin2c zlib_pmon.bin.gz zlib_pmon.bin.c biosdata
	
pmon.bin.c:  ../Targets/${TARGET}/compile/${TARGETEL}/pmon.bin
	gzip $< -c > pmon.bin.gz
	./bin2c pmon.bin.gz pmon.bin.c biosdata

endif

ifeq ("${tgt}","rom")
gencode=./genrom
endif

ifeq ("${tgt}","zlib_rom")
gencode=./genrom
endif


ifndef gencode
gencode=./genram
endif

mrproper: clean
	perl -i -ne 'print;exit if(/^# DO NOT DELETE/);' ../lib/libc/Makefile 
	perl -i -ne 'print;exit if(/^# DO NOT DELETE/);' ../lib/libm/Makefile 
	perl -i -ne 'print;exit if(/^# DO NOT DELETE/);' ../lib/libz/Makefile 
	make -C ../Targets/${TARGET}/compile/${TARGETEL}/ clean
	rm -fr ../Targets/${TARGET}/compile/${TARGETEL}
	rm -fr ld.script
	
cleanall: clean
	make -C ../Targets/${TARGET}/compile/${TARGETEL}/ clean
clean:
	rm -rf *.o zlib_gzip zloader pmon.bin.c gzrom gzrom.bin gzram  initmips.c pmon.bin.gz zlib_deflate/*.o zlib_inflate/*.o zlib_gzrom zlib_gzrom.bin
cfg:
	# DO NOT DELETE
	perl -i -ne 'print;exit if(/^# DO NOT DELETE/);' ../lib/libc/Makefile 
	perl -i -ne 'print;exit if(/^# DO NOT DELETE/);' ../lib/libm/Makefile 
	perl -i -ne 'print;exit if(/^# DO NOT DELETE/);' ../lib/libz/Makefile 
	cd ../Targets/${TARGET}/conf/;pmoncfg ${TARGETEL}
	make -C ../Targets/${TARGET}/compile/${TARGETEL}/ depend clean
recfg:
	vi ../Targets/${TARGET}/conf/$(TARGETEL)
	make cfg

zlib_gzip: zlib_gzip.c
	cd zlib_deflate/;gcc -I ../../include -c *.c
	cd zlib_inflate/;gcc -I ../../include -c *.c
	gcc -o zlib_gzip zlib_gzip.c zlib_deflate/*.o zlib_inflate/*.o
