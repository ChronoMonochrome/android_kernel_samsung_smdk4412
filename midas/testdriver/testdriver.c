#include <linux/module.h>
#include <linux/kernel.h>

static int testdriver_val = 0;

static int __init testdriver_init(void)
{
	pr_err("%s: hello from testdriver\n", __func__);
	return 0;
}

static void __exit testdriver_exit(void)
{
}

module_param_named(testdriver_param, testdriver_val, uint, 0644);

module_init(testdriver_init);
module_exit(testdriver_exit);
