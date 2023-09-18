Read operation:
====================

	It is forbidden to simply de-reference the pointer, protected by RCU region

	You need to use rcu_dereference() function.

	Additionally, the code that de-references the pointer and uses the result needs to be embraced by calls to	  rcu_read_lock() and rcu_read_unlock().

	rcu_read_lock() - mark the beginning of an RCU read-side critical section

	rcu_read_unlock() - marks the end of an RCU read-side critical section.

	struct my_data
	{
		int key;
		int val;
	};

	struct my_data *global = NULL;

	global = kmalloc(sizeof(struct my_data), GFP_KERNEL);
	
	Read operation
	----------------

	struct my_data *tmp;
	rcu_read_lock();

	tmp = rcu_dereference(global);
	pr_info("key:%d\t val:%d\n", tmp->key, tmp->val);
	rcu_read_unlock();


	
