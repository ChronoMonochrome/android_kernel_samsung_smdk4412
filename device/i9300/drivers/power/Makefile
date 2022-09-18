ccflags-$(CONFIG_POWER_SUPPLY_DEBUG) := -DDEBUG

power_supply-y				:= power_supply_core.o
power_supply-$(CONFIG_SYSFS)		+= power_supply_sysfs.o

obj-$(CONFIG_POWER_SUPPLY)	+= power_supply.o
obj-$(CONFIG_BATTERY_SAMSUNG)	+= samsung_fake_battery.o
