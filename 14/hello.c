//Is this code concurrency safe
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

typedef struct my_data
{
	struct list_head list;
	int key;
	int data;

}my_data;

LIST_HEAD(listhead);

void insert(int key, int data)
{
	my_data *ptr = kmalloc(sizeof(*ptr), GFP_KERNEL);
	ptr->key = key;
	ptr->data = data;
	list_add_tail(&(ptr->list), &listhead);
}

my_data *search(int key)
{
	my_data *ptr;

	list_for_each_entry(ptr, &listhead, list) {
		if (ptr->key == key)
			return ptr;
	}
	return NULL;
}

void delete(int key)
{
	my_data *ptr;
	
	ptr = search(key);
	if (ptr != NULL) {
		list_del(&(ptr->list));
		kfree(ptr);
	}

}

void print_list(void)
{
	my_data *ptr;

	list_for_each_entry(ptr, &listhead, list) {
		pr_info("key:%d\t value:%d\n", ptr->key, ptr->data);
	}
}

static int __init test_hello_init(void)
{
	insert(1, 1000);
	insert(2, 1001);
	insert(3, 1002);

	pr_info("printing list\n");
	print_list();
	pr_info("deleting key 2\n");
	delete(2);
	pr_info("printing list\n");
	print_list();
	return 0;
}

static void __exit test_hello_exit(void)
{
    pr_info("%s: In exit\n", __func__);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
