RCU Design
===============

Core of RCU is based on two primitives:

	1. RCU Read-side critical sections : rcu_read_lock/rcu_write_lock

	2. RCU Synchronization : synchronize_rcu/call_rcu()

Developers can use RCU Read-Side Critical sections and RCU Synchronization to build data structures that allow concurrent reading during updates.


Header File: <linux/rcupdate.h>

Core RCU API
===============

a.	rcu_read_lock()
b.	rcu_read_unlock()
c.	synchronize_rcu() / call_rcu()
d.	rcu_assign_pointer()
e.	rcu_dereference()

Write operation:
====================

	Direct assign a new pointer to a pointer is protected by RCU is forbidden

	You need to use rcu_assign_pointer() function.

	struct my_data
	{
		int key;
		int val;
	};

	struct my_data *global = NULL;

	Write operation
	----------------

	struct my_data *new_ptr;
	new_ptr = kmalloc(sizeof(struct my_data), GFP_KERNEL);
	new_ptr->key = 1;
	new_ptr->val = 1234;
	rcu_assign_pointer(global, new_ptr);


	
