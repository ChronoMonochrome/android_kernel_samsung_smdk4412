obj-$(CONFIG_MFD_MAX77693)	+= max77693-muic.o
obj-$(CONFIG_SEC_MODEM)		+= modem_if/

# Secure OS Mobicore Interface
CFLAGS_tzic.o :=$(call as-instr,.arch_extension sec,-DREQUIRES_SEC=1)
obj-$(CONFIG_MOBICORE_SUPPORT)  += tzic.o
