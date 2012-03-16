#include <linux/kernel.h>
#include <linux/reboot.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/err.h>
#include <linux/sysrq.h>
#include <linux/syscalls.h>
#include <linux/kthread.h>

static atomic_t probe_count = ATOMIC_INIT(0);
static DECLARE_WAIT_QUEUE_HEAD(probe_waitqueue);

static int      mymodule_reboot_thread(void *arg) {
  char          *argv[2];
  char          *envp[4];
  int           ret;

  wait_event(probe_waitqueue, atomic_read(&probe_count) > 0);
  atomic_dec(&probe_count);
  argv[0] = "/sbin/reboot";
  argv[1] = NULL;
  envp[0] = "HOME=/";
  envp[1] = "PWD=/";
  envp[2] = "PATH=/sbin";
  envp[3] = NULL;
  ret = call_usermodehelper(argv[0], argv, envp, 0);
  if (!ret) {
    printk("Rebooting...\n");
  }
  return ret;
}

irqreturn_t             mymodule_reboot_irq_handler(int irq, void *dev_id) {
  atomic_inc(&probe_count);
  wake_up(&probe_waitqueue);
  return IRQ_HANDLED;
}

void __init             mymodule_init(void) {
  struct task_struct    *thread;

  thread = kthread_create(mymodule_reboot_thread, NULL, "thread-name");
  if (!IS_ERR(thread)) {
    wake_up_process(thread);
  }
  request_any_context_irq(irqId, mymodule_reboot_irq_handler, IRQF_TRIGGER_FALLING, "irq-name", NULL);
}

void __exit             mymodule_exit(void) {
  free_irq(irqId, NULL);
}
