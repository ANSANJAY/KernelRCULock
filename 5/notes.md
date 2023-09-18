Why can't i directly dereference to the pointer/global shared resource?
-----------------------------------------------------------------

or

Why should i use rcu_dereference?
-------------------------------------

Consider the below code fragment:

	struct my_data
	{
		int key;
		int val;
	};

	
	struct my_data *ptr;

	ptr = global;
	add_key_val(ptr->key, ptr->val);


Due to compiler optimization, value of ptr->key, ptr->val are fetched before the value of ptr.

Compiler tries to guess value of ptr

retry:
	ptr = guess(global)
	add_key_val(ptr->key, ptr->val);
	if (ptr != global)
		goto retry;


rcu_dereference() internally uses memory barrier instructions/compiler directives to avoid this.

	rcu_read_lock();
	ptr = rcu_dereference(global);

	if (ptr != NULL) {
		add_key_val(ptr->key, ptr->val);
	}
	rcu_read_unlock();
