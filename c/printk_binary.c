void printk_binary(int val) {
  int i;

  for (i = 0; i < 32; i++) {
    if (val & 0x80000000) {
      printk("1");
    } else {
      printk("0");
    }
    if ((i + 1) % 8 == 0) {
      printk(" ");
    }
    val <<= 1;
  }
  printk("\n");
}

