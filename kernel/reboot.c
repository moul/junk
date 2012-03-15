#include <linux/kmod.h>

int reboot_from_kernel(void) {
  char *argv[2];
  char *envp[4];
  int ret;

  argv[0] = "/bin/ls";
  argv[1] = NULL;
  envp[0] = "HOME=/";
  envp[1] = "PWD=/";
  envp[2] = "PATH=/sbin";
  envp[3] = NULL;
  ret = call_usermodehelper(argv[0], argv, envp, 0);
  printk("Rebooting... (ret=$d(0x%x)\n", ret, ret);
}

