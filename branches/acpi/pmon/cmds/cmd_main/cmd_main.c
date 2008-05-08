	/*
		PMON command main
		Designed by LiuXiangYu(¡ıœË”Ó) USTC 04011
	*/
	#include <stdio.h>
	#include <termio.h>
	#include <endian.h>
	#include <string.h>
	#include <signal.h>
	#include <setjmp.h>
	#include <ctype.h>
	#include <unistd.h>
	#include <stdlib.h>
	#ifdef _KERNEL
	#undef _KERNEL
	#include <sys/ioctl.h>
	#define _KERNEL
	#else
	#include <sys/ioctl.h>
	#endif
	#include <pmon.h>
	#include <exec.h>
	#include <file.h>
	#include "window.h"

	#include "mod_debugger.h"
	#include "mod_symbols.h"

	#include "sd.h"
	#include "wd.h"

	#include <time.h>

	#define TM_YEAR_BASE 1900
	#include "cmd_hist.h"
	#include "cmd_more.h"
	extern unsigned int             memorysize;
	extern unsigned int             memorysize_high;
        
        extern char PciList[32][256];
        extern int PciList_num;
        extern char DevList[5][256];
        extern int DevList_num;

	enum Page {
	     Page_MAIN=0,
	     Page_Advanced,
	     Page_Boot,
	     Page_Exit,
	     Page_Time_Date=100,
             Page_Booting=101,
             Page_Warning=102,
             Page_Failed=103
	};

	void run(char *cmd)
	{
		char t[100];
		strcpy(t,cmd);
		do_cmd(t);
	}
	struct _daytime
	{
		char *name;
		short x,y;
		char buf[8];
		short buflen,base;
	}daytime[6]=	
	{
		{"Sec",29,16,"",4,0},
		{"Min",16,16,"",4,0},
		{"Hour",1,16,"",4,0},
		{"Day",29,15,"",4,0},
		{"Month",16,15,"",4,1},
		{"Year",1,15,"",6,TM_YEAR_BASE}
	};

	int	cmd_main __P((int, char *[]));
	int cmd_main
	(ac, av)
		int ac;
		char *av[];
	{
		char *message;//message passing through windows
		char* hint="";
		int oldwindow;//save the previous number of oldwindow
		char tinput[256];//input buffer1
		char line[100];
		char w0[6][50];//buffer of window"MAIN"
		char w1[6][50];//buffer of window"Boot"
		char w2[6][50];//buffer of window"Boot"
		char sibuf[4][20];
		//daytime modify
		int bp;
		int n = 0;
		int i = 0;//for cycle
		unsigned int a;
		time_t t;//current date and time
		struct tm tm;
		int freq;//cpu freq
		char *maintabs[]={"MAIN","Advanced","Boot","Exit"};
		char *f1[]={"wd0","wd1","cd0","fd0",0};
		char *f1b[]={"tty","ttyS0","ttyS1",0};
		char *f2[]={"rtl0","em0","em1","fxp0",0};
                
                _pciscan_forwindow();  
                _devls_forwindow();   
           
		w_init();

		w_setpage(Page_MAIN);

		strcpy(tinput,"");
		strcpy(w1[0],"boot/vmlinux");
		strcpy(w1[1],"/dev/hda1");
		strcpy(w1[2],"192.168.110.100");
		strcpy(w2[0],"192.168.110.176");	
		strcpy(w2[1],"192.168.110.176");

		strcpy(sibuf[0],f1[0]);
		strcpy(sibuf[1],f1b[0]);
		strcpy(sibuf[2],f2[0]);
		strcpy(sibuf[3],f2[0]);

		bp=0;	
		while(1)
		{
			if(w_getpage()>=Page_MAIN && w_getpage()<=Page_Exit)
			{
				if(w_keydown('[C')) { //HOOK  keyboard right
                                        if(w_getpage()==Page_Exit)
                                              w_setpage(Page_MAIN);
                                        else
					      w_setpage(w_getpage()+1);
                                }
				if(w_keydown('[D')) { //HOOK keyboard left
                                        if(w_getpage()==Page_MAIN)
                                              w_setpage(Page_Exit);
                                        else
					      w_setpage(w_getpage()-1);
                                }
			}
			if(w_keydown('`') || w_keydown('~'))//HOOK keyboard ~/`
				w_setpage(101);

			for(i=Page_MAIN;i<=Page_Exit;i++)
			{
				if(w_getpage()==i)
					w_setcolor(0xf0,0,0);
				else 
					w_setcolor(0,0,0);
				w_window(i*13+1,1,10,1,maintabs[i]);
			}
			w_defaultcolor();

		
			if((w_getpage() >=Page_MAIN && w_getpage()<=Page_Time_Date) || (w_getpage() == 101)) {
				w_window(49,3,30,19,"HINT");
				w_bigtext(49,4,30,15,hint);
			}
			
			/* Call the tgt_gettime() funciton every 50 cycles to ensure that the bios time could update in time */
			if(a>800)
			{
				a=0;
				 t = tgt_gettime();
				 tm = *localtime(&t);
			}
			a++;

			switch(w_getpage())
			{
			case Page_MAIN://Main window.Also display basic information
				oldwindow = Page_MAIN;
				w_window(1,3,47,19,"Basic Information");
				hint = "Display CPU, Memory and Timing information of Computer.";
				
				/* Display CPU information */
				sprintf(line,"Processor Type: %s",md_cpuname());
				w_text(1,5,WA_LEFT,line);
				
				sprintf(line,"Processor Speed: %d MHz",tgt_pipefreq()/1000000);
				w_text(1,6,WA_LEFT,line);

				/* Display Memory information */
				sprintf (line,"Memory size: %3d MB", (memorysize + memorysize_high)>>20);
				w_bigtext(1,8,40,2,line);
				sprintf(line,"Primary Instruction cache size: %dkb",CpuPrimaryInstCacheSize / 1024);
				w_bigtext(1,9,40,2,line);
				sprintf(line,"Primary Data cache size: %dkb ",CpuPrimaryDataCacheSize / 1024);
				w_bigtext(1,10,40,2,line);
				if(CpuSecondaryCacheSize != 0) {
					sprintf(line,"Secondary cache size: %dkb", CpuSecondaryCacheSize / 1024);
				w_bigtext(1,11,40,2,line);
                                }
				if(CpuTertiaryCacheSize != 0) {
					sprintf(line,"Tertiary cache size: %dkb", CpuTertiaryCacheSize / 1024);
				w_bigtext(1,12,40,2,line);
                                }

				if(w_button(25,13,20,"[Modify Time & Date]"))
					w_setpage(Page_Time_Date);
				if(w_focused()) {
					hint = "Modify Time and Date.";
				}
				/* Display the current date and time recored in BIOS */
				w_text(1,13,WA_LEFT,"System Time and Date:");
				for(i=0;i<6;i++)
				{
					sprintf(line,"%s:%d",daytime[i].name,((int *)(&tm))[i]+daytime[i].base);
					w_text(daytime[i].x,daytime[i].y,WA_LEFT,line);
				}
				break;
			case Page_Advanced://Device information on board
				oldwindow = Page_Advanced;
				hint = "Display device information";
                                w_window(1,3,47,19,"Advanced Information");
                               
                                w_text(2,5,WA_LEFT,"PCI Information");
                                if(w_focused())
                                        hint = "Display PCI Device";
                                for(i=0;i<PciList_num;i++)
                                        w_text(8,(5+i+1),WA_LEFT,PciList[i]);

                                w_text(2,18,WA_LEFT,"Drive Information");
                                if(w_focused())
                                        hint = "Display Drive Device";
                                for(i=0;i<DevList_num;i++)
                                        w_text(8,(18+i+1),WA_LEFT,DevList[i]);

                                break;
                        case Page_Boot://select boot device
                                oldwindow = Page_Boot;
                                hint = "Select Boot Device Priority";

				w_window(1,3,47,19,"Select boot option");
				w_text(2,4,WA_LEFT,"Boot from local");
				w_selectinput(18,5,20,"Set disk:       ",f1,sibuf[0],20);
				if(w_focused()) {
					hint = "Set the disk you want to boot.Use <Enter> to switch, other keys to modify.";
				}
				w_input(18,6,20,"Set kernel path:",w1[0],50);
				if(w_focused()) {
					hint = "Set kernel path. Just input the path in the textbox";
				}
				w_selectinput(18,7,20,"Set console:    ",f1b,sibuf[1],20);
				if(w_focused()) {
					hint = "Set console.Use <Enter> to switch, other keys to modify.";
				}
				w_input(18,8,20,"Set root:       ",w1[1],50);
				if(w_focused()) {
					hint = "Set root path. Just input the path in the textbox.";
				}
				if(w_button(23,9,10,"[BOOT NOW]")) {
					hint = "";	
					sprintf(line,"set disk %s",sibuf[0]);
					run(line);
					sprintf(line,"set kernelpath %s",w1[0]);
					run(line);
					sprintf(line,"set console %s",sibuf[1]);
					run(line);
					sprintf(line,"set root %s",w1[1]);
					run(line);
					sprintf(line,"set serverip %s",w1[2]);
					run(line);
					run("load /dev/fs/ext2@$disk/$kernelpath;g console=$console root=$root;");
					message = "Boot failed"; 
					w_setpage(Page_Failed);
				}

                                w_text(2,12,WA_LEFT,"Boot from Network");
                                w_selectinput(18,13,20,"Set Interface:  ",f2,sibuf[2],20);
				if(w_focused()) {
					hint = "Option:rtl0,em0,em1,fxp0.Press Enter to Switch, other keys to modify";
				}
				w_input(18,14,20,"Set Local IP:   ",w2[0],50);
				if(w_focused()) {
					hint = "Please input new IP in the textbox.";
				}
			 /*       if(w_button(18,15,10,"[Set IP]")){
						ifconfig(sibuf[2],w2[0]);//configure
							sprintf(line,"The device [%s] now has a new IP",sibuf[2]);
							message = line;
							w_setpage(100);
                                }*/
                                w_input(18,15,20,"Set Server IP:  ",w1[2],50);
				if(w_focused()) {
					hint = "Set server ip. Just input the path in the textbox.";
				}
	                        w_selectinput(18,16,20,"Set console:    ",f1b,sibuf[1],20);
				if(w_focused()) {
					hint = "Set console.Use <Enter> to switch, other keys to modify.";
				}
				w_input(18,17,20,"Set root:       ",w1[1],50);
				if(w_focused()) {
					hint = "Set root path. Just input the path in the textbox.";
				}

                                if(w_button(23,18,10,"[BOOT NOW]")) {
				        hint = "";	
				       	sprintf(line,"set kernelpath %s",w1[0]);
					run(line);
                                	sprintf(line,"set console %s",sibuf[1]);
					run(line);
					sprintf(line,"set root %s",w1[1]);
					run(line);
					sprintf(line,"set serverip %s",w1[2]);
					run(line);
                                        ifconfig(sibuf[2],w2[0]);//configure ifconfig
					run("load tftp://$serverip/$kernelpath;g console=$console root=$root;");
					message = "Boot failed"; 
					w_setpage(Page_Failed);
				}
			break;
			case Page_Exit://Save configuration and reboot the system
				oldwindow = Page_Exit;
				hint = "Exit system setup or restart system";
				w_window(1,3,47,19,"Exit system setup or Restart the system");
				if(w_button(3,5,20,"[ Restart the system ]")) 
					w_setpage(Page_Warning);
				if(w_focused())
					hint="<Enter> to restart system.";
				if(w_button(3,7,20,"  [ Return to PMON ]  "))
					{
                                                w_enterconsole();
						return(0);
					}
				if(w_focused())
					hint="<Enter> to exit system setup.";

			break;

			case Page_Warning:
				w_window(20,8,40,8,"WARRNING");
				w_text(40,10,WA_CENTRE,"Are you sure to restart the system?");
				if(w_button(37,12,10,"[ YES ]"))w_setpage(Page_Booting);
				if(w_button(37,14,10,"[ NO ]"))w_setpage(oldwindow);
			break;

			case Page_Time_Date://Modify Time and Date
				oldwindow=Page_MAIN;
				
				w_window(1,3,47,19,"Modify Time and Date");
				if(w_button(14,19,22,"[ Return ]"))w_setpage(oldwindow);
				if(w_focused())
					hint = "<Enter> to return. Up Arrow key to modify";
				for(i=0;i<6;i++)
				{
					if(w_input(daytime[i].x+8,daytime[i].y,6,daytime[i].name,daytime[i].buf,daytime[i].buflen))
					{
						sprintf(line,"date %04s%02s%02s%02s%02s.%02s",
	daytime[5].buf,daytime[4].buf,daytime[3].buf,daytime[2].buf,daytime[1].buf,daytime[0].buf);
						run(line);
						w_setfocusid(w_getfocusid()-1);
						
					}
					if(w_focused())
					{
						sprintf(line,"input %s, <Enter> to confirm.",daytime[i].name);
						hint=line;
					}
					else
						sprintf(daytime[i].buf,"%d",((int *)(&tm))[i]+daytime[i].base);
				}
			break;
			case Page_Failed:
				w_window(20,7,40,9,"Notice");
				w_text(39,9,WA_CENTRE,message);
				w_text(39,11,WA_CENTRE,"Press Enter to return");
				if(w_button(30,13,20,"[Return]"))w_setpage(oldwindow);
			break;
			case Page_Booting:
				printf("Rebooting.....");
				tgt_reboot();
				break;
			}
			w_present();
		}
	return(0);
}
static const Cmd Cmds[] = {
	{"MainCmds"},
	{"main","",0,"Simulates the MAIN BIOS SETUP",cmd_main, 0, 99, CMD_REPEAT},
	{0, 0}
};
static void init_cmd __P((void)) __attribute__ ((constructor));
static void
init_cmd()
{
	cmdlist_expand(Cmds, 1);
}
