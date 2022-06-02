#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/cdev.h>

static char *kbuf;
static dev_t first;
static unsigned int count = 1;
static int my_major = 700, my_minor = 0;
static struct cdev *my_cdev;

#define MYDEV_NAME "test chardev module"
#define KBUF_SIZE (size_t) ((10) * PAGE_SIZE)


static int mychardev_open(struct inode* inode, struct file *file)
{
	printk(KERN_INFO "Opening device %s \n\n", MYDEV_NAME );
	return 0;
}

static int mychardev_release(struct inode* inode, struct file *file)
{
	printk(KERN_INFO "Release device %s \n\n", MYDEV_NAME );
	return 0;
}

static ssize_t mychardev_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
	printk(KERN_INFO "Read device %s \n\n", MYDEV_NAME );
	
	int nbytes = lbuf - copy_to_user(buf, kbuf + *ppos, lbuf);
	*ppos += nbytes;
	
	printk(KERN_INFO "Read device %s nbytes = %d, ppos =%d \n\n", MYDEV_NAME, nbytes, (int)*ppos );
	
	return nbytes;
}

static ssize_t mychardev_write(struct file *file, const char __user *buf, size_t lbuf, loff_t *ppos)
{
	printk(KERN_INFO "Write device %s \n\n", MYDEV_NAME );
	return 0;
}

static const struct file_operations mycdev_fops = {
	
	.owner = THIS_MODULE,
	.read = mychardev_read,
	.write = mychardev_write,
	.open = mychardev_open,
	.release = mychardev_release,
	
};

static int __init init_chardev(void)
{
	printk( KERN_INFO "Loading\n" );
	kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL);//check exseption
	
	//init first device
	first = MKDEV (my_major, my_minor);
	//register device
	register_chrdev_region(first, count, MYDEV_NAME); //check exseption
	
	my_cdev = cdev_alloc();
	
	cdev_init(my_cdev, &mycdev_fops);
	cdev_add(my_cdev, first, count);
	
	return 0;
}

static void __exit cleanup_chardev(void)
{
	printk( KERN_INFO "Leaving\n" );
}




module_init(init_chardev);
module_exit(cleanup_chardev);

MODULE_LICENSE("GPL");
