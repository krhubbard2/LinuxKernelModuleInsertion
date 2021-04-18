// Headers needed for LKM insertion
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

// Headers needed for Device creation
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "totallyARealDevice"

static int dev_open(struct inode*, struct file*);
static int dev_release(struct inode*, struct file*);
static ssize_t dev_read(struct file*, char*, size_t, loff_t*);
static ssize_t dev_write(struct file*, const char*, size_t, loff_t*);

static struct file_operations fops = {
   .open = dev_open,
   .read = dev_read,
   .write = dev_write,
   .release = dev_release,
};

static int major; // Major number will be given by kernel

static int __init lkm_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops); // Loads device on insert

    if (major < 0) {
        printk(KERN_ALERT "LKM Module has failed to load");
        return major;
    }

    printk(KERN_INFO "Hello, world! LKM module has been loaded: %d\n", major);
    return 0; // Status code 
}

static void __exit lkm_exit(void) {
    unregister_chrdev(major, DEVICE_NAME); // Unregisters device on unload
    printk(KERN_INFO "Goodbye, world! LKM Module has been unloaded\n");
}


static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    int errors = 0;
    char *message = "totallyARealDevice is taking over the world.\n";
    int message_length = strlen(message);

    // Writes 'message' to the buffer of 'message_length' bytes.
    errors = copy_to_user(buffer, message, message_length);

    return errors == 0 ? message_length : -EFAULT;
}

static int dev_open(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "totallyARealDevice has been opened");
    return 0; // Return no error code
}

static int dev_release(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "totallyARealDevice has been closed");
    return 0; // Return no error code
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset) {
    printk(KERN_INFO "totallyARealDevice is read only.");
    return -EFAULT; // Return an error code
}

module_init(lkm_init);
module_exit(lkm_exit);
