/* test.h - MemTest-86  Version 3.2
 *
 * Released under version 2 of the Gnu Public License.
 * By Chris Brady
 */
#ifndef __NEWMTTEST__
#define __NEWMTTEST__

#define E88     0x00
#define E801    0x04
#define E820NR  0x08           /* # entries in E820MAP */
#define E820MAP 0x0c           /* our map */
#define E820MAX 32             /* number of entries in E820MAP */
#define E820ENTRY_SIZE 20
#define MEMINFO_SIZE 0x28c

#ifndef __ASSEMBLY__

#define E820_RAM        1
#define E820_RESERVED   2
#define E820_ACPI       3 /* usable as RAM once ACPI tables have been read */
#define E820_NVS        4

struct e820entry {
        unsigned long long addr;        /* start of memory segment */
        unsigned long long size;        /* size of memory segment */
        unsigned long type;             /* type of memory segment */
};

struct mem_info_t {
	unsigned long e88_mem_k;	/* 0x00 */
	unsigned long e801_mem_k;	/* 0x04 */
	unsigned long e820_nr;		/* 0x08 */
	struct e820entry e820[E820MAX];	/* 0x0c */
					/* 0x28c */
};

#define SPINSZ		0x800000
#define MOD_SZ		20
#define BAILOUT		if (bail) goto skip_test;
#define BAILR		if (bail) return;

#define RES_START	0xa0000
#define RES_END		0x100000
#ifdef BONITOEL
	#define SCREEN_ADR 0xb00b8000
#endif
	
#ifdef CONFIG_PCI0_GAINT_MEM
#define SCREEN_ADR 0xbeeb8000
#endif

#ifdef CONFIG_PCI0_HUGE_MEM
#define SCREEN_ADR 0xb48b8000
#endif

#ifdef CONFIG_PCI0_LARGE_MEM
#define SCREEN_ADR 0xb50b8000
#endif

#if !(defined(BONITOEL)|defined(CONFIG_PCI0_GAINT_MEM)|defined(CONFIG_PCI0_HUGE_MEM)|defined(CONFIG_PCI0_LARGE_MEM)) 
#define SCREEN_ADR 0xb00b8000	
#endif

#define SCREEN_END_ADR  (SCREEN_ADR + 80*25*2)

#define TITLE_WIDTH	28
#define LINE_TIME	10
#define COL_TIME	0
#define LINE_TST	2
#define LINE_RANGE	3
#define LINE_CPU	1
#define COL_MID		30
#define LINE_PAT        4
#define COL_PAT		41
#define LINE_INFO	10
#define COL_CACHE_TOP   13
#define COL_RESERVED    22
#define COL_MMAP	29
#define COL_CACHE	40
#define COL_ECC		46
#define COL_TST		52
#define COL_PASS	56
#define COL_ERR		63
#define COL_ECC_ERR	72
#define LINE_HEADER	12
#define LINE_SCROLL	14
#define BAR_SIZE	(78-COL_MID-9)

#define POP_W	30
#define POP_H	15
#define POP_X	16
#define POP_Y	8
#define NULL	0

/* memspeed operations */
#define MS_BCOPY	1
#define MS_COPY		2
#define MS_WRITE	3
#define MS_READ		4

#define SZ_MODE_BIOS		1
#define SZ_MODE_BIOS_RES	2
#define SZ_MODE_PROBE		3

#define getCx86(reg) ({ outb((reg), 0x22); inb(0x23); })
//int memcmp(const void *s1, const void *s2, ulong count);
//void *memmove(void *dest, const void *src, ulong n);
int query_linuxbios(void);
int query_pcbios(void);
int insertaddress(ulong);
void printpatn(void);
void printpatn(void);
void itoa(char s[], int n); 
void reverse(char *p);
void serial_echo_init(void);
void serial_echo_print(const char *s);
void ttyprint(int y, int x, const char *s);
void ttyprintc(int y, int x, char c);
void cprint(int y,int x, const char *s);
void hprint(int y,int x,ulong val);
void hprint2(int y,int x, ulong val, int len);
void xprint(int y,int x,ulong val);
void aprint(int y,int x,ulong page);
void dprint(int y,int x,ulong val,int len, int right);
void movinv1(int iter, ulong p1, ulong p2);
void movinvr();
void movinv32(int iter, ulong p1, ulong lb, ulong mb, int sval, int off);
void modtst(int off, int iter, ulong p1, ulong p2);
void error(ulong* adr, ulong good, ulong bad);
void ad_err1(ulong *adr1, ulong *adr2, ulong good, ulong bad);
void ad_err2(ulong *adr, ulong bad);
void do_tick(void);
//void rand_seed(int seed1, int seed2);
//ulong rand();
//void init(void);
struct eregs;
void inter(struct eregs *trap_regs);
void set_cache(int val);
int check_input(void);
void footer(void);
void scroll(void);
void popup(void);
void popdown(void);
void popclear(void);
void get_config(void);
void get_menu(void);
void get_printmode(void);
void addr_tst1(void);
void addr_tst2(void);
void bit_fade(void);
void Sleep(int sec);
void block_move(int iter);
void find_ticks(void);
void print_err(ulong *adr, ulong good, ulong bad, ulong xor);
void print_ecc_err(ulong page, ulong offset, int corrected, 
	unsigned short syndrome, int channel);
void mem_size(void);
void adj_mem(void);
ulong getval(int x, int y, int result_shift);
int get_key(void);
int ascii_to_keycode(int in);
void wait_keyup(void);
void print_hdr(void);
void restart(void);
void parity_err(ulong edi, ulong esi);
void start_config(void);
void clear_screen(void);
void paging_off(void);
int map_page(unsigned long page);
void *mapping(unsigned long page_address);
void *emapping(unsigned long page_address);
unsigned long page_of(void *ptr);

#define PRINTMODE_ADDRESSES 0
#define PRINTMODE_PATTERNS  1
#define PRINTMODE_NONE      2

#define BADRAM_MAXPATNS 10

struct pair {
       ulong adr;
       ulong mask;
};


static inline void cache_off(void)
{
		cacheflush();
		__asm__ volatile(
		 ".set mips3;\r\n"
		 "mfc0   $4,$16;\r\n"
        "and    $4,$4,0xfffffff8;\r\n"
        "or     $4,$4,0x2;\r\n"
        "mtc0   $4,$16;\r\n"
		".set mips0;\r\n"
		::
		: "$4"
		);
}
static inline void cache_on(void)
{
		 cacheflush();
	    __asm__ volatile(
		".set mips3;\r\n"
        "mfc0   $4,$16;\r\n"
        "and    $4,$4,0xfffffff8;\r\n"
        "or     $4,$4,0x3;\r\n"
        "mtc0   $4,$16;\r\n"
		".set mips0;"
		::
		:"$4"
		);
}


struct mmap {
	ulong pbase_addr;
	ulong *start;
	ulong *end;
};

struct pmap {
	ulong start;
	ulong end;
};

struct tseq {
	short cache;
	short pat;
	short iter;
	short ticks;
	short errors;
	char *msg;
};

struct cpu_ident {
	char type;
	char model;
	char step;
	char fill;
	long cpuid;
	long capability;
	char vend_id[12];
	unsigned char cache_info[16];
	long pwrcap;
};
#define X86_FEATURE_PAE		(0*32+ 6) /* Physical Address Extensions */

#define MAX_MEM_SEGMENTS E820MAX

/* Define common variables accross relocations of memtest86 */
struct vars {
	int test;
	int pass;
	unsigned long *eadr;
	unsigned long exor;
	int msg_line;
	int ecount;
	int ecc_ecount;
	int msegs;
	int testsel;
	int scroll_start;
	int rdtsc;
	int pae;
	int pass_ticks;
	int total_ticks;
	int pptr;
	int tptr;
	struct pmap pmap[MAX_MEM_SEGMENTS];
	struct mmap map[MAX_MEM_SEGMENTS];
	ulong plim_lower;
	ulong plim_upper;
	ulong clks_msec;
	ulong starth;
	ulong startl;
	ulong snaph;
	ulong snapl;
	int printmode;
	int numpatn;
	struct pair patn [BADRAM_MAXPATNS];
	ulong test_pages;
	ulong selected_pages;
	ulong reserved_pages;
};

#define FIRMWARE_UNKNOWN   0
#define FIRMWARE_PCBIOS    1
#define FIRMWARE_LINUXBIOS 2

extern struct vars * const v;
extern unsigned char _start[], _end[], startup_32[];
extern unsigned char _size, _pages;

extern struct mem_info_t mem_info;

#endif /* __ASSEMBLY__ */
#endif
