videodev-objs	:=	v4l2-dev.o v4l2-ioctl.o v4l2-device.o v4l2-fh.o \
			v4l2-event.o v4l2-ctrls.o v4l2-subdev.o

obj-$(CONFIG_VIDEO_DEV) += videodev.o

obj-$(CONFIG_VIDEOBUF_GEN) += videobuf-core.o

obj-$(CONFIG_VIDEOBUF2_CORE)		+= videobuf2-core.o
obj-$(CONFIG_VIDEOBUF2_DMA_CONTIG)	+= videobuf2-dma-contig.o

obj-$(CONFIG_V4L2_MEM2MEM_DEV) += v4l2-mem2mem.o

obj-$(CONFIG_VIDEO_S5C73M3)    += s5c73m3.o
obj-$(CONFIG_VIDEO_S5C73M3_SPI)        += s5c73m3_spi.o
obj-$(CONFIG_VIDEOBUF2_CMA_PHYS) += videobuf2-cma-phys.o
obj-$(CONFIG_VIDEOBUF2_ION) += videobuf2-ion.o
obj-$(CONFIG_VIDEO_EXYNOS)             += exynos/
obj-$(CONFIG_VIDEO_SAMSUNG)    += samsung/
obj-$(CONFIG_SAMSUNG_MHL)      += mhl/
