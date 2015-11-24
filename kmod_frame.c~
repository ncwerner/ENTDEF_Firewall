/* very basic kernel mod test 
 * outputs the print statements to
 * /var/log/message */

#include <linux/kernel.h>
#include <linux/module.h>

#ifndef __KERNEL__
#define __KERNEL__
#endif 

#ifndef MODULE
#define MODULE
#endif 

int init_module(void) {
    printk(KERN_INFO "Kernel mod init run\n");
    return 0;
}

void cleanup_module(void) {
    printk(KERN_INFO "Kernel mod removed\n");
}
