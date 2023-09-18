void synchronize_rcu(void);

Calling process is blocked until all pre-existing RCU read-side critical sections on all CPUs have completed
 
After the function returns, it is safe to free the memory associated with the old pointer.

 Note that synchronize_rcu will not necessarily wait for any subsequent RCU read-side critical sections to complete.

		CPU 0                  CPU 1                 CPU 2
	     ----------------- ------------------------- ---------------
	 1.  rcu_read_lock()
	 2.                    enters synchronize_rcu()
	 3.                                               rcu_read_lock()
	 4.  rcu_read_unlock()
	 5.                     exits synchronize_rcu()
	 6.                                              rcu_read_unlock()

