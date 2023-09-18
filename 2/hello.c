#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/rcupdate.h>
#include <linux/kthread.h>

MODULE_LICENSE("GPL");

struct task_struct *thread;

typedef struct my_data
{
	int key;
	int val;

}my_data;

my_data *global_ptr = NULL;


static int write_thread_fn(void *arg)
{
	my_data *new_ptr = kmalloc(sizeof(my_data), GFP_KERNEL);
	new_ptr->key = 1;
	new_ptr->val = 1000;
	rcu_assign_pointer(global_ptr, new_ptr);
	pr_info("global pointer\t key:%d\t val:%d\n", global_ptr->key, global_ptr->val);
	return 0;
}

static int __init test_hello_init(void)
{
	thread = kthread_run(write_thread_fn, NULL, "write_thread");
	return 0;
}

static void __exit test_hello_exit(void)
{
}

module_init(test_hello_init);
module_exit(test_hello_exit);
