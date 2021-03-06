#
# Makefile for the linux kernel.
#
# Note! Dependencies are done automagically by 'make dep', which also
# removes any old dependencies. DON'T put your own dependencies here
# unless it's something special (ie not a .c file).

USE_STANDARD_AS_RULE := true

O_TARGET		:= sa1100.o

obj-y :=
obj-m :=
obj-n :=
obj-  :=

export-objs :=	assabet.o bitsy.o freebird.o huw_webpanel.o yopy.o \
		generic.o hwtimer.o irq.o usb_ctl.o usb_recv.o usb_send.o \
		dma-sa1100.o dma-sa1111.o pcipool.o

# Common support (must be linked before board specific support)
obj-y += generic.o irq.o dma-sa1100.o
obj-$(CONFIG_SA1111) += sa1111.o dma-sa1111.o sa1111-pcibuf.o pcipool.o

# This needs to be cleaned up.  We probably need to have SA1100
# and SA1110 config symbols.
ifeq ($(CONFIG_CPU_FREQ),y)
obj-$(CONFIG_SA1100_ASSABET) += cpu-sa1110.o
obj-$(CONFIG_SA1100_LART) += cpu-sa1100.o
endif

# Specific board support
obj-$(CONFIG_SA1100_ASSABET) += assabet.o
obj-$(CONFIG_ASSABET_NEPONSET) += neponset.o
obj-$(CONFIG_SA1100_BITSY) += bitsy.o
obj-$(CONFIG_SA1100_BRUTUS) += brutus.o
obj-$(CONFIG_SA1100_CERF) += cerf.o
obj-$(CONFIG_SA1100_EMPEG) += empeg.o
obj-$(CONFIG_SA1100_FLEXANET) += flexanet.o
obj-$(CONFIG_SA1100_FREEBIRD) += freebird.o
obj-$(CONFIG_SA1100_GRAPHICSCLIENT) += graphicsclient.o
obj-$(CONFIG_SA1100_HUW_WEBPANEL) += huw_webpanel.o
obj-$(CONFIG_SA1100_ITSY) += itsy.o
obj-$(CONFIG_SA1100_JORNADA720) += jornada720.o
obj-$(CONFIG_SA1100_LART) += lart.o
obj-$(CONFIG_SA1100_NANOENGINE) += nanoengine.o
obj-$(CONFIG_SA1100_OMNIMETER) += omnimeter.o
obj-$(CONFIG_SA1100_PANGOLIN) += pangolin.o
obj-$(CONFIG_SA1100_PFS168) += pfs168.o
obj-$(CONFIG_SA1100_PLEB) += pleb.o
obj-$(CONFIG_SA1100_SHERMAN) += sherman.o
obj-$(CONFIG_SA1100_SIMPAD) += simpad.o
obj-$(CONFIG_SA1100_VICTOR) += victor.o
obj-$(CONFIG_SA1100_XP860) += xp860.o
obj-$(CONFIG_SA1100_YOPY) += yopy.o

# LEDs support
leds-y := leds.o
leds-$(CONFIG_SA1100_ASSABET) += leds-assabet.o
leds-$(CONFIG_SA1100_BRUTUS) += leds-brutus.o
leds-$(CONFIG_SA1100_CERF) += leds-cerf.o
leds-$(CONFIG_SA1100_FLEXANET) += leds-flexanet.o
leds-$(CONFIG_SA1100_GRAPHICSCLIENT) += leds-graphicsclient.o
leds-$(CONFIG_SA1100_LART) += leds-lart.o
leds-$(CONFIG_SA1100_PFS168) += leds-pfs168.o
obj-$(CONFIG_LEDS) += $(leds-y)

include $(TOPDIR)/Rules.make
