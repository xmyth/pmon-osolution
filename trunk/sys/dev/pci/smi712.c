/***************************************************************************
 * Name:
 *     smi712.c
 * License:
 *     2003-2007, Copyright by BLX IC Design Co., Ltd.
 * Description:
 *     smi712 driver
 *
 ***************************************************************************/

#include "smi712.h"

//#if     ENABLE_VGA_SMI712
////////////////////////////////
extern void  video_hw_init();

////////////////////////////////
static void smi_set_timing(struct par_info *hw)
{
        int i=0,j=0;
        u32 m_nScreenStride;
//    video_hw_init(); //xuhua    
    for (j=0;j < numVGAModes;j++) {
                if (VGAMode[j].mmSizeX == hw->width &&
                        VGAMode[j].mmSizeY == hw->height &&
                        VGAMode[j].bpp == hw->bits_per_pixel &&
                        VGAMode[j].hz == hw->hz)
                {
                        smi_mmiowb(0x0,0x3c6);

                        smi_seqw(0,0x1);

                        smi_mmiowb(VGAMode[j].Init_MISC,0x3c2);

                        for (i=0;i<SIZE_SR00_SR04;i++)  /* init SEQ register SR00 - SR04 */
                        {
                                smi_seqw(i,VGAMode[j].Init_SR00_SR04[i]);
                        }

                        for (i=0;i<SIZE_SR10_SR24;i++)  /* init SEQ register SR10 - SR24 */
                        {
                                smi_seqw(i+0x10,VGAMode[j].Init_SR10_SR24[i]);
                        }

                        for (i=0;i<SIZE_SR30_SR75;i++)  /* init SEQ register SR30 - SR75 */
                        {
                                if (((i+0x30) != 0x62) && ((i+0x30) != 0x6a) && ((i+0x30) != 0x6b))
                                        smi_seqw(i+0x30,VGAMode[j].Init_SR30_SR75[i]);
                        }
                        for (i=0;i<SIZE_SR80_SR93;i++)  /* init SEQ register SR80 - SR93 */
                        {
                                smi_seqw(i+0x80,VGAMode[j].Init_SR80_SR93[i]);
                        }
                        for (i=0;i<SIZE_SRA0_SRAF;i++)  /* init SEQ register SRA0 - SRAF */
                        {
                                smi_seqw(i+0xa0,VGAMode[j].Init_SRA0_SRAF[i]);
                        }

                        for (i=0;i<SIZE_GR00_GR08;i++)  /* init Graphic register GR00 - GR08 */
                        {
                                smi_grphw(i,VGAMode[j].Init_GR00_GR08[i]);
                        }

                        for (i=0;i<SIZE_AR00_AR14;i++)  /* init Attribute register AR00 - AR14 */
                        {

                                smi_attrw(i,VGAMode[j].Init_AR00_AR14[i]);
                        }

                        for (i=0;i<SIZE_CR00_CR18;i++)  /* init CRTC register CR00 - CR18 */
                        {
                                smi_crtcw(i,VGAMode[j].Init_CR00_CR18[i]);
                        }

                        for (i=0;i<SIZE_CR30_CR4D;i++)  /* init CRTC register CR30 - CR4D */
                        {
                                smi_crtcw(i+0x30,VGAMode[j].Init_CR30_CR4D[i]);
                        }

                        for (i=0;i<SIZE_CR90_CRA7;i++)  /* init CRTC register CR90 - CRA7 */
                        {
                                smi_crtcw(i+0x90,VGAMode[j].Init_CR90_CRA7[i]);
                        }
                }
        }
        smi_mmiowb(0x67,0x3c2);
        
        /* set VPR registers */
        writel(hw->m_pVPR+0x0C, 0x0);
        writel(hw->m_pVPR+0x40, 0x0);
        /* set data width */
        m_nScreenStride = (hw->width * hw->bits_per_pixel) / 64;
        
        /* case 16: */
        writel(hw->m_pVPR+0x0, 0x00020000);
                        
        writel(hw->m_pVPR+0x10, (u32)(((m_nScreenStride + 2) << 16) | m_nScreenStride));
}



/***************************************************************************
 * We need to wake up the LynxEM+, and make sure its in linear memory mode.
 ***************************************************************************/
static inline void 
smi_init_hw(void)
{
#if 0
	outb(0x18, 0x3c4);
    outb(0x11, 0x3c5);
#endif
	linux_outb(0x18, 0x3c4);
    linux_outb(0x11, 0x3c5);
}



int  smi712_init(char * fbaddress,char * ioaddress)
{
  
        u32 smem_size;

        
        smi_init_hw();


				
        hw.m_pLFB = SMILFB = fbaddress;
        hw.m_pMMIO = SMIRegs = SMILFB + 0x00700000; /* ioaddress */
        hw.m_pDPR = hw.m_pLFB + 0x00408000;
        hw.m_pVPR = hw.m_pLFB + 0x0040c000;

        /* now we fix the  mode */
#if 0
		hw.width = 800;
        hw.height = 600;
#endif
#if 1
		hw.width = 640;
        hw.height = 480;
#endif
		hw.bits_per_pixel = 16;
        hw.hz = 60;
        
        if (!SMIRegs)
        {
                printf(" unable to map memory mapped IO\n");
                return -1;
        }

		/*xuhua*/
		smi_seqw(0x21,0x00); 
		/*****/
        smi_seqw(0x62,0x7A);
        smi_seqw(0x6a,0x0c);
        smi_seqw(0x6b,0x02);
        smem_size = 0x00400000;

        /* LynxEM+ memory dection */
        *(u32 *)(SMILFB + 4) = 0xAA551133;
        if (*(u32 *)(SMILFB + 4) != 0xAA551133)
        {
                smem_size = 0x00200000;
                /* Program the MCLK to 130 MHz */
                smi_seqw(0x6a,0x12);
                smi_seqw(0x6b,0x02);
                smi_seqw(0x62,0x3e);
        }

        smi_set_timing(&hw);
                
        printf("Silicon Motion, Inc. LynxEM+ Init complete.\n");

        return 0;

}

//#endif

/* ---------------------------------------------------------------------- */
// $Log$
