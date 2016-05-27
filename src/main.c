/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* XILINX CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "fmc_imageon_vita_passthrough.h"
fmc_imageon_vita_passthrough_t demo;

int main()
{
	unsigned int i;
    printf("Starting passthrough_linux application\n\r");
    int mem = open("/dev/mem", O_RDWR);

    demo.uBaseAddr_IIC_FmcImageon = (Xuint32)mmap(NULL, 0x400, PROT_READ | PROT_WRITE, MAP_SHARED, mem, XPAR_FMC_IMAGEON_IIC_0_BASEADDR);
    demo.uBaseAddr_VITA_SPI = (Xuint32)mmap(NULL, 0x400, PROT_READ | PROT_WRITE, MAP_SHARED, mem, XPAR_FMC_IMAGEON_VITA_COLOR_ONSEMI_VITA_SPI_0_S00_AXI_BASEADDR);
    demo.uBaseAddr_VITA_CAM = (Xuint32)mmap(NULL, 0x400, PROT_READ | PROT_WRITE, MAP_SHARED, mem, XPAR_FMC_IMAGEON_VITA_COLOR_ONSEMI_VITA_CAM_0_S00_AXI_BASEADDR);

    if(demo.uBaseAddr_IIC_FmcImageon == -1 || demo.uBaseAddr_VITA_SPI == -1 || demo.uBaseAddr_VITA_CAM == 1){
    	printf("Address mapping failed, are you root?\n");
    	return(0);
    }

    demo.bVerbose = TRUE;
    fmc_imageon_vita_passthrough_init( &demo );
    /*
    unsigned long vdma = (unsigned long)mmap(NULL, 0x400, PROT_READ | PROT_WRITE, MAP_SHARED, mem, XPAR_AXI_VDMA_0_BASEADDR);
    printf("vdma: %lx\n", vdma);

    //Xil_Out32(vdma + 0xa0, 0x7d0);
    for(i = 0; i < 20; i++){
      printf("0x%x:  0x%lx\n", 4*i, Xil_In32(demo.uBaseAddr_IIC_FmcImageon + 4*i));
    }*/

    return 0;
}
