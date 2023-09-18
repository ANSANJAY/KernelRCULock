void call_rcu(struct rcu_head *head, rcu_callback_t func);

Another way to avoid blocking is to register a callback which will be called when all the read-side critical sections are completed.

This requires that an instance of rcu_head is embedded
