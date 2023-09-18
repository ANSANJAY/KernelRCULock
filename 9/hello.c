#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/rcupdate.h>
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

struct task_struct *thread1, *thread2, *thread3;

typedef struct my_data
{
	int key;
	int val;

}my_data;

my_data *global_ptr = NULL;

static int write_thread_fn(void *arg)
{
	while(!kthread_should_stop())
	{
		my_data *tmp_ptr = global_ptr;
		my_data *new_ptr = kmalloc(sizeof(my_data), GFP_KERNEL);
		memcpy(new_ptr, global_ptr, sizeof(my_data));
		new_ptr->key++;
		new_ptr->val++;
		rcu_assign_pointer(global_ptr, new_ptr);
		pr_info("%s: processor:%d write complete\n\n", __func__, smp_processor_id());
		pr_info("%s: Processor:%d\t Starting synchronize_rcu \n", __func__, smp_processor_id());
		synchronize_rcu();
		pr_info("%s: Processor:%d\t Ending synchronize_rcu \n", __func__, smp_processor_id());
		kfree(tmp_ptr);
		msleep(3000);
	}
	return 0;
}


static int read_thread_fn(void *arg)
{
	while(!kthread_should_stop())
	{
		my_data *ptr = NULL;
		rcu_read_lock();
		ptr = rcu_dereference(global_ptr);
		if (ptr != NULL)
			pr_info("%s:processor:%d\tkey:%d\t val:%d\n", __func__, smp_processor_id(), 
						ptr->key, ptr->val);
		else
			pr_info("%s write thread did not yet start\n", __func__);
		rcu_read_unlock();
		msleep(3000);
	}
	return 0;
}

static int __init test_hello_init(void)
{
	global_ptr = kmalloc(sizeof(my_data), GFP_KERNEL);
	global_ptr->key = 1;
	global_ptr->val = 1001;

	thread1 = kthread_run(read_thread_fn, NULL, "read_thread1");
	thread2 = kthread_run(write_thread_fn, NULL, "write_thread1");
	thread3 = kthread_run(read_thread_fn, NULL, "read_thread2");
	return 0;
}

static void __exit test_hello_exit(void)
{
	kthread_stop(thread1);
	kthread_stop(thread2);
	kthread_stop(thread3);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
