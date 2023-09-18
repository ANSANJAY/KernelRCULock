How does RCU/synchronize_cpu() know that all readers have finished reading?
============================================================================

We know RCU read-side critical sections delimited by rcu_read_lock() and rcu_read_unlock() are not permitted to block or sleep. 

 Therefore, when a given CPU executes a context switch, we are guaranteed that any prior RCU read-side critical sections will have completed. 

synchronize_cpu() returns as soon as all the CPU's have completed one context switch.


