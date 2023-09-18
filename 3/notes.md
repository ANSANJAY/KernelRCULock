Why can't i directly write to the pointer/global shared resource?
-----------------------------------------------------------------

or

Why should i use rcu_assign_pointer?
-------------------------------------

Consider the below code fragment:

	struct my_data
	{
		int key;
		int val;
	};

	struct my_data *global = NULL;

	....
	
	struct my_data *ptr;
	ptr = kmalloc(sizeof(struct my_data), GFP_KERNEL);
	ptr->key = 1;
	ptr->val = 1201;
	global = ptr;


The problem here is CPU/Compiler can perform optimizations and can execute the above last three lines in any order

If assignment of ptr to global happens before initialization of ptr fields, concurrent readers can could see the unitialized values.

	
	ptr = kmalloc(sizeof(struct my_data), GFP_KERNEL);
	global = ptr;
	ptr->key = 1;
	ptr->val = 1201;


We need to keep use memory barriers to keep the things in order.

rcu_assign_pointer will internally use memory barriers and make everything happen as per the order
	
