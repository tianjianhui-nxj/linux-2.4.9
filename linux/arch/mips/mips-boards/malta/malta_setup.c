/*
 * Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.
 *
 * ########################################################################
 *
 *  This program is free software; you can distribute it and/or modify it
 *  under the terms of the GNU General Public License (Version 2) as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.
 *
 * ########################################################################
 *
 * Malta specific setup, including init of the feature struct.
 *
 */
#include <linux/config.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/mc146818rtc.h>
#include <linux/ioport.h>
#include <linux/pci.h>
#ifdef CONFIG_BLK_DEV_IDE
#include <linux/ide.h>
#endif

#include <asm/cpu.h>
#include <asm/bootinfo.h>
#include <asm/irq.h>
#include <asm/mips-boards/generic.h>
#include <asm/mips-boards/prom.h>
#include <asm/mips-boards/malta.h>
#include <asm/mips-boards/maltaint.h>
#ifdef CONFIG_BLK_DEV_FD
#include <asm/floppy.h>
#endif
#include <asm/dma.h>

#if defined(CONFIG_SERIAL_CONSOLE) || defined(CONFIG_PROM_CONSOLE)
extern void console_setup(char *, int *);
char serial_console[20];
#endif

#ifdef CONFIG_REMOTE_DEBUG
extern void set_debug_traps(void);
extern void rs_kgdb_hook(int);
extern void breakpoint(void);
static int remote_debug = 0;
#endif

#ifdef CONFIG_BLK_DEV_IDE
extern struct ide_ops std_ide_ops;
#endif
#ifdef CONFIG_BLK_DEV_FD
extern struct fd_ops std_fd_ops;
#endif
extern struct rtc_ops malta_rtc_ops;

extern void mips_reboot_setup(void);

struct resource standard_io_resources[] = {
	{ "dma1", 0x00, 0x1f, IORESOURCE_BUSY },
	{ "pic1", 0x20, 0x3f, IORESOURCE_BUSY },
	{ "timer", 0x40, 0x5f, IORESOURCE_BUSY },
	{ "dma page reg", 0x80, 0x8f, IORESOURCE_BUSY },
	{ "pic2", 0xa0, 0xbf, IORESOURCE_BUSY },
	{ "dma2", 0xc0, 0xdf, IORESOURCE_BUSY },
};

#define STANDARD_IO_RESOURCES (sizeof(standard_io_resources)/sizeof(struct resource))

static void __init malta_irq_setup(void)
{
  	maltaint_init();

#ifdef CONFIG_REMOTE_DEBUG
	if (remote_debug) {
		set_debug_traps();
		breakpoint(); 
	}
#endif
}


void __init malta_setup(void)
{
#ifdef CONFIG_REMOTE_DEBUG
	int rs_putDebugChar(char);
	char rs_getDebugChar(void);
	extern int (*putDebugChar)(char);
	extern char (*getDebugChar)(void);
#endif
	char *argptr;
	int i;

	irq_setup = malta_irq_setup;

	/* Request I/O space for devices used on the Malta board. */
	for (i = 0; i < STANDARD_IO_RESOURCES; i++)
		request_resource(&ioport_resource, standard_io_resources+i);

	/* 
	 * Enable DMA channel 4 (cascade channel) in the PIIX4 south bridge.
	 */
	enable_dma(4);

#ifdef CONFIG_SERIAL_CONSOLE
	argptr = prom_getcmdline();
	if ((argptr = strstr(argptr, "console=")) == NULL) {
		argptr = prom_getcmdline();
		strcat(argptr, " console=ttyS0,38400");
	}
#endif

#ifdef CONFIG_REMOTE_DEBUG
	argptr = prom_getcmdline();
	if ((argptr = strstr(argptr, "kgdb=ttyS")) != NULL) {
		int line;
		argptr += strlen("kgdb=ttyS");
		if (*argptr != '0' && *argptr != '1')
			printk("KGDB: Uknown serial line /dev/ttyS%c, "
			       "falling back to /dev/ttyS1\n", *argptr);
		line = *argptr == '0' ? 0 : 1;
		printk("KGDB: Using serial line /dev/ttyS%d for session\n",
		       line ? 1 : 0);

		rs_kgdb_hook(line);
		putDebugChar = rs_putDebugChar;
		getDebugChar = rs_getDebugChar;

		prom_printf("KGDB: Using serial line /dev/ttyS%d for session, "
			    "please connect your debugger\n", line ? 1 : 0);

		remote_debug = 1;
		/* Breakpoints and stuff are in malta_irq_setup() */
	}
#endif

	argptr = prom_getcmdline();
	if ((argptr = strstr(argptr, "nofpu")) != NULL)
		mips_cpu.options &= ~MIPS_CPU_FPU;
		
	rtc_ops = &malta_rtc_ops;
#ifdef CONFIG_BLK_DEV_IDE
        ide_ops = &std_ide_ops;
#endif
#ifdef CONFIG_BLK_DEV_FD
        fd_ops = &std_fd_ops;
#endif
	mips_reboot_setup();
}
