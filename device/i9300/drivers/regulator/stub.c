#include <linux/err.h>
#include <linux/module.h>
#include <device/linux/regulator/driver.h>
#include <device/linux/regulator/machine.h>

int regulator_disable_deferred(struct regulator *regulator, int ms)
{
	return -EINVAL;
}
