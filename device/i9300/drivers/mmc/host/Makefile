#
# Makefile for MMC/SD host controller drivers
#

obj-$(CONFIG_MMC_ARMMMCI)	+= mmci.o
obj-$(CONFIG_MMC_PXA)		+= pxamci.o
obj-$(CONFIG_MMC_IMX)		+= imxmmc.o
obj-$(CONFIG_MMC_MXC)		+= mxcmmc.o
obj-$(CONFIG_MMC_MXS)		+= mxs-mmc.o
obj-$(CONFIG_MMC_DW)		+= dw_mmc.o
obj-$(CONFIG_MMC_MSHCI)		+= mshci.o
obj-$(CONFIG_MMC_MSHCI)		+= mshci-s3c.o
obj-$(CONFIG_MMC_MSHCI_S3C_DMA_MAP)	+= mshci-s3c-dma.o
obj-$(CONFIG_MMC_SDHCI)		+= sdhci.o
obj-$(CONFIG_MMC_SDHCI_PCI)	+= sdhci-pci.o
obj-$(CONFIG_MMC_SDHCI_PXA)	+= sdhci-pxa.o
obj-$(CONFIG_MMC_SDHCI_S3C_LEGACY)	+= sdhci-s3c.o
obj-$(CONFIG_MMC_SDHCI_SPEAR)	+= sdhci-spear.o
obj-$(CONFIG_MMC_WBSD)		+= wbsd.o
obj-$(CONFIG_MMC_AU1X)		+= au1xmmc.o
obj-$(CONFIG_MMC_OMAP)		+= omap.o
obj-$(CONFIG_MMC_OMAP_HS)	+= omap_hsmmc.o
obj-$(CONFIG_MMC_AT91)		+= at91_mci.o
obj-$(CONFIG_MMC_ATMELMCI)	+= atmel-mci.o
obj-$(CONFIG_MMC_TIFM_SD)	+= tifm_sd.o
obj-$(CONFIG_MMC_MSM)		+= msm_sdcc.o
obj-$(CONFIG_MMC_MVSDIO)	+= mvsdio.o
obj-$(CONFIG_MMC_DAVINCI)       += davinci_mmc.o
obj-$(CONFIG_MMC_SPI)		+= mmc_spi.o
ifeq ($(CONFIG_OF),y)
obj-$(CONFIG_MMC_SPI)		+= of_mmc_spi.o
endif
obj-$(CONFIG_MMC_S3C)   	+= s3cmci.o
obj-$(CONFIG_MMC_SDRICOH_CS)	+= sdricoh_cs.o
obj-$(CONFIG_MMC_TMIO)		+= tmio_mmc.o
obj-$(CONFIG_MMC_TMIO_CORE)	+= tmio_mmc_core.o
tmio_mmc_core-y			:= tmio_mmc_pio.o
ifneq ($(CONFIG_MMC_SDHI),n)
tmio_mmc_core-y			+= tmio_mmc_dma.o
endif
obj-$(CONFIG_MMC_SDHI)		+= sh_mobile_sdhi.o
obj-$(CONFIG_MMC_CB710)		+= cb710-mmc.o
obj-$(CONFIG_MMC_VIA_SDMMC)	+= via-sdmmc.o
obj-$(CONFIG_SDH_BFIN)		+= bfin_sdh.o
obj-$(CONFIG_MMC_SH_MMCIF)	+= sh_mmcif.o
obj-$(CONFIG_MMC_JZ4740)	+= jz4740_mmc.o
obj-$(CONFIG_MMC_VUB300)	+= vub300.o
obj-$(CONFIG_MMC_USHC)		+= ushc.o

obj-$(CONFIG_MMC_SDHCI_PLTFM)			+= sdhci-platform.o
sdhci-platform-y				:= sdhci-pltfm.o
sdhci-platform-$(CONFIG_MMC_SDHCI_CNS3XXX)	+= sdhci-cns3xxx.o
sdhci-platform-$(CONFIG_MMC_SDHCI_ESDHC_IMX)	+= sdhci-esdhc-imx.o
sdhci-platform-$(CONFIG_MMC_SDHCI_DOVE)		+= sdhci-dove.o
sdhci-platform-$(CONFIG_MMC_SDHCI_TEGRA)	+= sdhci-tegra.o

obj-$(CONFIG_MMC_SDHCI_OF)	+= sdhci-of.o
sdhci-of-y				:= sdhci-of-core.o
sdhci-of-$(CONFIG_MMC_SDHCI_OF_ESDHC)	+= sdhci-of-esdhc.o
sdhci-of-$(CONFIG_MMC_SDHCI_OF_HLWD)	+= sdhci-of-hlwd.o

ifeq ($(CONFIG_CB710_DEBUG),y)
	CFLAGS-cb710-mmc	+= -DDEBUG
endif
